#include "D:\LEGION\LEGION\main.h"

void Utils::CalcScreenCoors(CVector* vecWorld, CVector* vecScreen)
{
	D3DXMATRIX m((float*)(0xB6FA2C));

	DWORD* dwLenX = (DWORD*)(0xC17044);
	DWORD* dwLenY = (DWORD*)(0xC17048);

	vecScreen->x = (vecWorld->z * m._31) + (vecWorld->y * m._21) + (vecWorld->x * m._11) + m._41;
	vecScreen->y = (vecWorld->z * m._32) + (vecWorld->y * m._22) + (vecWorld->x * m._12) + m._42;
	vecScreen->z = (vecWorld->z * m._33) + (vecWorld->y * m._23) + (vecWorld->x * m._13) + m._43;

	double fRecip = (double)1.0 / vecScreen->z;
	vecScreen->x *= (float)(fRecip * (*dwLenX));
	vecScreen->y *= (float)(fRecip * (*dwLenY));
}

void Utils::CalcWorldCoors(CVector* vecScreen, CVector* vecWorld)
{
	D3DXMATRIXA16 m((float*)(0xB6FA2C));

	D3DXMATRIXA16 minv;
	memset(&minv, 0, sizeof(D3DXMATRIXA16));
	m._44 = 1.0f;

	D3DXMatrixInverse(&minv, NULL, &m);

	DWORD* dwLenX = (DWORD*)(0xC17044);
	DWORD* dwLenY = (DWORD*)(0xC17048);

	float fRecip = 1.0f / vecScreen->z;
	vecScreen->x /= fRecip * (*dwLenX);
	vecScreen->y /= fRecip * (*dwLenY);

	vecWorld->x = vecScreen->z * minv._31 + vecScreen->y * minv._21 + vecScreen->x * minv._11 + minv._41;
	vecWorld->y = vecScreen->z * minv._32 + vecScreen->y * minv._22 + vecScreen->x * minv._12 + minv._42;
	vecWorld->y = vecScreen->z * minv._33 + vecScreen->y * minv._23 + vecScreen->x * minv._13 + minv._43;
}

void Utils::CalcMapToScreen(ImVec2 vecWindow, CVector* vecMap, CVector* vecScreen, float fSize)
{
	vecScreen->x = vecWindow.x + fSize / 2.f + (vecMap->x / (3000.f / (fSize / 2.f)));
	vecScreen->y = vecWindow.y + fSize / 2.f - (vecMap->y / (3000.f / (fSize / 2.f)));
}

void Utils::CalcScreenToMap(ImVec2 vecWindow, CVector* vecScreen, CVector* vecMap, float fSize)
{
	if (vecScreen->x >= fSize / 2.f)
		vecMap->x = vecWindow.x + (vecScreen->x * (3000.f / (fSize / 2.f))) - 3000.f;
	else vecMap->x = vecWindow.x + (3000.f - (vecScreen->x * (3000.f / (fSize / 2.f)))) * -1.f;

	if (vecScreen->y >= fSize / 2.f)
		vecMap->y = vecWindow.y + ((vecScreen->y * (3000.f / (fSize / 2.f))) - 3000.f) * -1.f;
	else vecMap->y = vecWindow.y + 3000.f - (vecScreen->y * (3000.f / (fSize / 2.f)));
}

float Utils::getDistance(CVector vecTarget)
{
	CVector vecSelf = FindPlayerPed()->GetPosition();
	return sqrt((vecSelf.x - vecTarget.x) * (vecSelf.x - vecTarget.x) + (vecSelf.y - vecTarget.y) * (vecSelf.y- vecTarget.y) + (vecSelf.z - vecTarget.z) * (vecSelf.z - vecTarget.z));
}

float Utils::getDistanceFromCamera(CVector vecTarget)
{
	CVector vecSrc = TheCamera.m_vecGameCamPos;
	return sqrt((vecSrc.x - vecTarget.x) * (vecSrc.x- vecTarget.x) + (vecSrc.y - vecTarget.y) * (vecSrc.y - vecTarget.y) + (vecSrc.z - vecTarget.z) * (vecSrc.z - vecTarget.z));
}

void Utils::DisembarkInstantly()
{
	CTaskManager* taskManager = &FindPlayerPed()->m_pIntelligence->m_TaskMgr;

	for (int i = 0; i < TASK_PRIMARY_MAX; i++)
	{
		CTask* pTask = taskManager->m_aPrimaryTasks[i];
		if (pTask)
		{
			pTask->MakeAbortable(FindPlayerPed(), ABORT_PRIORITY_IMMEDIATE, NULL);
			if (i != TASK_PRIMARY_DEFAULT)
				taskManager->SetTask(NULL, i, 0);
		}
	}

	for (int i = 0; i < TASK_SECONDARY_MAX; i++)
	{
		CTask* pTask = taskManager->m_aSecondaryTasks[i];
		if (pTask)
		{
			pTask->MakeAbortable(FindPlayerPed(), ABORT_PRIORITY_IMMEDIATE, NULL);
			if (i != TASK_SECONDARY_FACIAL_COMPLEX)
				taskManager->SetTaskSecondary(NULL, i);
		}
	}
}

void Utils::PerformAnimation(const char* szBlockName, const char* szAnimName, int iTime, bool bLoop, bool bUpdatePosition, bool bInterruptable, bool bFreezeLastFrame, bool bRunInSequence, bool bOffsetPed, bool bHoldLastFrame)
{
	CAnimBlock* pBlock = CAnimManager::GetAnimationBlock(szBlockName);
	if (pBlock)
	{
		bool bLoaded = true;

		if (!pBlock->bLoaded)
		{
			int iTimeToWait = 50;

			CStreaming::RequestModel((((DWORD)pBlock - 0xb5d4a0) / 32) + 25575, 4);
			CStreaming::LoadAllRequestedModels(false);

			while (!pBlock->bLoaded && iTimeToWait != 0)
			{
				iTimeToWait--;
				Sleep(10);
			}

			if (iTimeToWait == 0)
				bLoaded = false;
		}

		if (bLoaded)
		{
			CTaskManager* taskManager = &FindPlayerPed()->m_pIntelligence->m_TaskMgr;
			for (int i = 0; i < TASK_PRIMARY_MAX; i++)
			{
				CTask* pTask = taskManager->m_aPrimaryTasks[i];
				if (pTask)
					pTask->MakeAbortable(FindPlayerPed(), ABORT_PRIORITY_IMMEDIATE, NULL);
			}
			for (int i = 0; i < TASK_SECONDARY_MAX; i++)
			{
				CTask* pTask = taskManager->m_aSecondaryTasks[i];
				if (pTask)
					pTask->MakeAbortable(FindPlayerPed(), ABORT_PRIORITY_IMMEDIATE, NULL);
			}

			FindPlayerPed()->m_pIntelligence->m_TaskMgr.SetTask(NULL, TASK_PRIMARY_EVENT_RESPONSE_TEMP, 0);

			CTask* jumpTask = FindPlayerPed()->m_pIntelligence->m_TaskMgr.FindActiveTaskByType(211);
			if (jumpTask)
				FindPlayerPed()->m_pIntelligence->m_TaskMgr.SetTask(NULL, TASK_PRIMARY_PRIMARY, 0);

			int flags = 0x10;
			if (bLoop) flags |= 0x2;
			if (bUpdatePosition)
			{
				flags |= 0x40;
				flags |= 0x80;
			}
			if (!bFreezeLastFrame)
				flags |= 0x08;

			CTask* pTask = new CTaskSimpleRunNamedAnim(szAnimName, pBlock->szName, flags, 4.0f, iTime, !bInterruptable, bRunInSequence, bOffsetPed, bHoldLastFrame);
			if (pTask)
				FindPlayerPed()->m_pIntelligence->m_TaskMgr.SetTask(pTask, TASK_PRIMARY_PRIMARY, false);
		}
		else
		{
			CStreaming::RequestModel((((DWORD)pBlock - 0xb5d4a0) / 32) + 25575, 8);
			CStreaming::LoadAllRequestedModels(false);
		}
	}
}

bool Utils::isPlayingAnimation(CEntity* pEntity, char const* szAnimName)
{
	return RpAnimBlendClumpGetAssociation(pEntity->m_pRwClump, szAnimName);
}

CVector* Utils::getBonePosition(CPed* pPed, ePedBones bone, CVector* vecPosition)
{
	pPed->GetBonePosition(*(RwV3d*)vecPosition, bone, true);
	return vecPosition;
}

float Utils::vecLength(CVector vecPos)
{
	return sqrt((vecPos.x * vecPos.x) + (vecPos.y * vecPos.y + (vecPos.z * vecPos.z)));
}