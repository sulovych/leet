#include "D:\LEGION\LEGION\main.h"

CAimbot* pAimbot;

static ULONGLONG dwStartTick = 0; // таймер для получения видимости прицела
static ULONGLONG dwStartTick3 = 0; // таймер для возврата координат прицела
int crosshair = 0;

void CAimbot::Update()
{
	int iMode = TheCamera.m_aCams[0].m_nMode;
	bCrosshair = iMode == 53 || iMode == 7;
	if (bCrosshair && dwStartTick == 0)
	{
		dwStartTick = GetTickCount64();
		crosshair = 1;
	}	
	if (!bCrosshair)
	{
		crosshair = 0;
		dwStartTick = 0;
	}

	if (pSAMP->getPlayers()->pLocalPlayer->byteCurrentWeapon != 34)
	{
		vecCrosshair.x = ImGui::GetIO().DisplaySize.x * 0.5299999714f;
		vecCrosshair.y = ImGui::GetIO().DisplaySize.y * 0.4f;
	}
	else
	{
		vecCrosshair.x = ImGui::GetIO().DisplaySize.x / 2.f;
		vecCrosshair.y = ImGui::GetIO().DisplaySize.y / 2.f;
	}

	GetAimingPlayer();
	GetAimingPlayer2();
	GetAimingPlayer3();
	SmoothAimbot();
	FlickShot();
	Triggerbot();
	Coords();
}

void CAimbot::Render()
{
		if (g_Config.g_Aimbot.bDrawDebug)
		{
			if (bCrosshair && g_Config.g_Aimbot.bAimbotEnabledSmooth[pSAMP->getPlayers()->pLocalPlayer->byteCurrentWeapon])
				pRender->DrawCircle(vecCrosshair, (float)g_Config.g_Aimbot.iAimbotConfig[pSAMP->getPlayers()->pLocalPlayer->byteCurrentWeapon][FOV_SMOOTH], { 0.f, 1.f, 0.f }, g_Config.g_Aimbot.fOutlineThickness);
	        if (g_Config.g_Aimbot.bAimbotEnabledFlick[pSAMP->getPlayers()->pLocalPlayer->byteCurrentWeapon])
				pRender->DrawCircle(vecCrosshair, (float)g_Config.g_Aimbot.iAimbotConfig[pSAMP->getPlayers()->pLocalPlayer->byteCurrentWeapon][FOV_FLICK], { 0.f, 1.f, 1.f }, g_Config.g_Aimbot.fOutlineThickness);
			if (g_Config.g_Aimbot.bAimbotEnabledSilent[pSAMP->getPlayers()->pLocalPlayer->byteCurrentWeapon])
				pRender->DrawCircle(vecCrosshair, (float)g_Config.g_Aimbot.iAimbotConfig[pSAMP->getPlayers()->pLocalPlayer->byteCurrentWeapon][FOV_SILENT], { 1.f, 0.f, 0.f }, g_Config.g_Aimbot.fOutlineThickness);
			if (bCrosshair && g_Config.g_Aimbot.bAimbotEnabledSmooth[pSAMP->getPlayers()->pLocalPlayer->byteCurrentWeapon] && iTargetPlayer != -1)
				pRender->DrawLine(vecCrosshair, vecTargetBone, { 0.f, 1.f, 0.f }, g_Config.g_Aimbot.fOutlineThickness);
			if (g_Config.g_Aimbot.bAimbotEnabledFlick[pSAMP->getPlayers()->pLocalPlayer->byteCurrentWeapon] && iTargetPlayer2 != -1)
				pRender->DrawLine(vecCrosshair, vecTargetBone2, { 0.f, 1.f, 1.f }, g_Config.g_Aimbot.fOutlineThickness);
			if (g_Config.g_Aimbot.bAimbotEnabledSilent[pSAMP->getPlayers()->pLocalPlayer->byteCurrentWeapon] && iTargetPlayer3 != -1)
				pRender->DrawLine(vecCrosshair, vecTargetBone3, { 1.f, 0.f, 0.f }, g_Config.g_Aimbot.fOutlineThickness);
		}
}

void CAimbot::GetAimingPlayer()
{
	iTargetPlayer = -1;
	float fNearestDistance = 9999.f;

	if (g_Config.g_Aimbot.bAimbotEnabledSmooth[pSAMP->getPlayers()->pLocalPlayer->byteCurrentWeapon] && isKeyDown(VK_RBUTTON))
	{
		CVector vecCamera, vecOrigin, vecTarget;
		Utils::getBonePosition(FindPlayerPed(), BONE_RIGHTWRIST, &vecOrigin);
		TheCamera.Find3rdPersonCamTargetVector(100.f, vecOrigin, &vecCamera, &vecTarget);

		for (int i = 0; i < SAMP_MAX_PLAYERS; i++)
		{
			if (!pSAMP->isPlayerStreamed(i))
				continue;

			CPed* pPed = CPools::GetPed(pSAMP->getPlayers()->pRemotePlayer[i]->pPlayerData->pSAMP_Actor->ulGTAEntityHandle);
			if (!pPed || !pPed->IsAlive())
				continue;

			if (g_Config.g_Aimbot.bTeamProtect && pSAMP->getPlayerColor(i) == pSAMP->getPlayerColor(pSAMP->getPlayers()->sLocalPlayerID))
				continue;

			if (g_Config.g_Aimbot.bIgnoreAFK && pSAMP->getPlayers()->pRemotePlayer[i]->pPlayerData->iAFKState == 2)
				continue;

			float fTargetDistance = Math::vect3_dist(&pSAMP->getPlayers()->pRemotePlayer[i]->pPlayerData->pSAMP_Actor->pGTA_Ped->base.matrix[12], &pSAMP->getPlayers()->pLocalPlayer->pSAMP_Actor->pGTA_Ped->base.matrix[12]);
			if (!g_Config.g_Aimbot.bIgnoreMaxDistance && fTargetDistance > fWeaponRange[pSAMP->getPlayers()->pLocalPlayer->byteCurrentWeapon])
				continue;

			byte state = pSAMP->getPlayers()->pRemotePlayer[i]->pPlayerData->bytePlayerState;
			if (g_Config.g_Aimbot.bBoneCenter)
				iBoneList[0] = BONE_SPINE1;
			else
				iBoneList[0] = -1;
			if (g_Config.g_Aimbot.bBoneHead)
				iBoneList[1] = BONE_NECK;
			else iBoneList[1] = -1;
			if (g_Config.g_Aimbot.bBoneNeck)
				iBoneList[2] = BONE_UPPERTORSO;
			else iBoneList[2] = -1;
			if (g_Config.g_Aimbot.bBoneElbows)
			{
				iBoneList[3] = BONE_RIGHTELBOW;
				iBoneList[4] = BONE_LEFTELBOW;
			}
			else
			{
				iBoneList[3] = -1;
				iBoneList[4] = -1;
			}
			if (g_Config.g_Aimbot.bBoneStomach)
				iBoneList[5] = BONE_PELVIS;
			else iBoneList[5] = -1;
			if (g_Config.g_Aimbot.bBoneKnees)
			{
				iBoneList[6] = BONE_LEFTKNEE;
				iBoneList[7] = BONE_RIGHTKNEE;
			}
			else
			{
				iBoneList[6] = -1;
				iBoneList[7] = -1;
			}
			if (g_Config.g_Aimbot.bBoneShoulders)
			{
				iBoneList[8] = BONE_RIGHTSHOULDER;
				iBoneList[9] = BONE_LEFTSHOULDER;
			}
			else
			{
				iBoneList[8] = -1;
				iBoneList[9] = -1;
			}
			if (g_Config.g_Aimbot.bShootInCar && state != PLAYER_STATE_ONFOOT)
			{
				for (int j = 0; j < 10; j++)
					iBoneList[j] = BONE_HEAD;
			}
			for (auto iBone : iBoneList)
			{
				CVector vecBone, vecBoneScreen;
				Utils::getBonePosition(pPed, (ePedBones)iBone, &vecBone);
				Utils::CalcScreenCoors(&vecBone, &vecBoneScreen);
				if (vecBoneScreen.z < 1.0f)
					continue;

				float fCentreDistance = Math::vect2_dist(&vecCrosshair, &vecBoneScreen);
				if (fCentreDistance >= (float)g_Config.g_Aimbot.iAimbotConfig[pSAMP->getPlayers()->pLocalPlayer->byteCurrentWeapon][FOV_SMOOTH] * 1.5f)
					continue;

				if (!g_Config.g_Aimbot.bWallShot && !CWorld::GetIsLineOfSightClear(vecCamera, vecBone, true, true, false, true, true, true, false))
					continue;

				if (fCentreDistance < fNearestDistance)
				{
					fNearestDistance = fCentreDistance;
					iTargetPlayer = i; iTargetBone = iBone;
					vecTargetBone = vecBoneScreen;
				}
			}
		}
	}
}

void CAimbot::GetAimingPlayer2()
{
	iTargetPlayer2 = -1;
	float fNearestDistance2 = 9999.f;

	if (g_Config.g_Aimbot.bAimbotEnabledFlick[pSAMP->getPlayers()->pLocalPlayer->byteCurrentWeapon])
	{
		CVector vecCamera2, vecOrigin2, vecTarget2;
		Utils::getBonePosition(FindPlayerPed(), BONE_RIGHTWRIST, &vecOrigin2);
		TheCamera.Find3rdPersonCamTargetVector(100.f, vecOrigin2, &vecCamera2, &vecTarget2);

		for (int i = 0; i < SAMP_MAX_PLAYERS; i++)
		{
			if (!pSAMP->isPlayerStreamed(i))
				continue;

			CPed* pPed = CPools::GetPed(pSAMP->getPlayers()->pRemotePlayer[i]->pPlayerData->pSAMP_Actor->ulGTAEntityHandle);
			if (!pPed || !pPed->IsAlive())
				continue;

			if (g_Config.g_Aimbot.bTeamProtect && pSAMP->getPlayerColor(i) == pSAMP->getPlayerColor(pSAMP->getPlayers()->sLocalPlayerID))
				continue;

			if (g_Config.g_Aimbot.bIgnoreAFK && pSAMP->getPlayers()->pRemotePlayer[i]->pPlayerData->iAFKState == 2)
				continue;

			float fTargetDistance = Math::vect3_dist(&pSAMP->getPlayers()->pRemotePlayer[i]->pPlayerData->pSAMP_Actor->pGTA_Ped->base.matrix[12], &pSAMP->getPlayers()->pLocalPlayer->pSAMP_Actor->pGTA_Ped->base.matrix[12]);
			if (!g_Config.g_Aimbot.bIgnoreMaxDistance && fTargetDistance > fWeaponRange[pSAMP->getPlayers()->pLocalPlayer->byteCurrentWeapon])
				continue;

			byte state = pSAMP->getPlayers()->pRemotePlayer[i]->pPlayerData->bytePlayerState;
			if (g_Config.g_Aimbot.bBoneCenter2)
				iBoneList2[0] = BONE_SPINE1;
			else
				iBoneList2[0] = -1;
			if (g_Config.g_Aimbot.bBoneHead2)
				iBoneList2[1] = BONE_NECK;
			else iBoneList2[1] = -1;
			if (g_Config.g_Aimbot.bBoneNeck2)
				iBoneList2[2] = BONE_UPPERTORSO;
			else iBoneList2[2] = -1;
			if (g_Config.g_Aimbot.bBoneElbows2)
			{
				iBoneList2[3] = BONE_RIGHTELBOW;
				iBoneList2[4] = BONE_LEFTELBOW;
			}
			else
			{
				iBoneList2[3] = -1;
				iBoneList2[4] = -1;
			}
			if (g_Config.g_Aimbot.bBoneStomach2)
				iBoneList2[5] = BONE_PELVIS;
			else iBoneList2[5] = -1;
			if (g_Config.g_Aimbot.bBoneKnees2)
			{
				iBoneList2[6] = BONE_LEFTKNEE;
				iBoneList2[7] = BONE_RIGHTKNEE;
			}
			else
			{
				iBoneList2[6] = -1;
				iBoneList2[7] = -1;
			}
			if (g_Config.g_Aimbot.bBoneShoulders2)
			{
				iBoneList2[8] = BONE_RIGHTSHOULDER;
				iBoneList2[9] = BONE_LEFTSHOULDER;
			}
			else
			{
				iBoneList2[8] = -1;
				iBoneList2[9] = -1;
			}
			if (g_Config.g_Aimbot.bShootInCar && state != PLAYER_STATE_ONFOOT)
			{
				for (int j = 0; j < 10; j++)
					iBoneList2[j] = BONE_HEAD;
			}

			for (auto iBone2 : iBoneList2)
			{
				CVector vecBone2, vecBoneScreen2;
				Utils::getBonePosition(pPed, (ePedBones)iBone2, &vecBone2);
				Utils::CalcScreenCoors(&vecBone2, &vecBoneScreen2);
				if (vecBoneScreen2.z < 1.0f)
					continue;

				float fCentreDistance2 = Math::vect2_dist(&vecCrosshair, &vecBoneScreen2);
				if (fCentreDistance2 >= (float)g_Config.g_Aimbot.iAimbotConfig[pSAMP->getPlayers()->pLocalPlayer->byteCurrentWeapon][FOV_FLICK] * 1.5f)
					continue;

				if (!g_Config.g_Aimbot.bWallShot && ((g_Config.g_Aimbot.bShootInCar && (state != PLAYER_STATE_ONFOOT)) ? !CWorld::GetIsLineOfSightClear(vecCamera2, vecBone2, true, false, false, true, true, false, false) : !CWorld::GetIsLineOfSightClear(vecCamera2, vecBone2, true, true, false, true, true, true, false)))
					continue;

				if (fCentreDistance2 <= fNearestDistance2)
				{
					fNearestDistance2 = fCentreDistance2;
					iTargetPlayer2 = i; iTargetBone2 = iBone2;
					vecTargetBone2 = vecBoneScreen2;
				}
			}
		}
	}
}

void CAimbot::GetAimingPlayer3()
{
	iTargetPlayer3 = -1;
	float fNearestDistance3 = 9999.f;

	if (g_Config.g_Aimbot.bAimbotEnabledSilent[pSAMP->getPlayers()->pLocalPlayer->byteCurrentWeapon])
	{
		CVector vecCamera3, vecOrigin3, vecTarget3;
		Utils::getBonePosition(FindPlayerPed(), BONE_RIGHTWRIST, &vecOrigin3);
		TheCamera.Find3rdPersonCamTargetVector(100.f, vecOrigin3, &vecCamera3, &vecTarget3);

		for (int i = 0; i < SAMP_MAX_PLAYERS; i++)
		{
			if (!pSAMP->isPlayerStreamed(i))
				continue;

			CPed* pPed = CPools::GetPed(pSAMP->getPlayers()->pRemotePlayer[i]->pPlayerData->pSAMP_Actor->ulGTAEntityHandle);
			if (!pPed || !pPed->IsAlive())
				continue;

			if (g_Config.g_Aimbot.bTeamProtect && pSAMP->getPlayerColor(i) == pSAMP->getPlayerColor(pSAMP->getPlayers()->sLocalPlayerID))
				continue;

			if (g_Config.g_Aimbot.bIgnoreAFK && pSAMP->getPlayers()->pRemotePlayer[i]->pPlayerData->iAFKState == 2)
				continue;

			float fTargetDistance = Math::vect3_dist(&pSAMP->getPlayers()->pRemotePlayer[i]->pPlayerData->pSAMP_Actor->pGTA_Ped->base.matrix[12], &pSAMP->getPlayers()->pLocalPlayer->pSAMP_Actor->pGTA_Ped->base.matrix[12]);
			if (!g_Config.g_Aimbot.bIgnoreMaxDistance && fTargetDistance > fWeaponRange[pSAMP->getPlayers()->pLocalPlayer->byteCurrentWeapon])
				continue;

			byte state = pSAMP->getPlayers()->pRemotePlayer[i]->pPlayerData->bytePlayerState;
			if (g_Config.g_Aimbot.bBoneCenter3)
				iBoneList3[0] = BONE_SPINE1;
			else
				iBoneList3[0] = -1;
			if (g_Config.g_Aimbot.bBoneHead3)
				iBoneList3[1] = BONE_NECK;
			else iBoneList3[1] = -1;
			if (g_Config.g_Aimbot.bBoneNeck3)
				iBoneList3[2] = BONE_UPPERTORSO;
			else iBoneList3[2] = -1;
			if (g_Config.g_Aimbot.bBoneElbows3)
			{
				iBoneList3[3] = BONE_RIGHTELBOW;
				iBoneList3[4] = BONE_LEFTELBOW;
			}
			else
			{
				iBoneList3[3] = -1;
				iBoneList3[4] = -1;
			}
			if (g_Config.g_Aimbot.bBoneStomach3)
				iBoneList3[5] = BONE_PELVIS;
			else iBoneList3[5] = -1;
			if (g_Config.g_Aimbot.bBoneKnees3)
			{
				iBoneList3[6] = BONE_LEFTKNEE;
				iBoneList3[7] = BONE_RIGHTKNEE;
			}
			else
			{
				iBoneList3[6] = -1;
				iBoneList3[7] = -1;
			}
			if (g_Config.g_Aimbot.bBoneShoulders3)
			{
				iBoneList3[8] = BONE_RIGHTSHOULDER;
				iBoneList3[9] = BONE_LEFTSHOULDER;
			}
			else
			{
				iBoneList3[8] = -1;
				iBoneList3[9] = -1;
			}
			if (g_Config.g_Aimbot.bShootInCar && state != PLAYER_STATE_ONFOOT)
			{
				for (int j = 0; j < 10; j++)
					iBoneList3[j] = BONE_HEAD;
			}

			for (auto iBone3 : iBoneList3)
			{
				CVector vecBone3, vecBoneScreen3;
				Utils::getBonePosition(pPed, (ePedBones)iBone3, &vecBone3);
				Utils::CalcScreenCoors(&vecBone3, &vecBoneScreen3);
				if (vecBoneScreen3.z < 1.0f)
					continue;

				float fCentreDistance3 = Math::vect2_dist(&vecCrosshair, &vecBoneScreen3);
				if (fCentreDistance3 >= (float)g_Config.g_Aimbot.iAimbotConfig[pSAMP->getPlayers()->pLocalPlayer->byteCurrentWeapon][FOV_SILENT] * 1.5f)
					continue;

				if (!g_Config.g_Aimbot.bWallShot && !CWorld::GetIsLineOfSightClear(vecCamera3, vecBone3, true, true, false, true, true, true, false))
					continue;

				if (fCentreDistance3 < fNearestDistance3)
				{
					fNearestDistance3 = fCentreDistance3;
					iTargetPlayer3 = i; iTargetBone3 = iBone3;
					vecTargetBone3 = vecBoneScreen3;
				}
			}
		}
	}
}

void CAimbot::SmoothAimbot()
{
	if (g_Config.g_Aimbot.bAimbotEnabledSmooth[pSAMP->getPlayers()->pLocalPlayer->byteCurrentWeapon] && iTargetPlayer != -1 && GetTickCount64() - dwStartTick > 420 && crosshair == 1)
	{
		if (g_Config.g_Aimbot.bSmoothIsFire && !isKeyDown(VK_LBUTTON))
			return;

		int anim = pSAMP->getPlayers()->pLocalPlayer->onFootData.sCurrentAnimationID;
		if (g_Config.g_Aimbot.bIsStun && (anim == 1071 || anim == 1072 || anim == 1073 || anim == 1074 || anim == 1075 || anim == 1076 || anim == 1077 || anim == 1078 || anim == 1079 || anim == 1080 || anim == 1081 || anim == 1082 || anim == 1083 || anim == 1084 || anim == 1085 || anim == 1086 || anim == 1240 || anim == 1241 || anim == 1242 || anim == 1243))
			return;

		CPed* pPed = CPools::GetPed(pSAMP->getPlayers()->pRemotePlayer[pAimbot->iTargetPlayer]->pPlayerData->pSAMP_Actor->ulGTAEntityHandle);
		if (!pPed)
			return;

		if (g_Config.g_Aimbot.bStopOnBody)
		{
			CVector vecCamera, vecOrigin, vecTarget;
			if (pSAMP->getPlayers()->pLocalPlayer->byteCurrentWeapon != 34)
			{
				Utils::getBonePosition(FindPlayerPed(), BONE_RIGHTWRIST, &vecOrigin);
				TheCamera.Find3rdPersonCamTargetVector(100.f, vecOrigin, &vecCamera, &vecTarget);
			}
			else
			{
				CVector vecFront = TheCamera.m_aCams[0].m_vecFront;
				vecFront.Normalise();
				vecOrigin = *TheCamera.GetGameCamPosition();
				vecOrigin += (vecFront * 2.0f);
				vecTarget = vecOrigin + (vecFront * 100.f);
			}
			CColPoint pCollision; CEntity* pCollisionEntity = NULL;
			bool bCollision = CWorld::ProcessLineOfSight(vecCamera, vecTarget, pCollision, pCollisionEntity, !g_Config.g_Aimbot.bWallShot, !g_Config.g_Aimbot.bWallShot, true, true, true, true, false, true);
			if (bCollision && pCollisionEntity && pCollisionEntity->m_nType == ENTITY_TYPE_PED && pCollisionEntity == (CEntity*)pPed)
				return;
		}

		CVector vecOrigin = *TheCamera.GetGameCamPosition(), vecTarget = *Utils::getBonePosition(pPed, (ePedBones)iTargetBone, &vecTarget), vecVector = vecOrigin - vecTarget;

		float fFix = 0.f, fVecX = 0.f, fZ = 0.f, fX = 0.f;

		if (TheCamera.m_aCams[0].m_nMode == 53 || TheCamera.m_aCams[0].m_nMode == 55)
		{
			float fMult = tan(TheCamera.FindCamFOV() / 2.0f * 0.017453292f);
			fZ = M_PI - atan2(1.0f, fMult * ((1.0f - CCamera::m_f3rdPersonCHairMultY * 2.0f) * (1.0f / CDraw::ms_fAspectRatio)));
			fX = M_PI - atan2(1.0f, fMult * (CCamera::m_f3rdPersonCHairMultX * 2.0f - 1.0f));
		}
		else fX = fZ = M_PI / 2;

		BYTE byteWeapon = pSAMP->getPlayers()->pLocalPlayer->byteCurrentWeapon;
		if (byteWeapon >= 22 && byteWeapon <= 29 || byteWeapon == 32) fFix = 0.04253f;
		else if (byteWeapon == 30 || byteWeapon == 31) fFix = 0.028f;
		else if (byteWeapon == 33) fFix = 0.01897f;

		float fDistX = sqrt(vecVector.x * vecVector.x + vecVector.y * vecVector.y);

		if (vecVector.x <= 0.0 && vecVector.y >= 0.0 || vecVector.x >= 0.0 && vecVector.y >= 0.0)
			fVecX = (acosf(vecVector.x / fDistX) + fFix) - TheCamera.m_aCams[0].m_fHorizontalAngle;
		if (vecVector.x >= 0.0 && vecVector.y <= 0.0 || vecVector.x <= 0.0 && vecVector.y <= 0.0)
			fVecX = (-acosf(vecVector.x / fDistX) + fFix) - TheCamera.m_aCams[0].m_fHorizontalAngle;

		float fSmoothX = fVecX / (g_Config.g_Aimbot.iAimbotConfig[byteWeapon][SMOOTH] * 1.6);

		if (fSmoothX > -1.0 && fSmoothX < 0.5 && fVecX > -2.0 && fVecX < 2.0)
			TheCamera.m_aCams[0].m_fHorizontalAngle += fSmoothX;

		if (g_Config.g_Aimbot.bSmoothLockY)
		{
			float fDistZ = sqrt(vecVector.x * vecVector.x + vecVector.y * vecVector.y);
			float fSmoothZ = (atan2f(fDistZ, vecVector.z) - fZ - TheCamera.m_aCams[0].m_fVerticalAngle) / (g_Config.g_Aimbot.iAimbotConfig[byteWeapon][SMOOTH] * 2);
			TheCamera.m_aCams[0].m_fVerticalAngle += fSmoothZ;
		}
	}
}

void CAimbot::FlickShot()
{
	if (g_Config.g_Aimbot.bAimbotEnabledFlick[pSAMP->getPlayers()->pLocalPlayer->byteCurrentWeapon] && iTargetPlayer2 != -1)
	{

		if (GetTickCount64() - dwStartTick > 420 && crosshair == 1)
			return;

		if (g_Config.g_Aimbot.bSmoothIsFire && !isKeyDown(VK_LBUTTON))
			return;

		int anim = pSAMP->getPlayers()->pLocalPlayer->onFootData.sCurrentAnimationID;
		if (anim != 1162 && anim != 1163 && anim != 1167 || ImGui::GetIO().MouseDrawCursor == true || pSAMP->isScoreBoardOpen())
			return;

		if (g_Config.g_Aimbot.bIsStun && (anim == 1071 || anim == 1072 || anim == 1073 || anim == 1074 || anim == 1075 || anim == 1076 || anim == 1077 || anim == 1078 || anim == 1079 || anim == 1080 || anim == 1081 || anim == 1082 || anim == 1083 || anim == 1084 || anim == 1085 || anim == 1086 || anim == 1240 || anim == 1241 || anim == 1242 || anim == 1243))
			return;

		CPed* pPed = CPools::GetPed(pSAMP->getPlayers()->pRemotePlayer[pAimbot->iTargetPlayer2]->pPlayerData->pSAMP_Actor->ulGTAEntityHandle);
		if (!pPed)
			return;

		if (g_Config.g_Aimbot.bStopOnBody2)
		{
			CVector vecCamera2, vecOrigin2, vecTarget2;
			if (pSAMP->getPlayers()->pLocalPlayer->byteCurrentWeapon != 34)
			{
				Utils::getBonePosition(FindPlayerPed(), BONE_RIGHTWRIST, &vecOrigin2);
				TheCamera.Find3rdPersonCamTargetVector(100.f, vecOrigin2, &vecCamera2, &vecTarget2);
			}
			else
			{
				CVector vecFront2 = TheCamera.m_aCams[0].m_vecFront;
				vecFront2.Normalise();
				vecOrigin2 = *TheCamera.GetGameCamPosition();
				vecOrigin2 += (vecFront2 * 2.0f);
				vecTarget2 = vecOrigin2 + (vecFront2 * 100.f);
			}
			CColPoint pCollision; CEntity* pCollisionEntity = NULL;
			bool bCollision = CWorld::ProcessLineOfSight(vecCamera2, vecTarget2, pCollision, pCollisionEntity, !g_Config.g_Aimbot.bWallShot, !g_Config.g_Aimbot.bWallShot, true, true, true, true, false, true);
			if (bCollision && pCollisionEntity && pCollisionEntity->m_nType == ENTITY_TYPE_PED && pCollisionEntity == (CEntity*)pPed)
				return;
		}

		CVector vecOrigin2 = *TheCamera.GetGameCamPosition(), vecTarget2 = *Utils::getBonePosition(pPed, (ePedBones)iTargetBone2, &vecTarget2), vecVector2 = vecOrigin2 - vecTarget2;

		float fFix = 0.f, fVecX = 0.f, fZ = 0.f, fX = 0.f;

		if (TheCamera.m_aCams[0].m_nMode == 53 || TheCamera.m_aCams[0].m_nMode == 55)
		{
			float fMult = tan(TheCamera.FindCamFOV() / 2.0f * 0.017453292f);
			fZ = M_PI - atan2(1.0f, fMult * ((1.0f - CCamera::m_f3rdPersonCHairMultY * 2.0f) * (1.0f / CDraw::ms_fAspectRatio)));
			fX = M_PI - atan2(1.0f, fMult * (CCamera::m_f3rdPersonCHairMultX * 2.0f - 1.0f));
		}
		else fX = fZ = M_PI / 2;

		BYTE byteWeapon = pSAMP->getPlayers()->pLocalPlayer->byteCurrentWeapon;
		if (byteWeapon >= 22 && byteWeapon <= 29 || byteWeapon == 32) fFix = 0.04253f;
		else if (byteWeapon == 30 || byteWeapon == 31) fFix = 0.048f;
		else if (byteWeapon == 33) fFix = 0.04542f;

		float fDistX = sqrt(vecVector2.x * vecVector2.x + vecVector2.y * vecVector2.y);

		if (vecVector2.x <= 0.0 && vecVector2.y >= 0.0 || vecVector2.x >= 0.0 && vecVector2.y >= 0.0)
			fVecX = (acosf(vecVector2.x / fDistX) + fFix) - TheCamera.m_aCams[0].m_fHorizontalAngle;
		if (vecVector2.x >= 0.0 && vecVector2.y <= 0.0 || vecVector2.x <= 0.0 && vecVector2.y <= 0.0)
			fVecX = (-acosf(vecVector2.x / fDistX) + fFix) - TheCamera.m_aCams[0].m_fHorizontalAngle;

		float fSmoothX = fVecX / (g_Config.g_Aimbot.iAimbotConfig[byteWeapon][FLICK] * 1.6);

		if (fSmoothX > -1.0 && fSmoothX < 0.5 && fVecX > -2.0 && fVecX < 2.0)
			TheCamera.m_aCams[0].m_fHorizontalAngle += fSmoothX;

		if (g_Config.g_Aimbot.bSmoothLockY2 && pSAMP->getPlayers()->pLocalPlayer->byteCurrentWeapon != 33)
		{
			float fDistZ = sqrt(vecVector2.x * vecVector2.x + vecVector2.y * vecVector2.y);
			float fSmoothZ = (atan2f(fDistZ, vecVector2.z) - fZ - TheCamera.m_aCams[0].m_fVerticalAngle) / (g_Config.g_Aimbot.iAimbotConfig[byteWeapon][FLICK] * 6);
			TheCamera.m_aCams[0].m_fVerticalAngle += fSmoothZ - 0.001;
		}
		else if (g_Config.g_Aimbot.bSmoothLockY2)
		{
			float fDistZ = sqrt(vecVector2.x * vecVector2.x + vecVector2.y * vecVector2.y);
			float fSmoothZ = (atan2f(fDistZ, vecVector2.z) - fZ - TheCamera.m_aCams[0].m_fVerticalAngle) / (g_Config.g_Aimbot.iAimbotConfig[byteWeapon][FLICK] * 8);
			TheCamera.m_aCams[0].m_fVerticalAngle += fSmoothZ - 0.003;
		}
	}
}

bool __stdcall CAimbot::hkFireInstantHit(void* this_, CEntity* pFiringEntity, CVector* pOrigin, CVector* pMuzzle, CEntity* pTargetEntity, CVector* pTarget, CVector* pVec, bool bCrossHairGun, bool bCreateGunFx)
{
	if (pFiringEntity == (CEntity*)FindPlayerPed() && pAimbot->iTargetPlayer3 != -1 && g_Config.g_Aimbot.bAimbotEnabledSilent[pSAMP->getPlayers()->pLocalPlayer->byteCurrentWeapon] && rand() % 100 <= g_Config.g_Aimbot.iAimbotConfig[pSAMP->getPlayers()->pLocalPlayer->byteCurrentWeapon][SILENT])
	{
		static unsigned long dwStartTick2{ GetTickCount() };
		int ammoInClip = FindPlayerPed()->m_aWeapons[FindPlayerPed()->m_nActiveWeaponSlot].m_nAmmoInClip;
		if (g_Config.g_Aimbot.bDisable1st)
		{
			if ( (GetTickCount64() - dwStartTick > 260 && crosshair == 1 && ammoInClip == 7) || (ammoInClip < 7 && (GetTickCount64() - dwStartTick2 > 1500)) )
			{
				    dwStartTick2 = GetTickCount64();
					Memory::memcpy_safe((void*)0x740B4E, "\x6A\x01\x6A\x01", 4);
					*reinterpret_cast<float*>(0x8D6114) = 5.f;
					return pAimbot->oFireInstantHit(this_, pFiringEntity, pOrigin, pMuzzle, pTargetEntity, pTarget, pVec, bCrossHairGun, bCreateGunFx);
			}
		}
		dwStartTick2 = GetTickCount64();

		CPed* pPed = CPools::GetPed(pSAMP->getPlayers()->pRemotePlayer[pAimbot->iTargetPlayer3]->pPlayerData->pSAMP_Actor->ulGTAEntityHandle);
		if (pPed)
		{
			CVector vecCamera3, vecOrigin3, vecTarget3;
			Utils::getBonePosition(FindPlayerPed(), BONE_SPINE1, &vecOrigin3);
			TheCamera.Find3rdPersonCamTargetVector(100.f, vecOrigin3, &vecCamera3, &vecTarget3);
			if (pAimbot->bCrosshair)
				pOrigin = &vecCamera3;

			CVector vecBone3, vecBoneScreen3;
			Utils::getBonePosition(pPed, (ePedBones)pAimbot->iTargetBone3, &vecBone3);
			pTarget = &vecBone3;
			byte state = pSAMP->getPlayers()->pRemotePlayer[pAimbot->iTargetPlayer3]->pPlayerData->bytePlayerState;
			
			if (g_Config.g_Aimbot.bGTrinagle)
			{
				dwStartTick3 = GetTickCount64();
				
				/*std::memcpy((void*)0x60BA52, "\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90", 10);  // ноп треугольник из пкм
				std::memcpy((void*)0x60B874, "\xEB\x14\x85\xC9\xEB\x06\x57\xE8\x80\x61", 10); // ноп треугольник из пкм
				std::memcpy((void*)0x6870ED, "\x90\x90\x90\x90\x90\x90", 5); // ноп треугольник без пкм
				int target = pSAMP->getPlayers()->pLocalPlayer->sAimingAtPid;
				if (target == 65535)
					*reinterpret_cast<CPed**>(*reinterpret_cast<int*>(0xB6F5F0) + 0x79C) = pPed;*/
			
			}
				CVector vecFoot = pPed->GetPosition(), vecFootScreen;
				vecFoot.z -= 1.2f;
				Utils::CalcScreenCoors(&vecFoot, &vecFootScreen);

				float distance = Utils::getDistance(pPed->GetPosition());
				if (distance < 6.5f) 
					g_Config.g_Aimbot.fSilentAccuracy = 100.0f; 

				else if (distance >= 6.5f && distance <= 25.0f)
					g_Config.g_Aimbot.fSilentAccuracy = 100.0f * (25.0f - distance) / (25.0f - 6.5f);
				
				else 
					g_Config.g_Aimbot.fSilentAccuracy = 0.0f; 
				
			pSecure->memcpy_safe((void*)0x740B4E, g_Config.g_Aimbot.bWallShot || (g_Config.g_Aimbot.bIgnoreMaxDistance && g_Config.g_Aimbot.bWallShot) ? "\x6A\x00\x6A\x00" : "\x6A\x01\x6A\x01", 4);
			pSecure->Write(0x8D6114, (float)(g_Config.g_Aimbot.fSilentAccuracy / 20.f));
		}
	}
	else
	{
		Memory::memcpy_safe((void*)0x740B4E, "\x6A\x01\x6A\x01", 4);
		*reinterpret_cast<float*>(0x8D6114) = 5.f;
	}
	return pAimbot->oFireInstantHit(this_, pFiringEntity, pOrigin, pMuzzle, pTargetEntity, pTarget, pVec, bCrossHairGun, bCreateGunFx);
}

void CAimbot::Coords()
{
	/*if (GetTickCount64() - dwStartTick3 > 160 && dwStartTick3 != 0)
	{
		std::memcpy((void*)0x60BA52, "\xC7\x86\x9C\x07\x00\x00\x00\x00\x00\x00", 10);
		std::memcpy((void*)0x60B874, "\x74\x14\x85\xC9\x74\x06\x57\xE8\x80\x61", 10); 
		std::memcpy((void*)0x6870ED, "\xE8\xDE\x2D\xF8\xFF\x8B", 5);
	}*/
	if (pAimbot->iTargetPlayer3 != -1 && g_Config.g_Aimbot.bAimbotEnabledSilent[pSAMP->getPlayers()->pLocalPlayer->byteCurrentWeapon] && GetTickCount64() - dwStartTick3 <= 160 && dwStartTick3 != 0)
	{
		CPed* pPed = CPools::GetPed(pSAMP->getPlayers()->pRemotePlayer[pAimbot->iTargetPlayer3]->pPlayerData->pSAMP_Actor->ulGTAEntityHandle);
		CVector vecBone3, vecBoneScreen3;
		Utils::getBonePosition(pPed, (ePedBones)pAimbot->iTargetBone3, &vecBone3);

		static float fDrawPosX = *reinterpret_cast<float*>(0xB6EC10);
		static float fDrawPosY = *reinterpret_cast<float*>(0xB6EC14);
		memwrapper::write_memory<std::uintptr_t*>(0x0058E264, (std::uintptr_t*)&fDrawPosX); //orig address -> 0xB6EC10 / patch address -> &fDrawPosX
		memwrapper::write_memory<std::uintptr_t*>(0x0058E254, (std::uintptr_t*)&fDrawPosY); //orig address -> 0xB6EC14 / patch address -> &fDrawPosY
		POINT pos;
		pos.x = *(int*)0xC9C040;
		pos.y = *(int*)0xC9C044;
		Utils::CalcScreenCoors(&vecBone3, &vecBoneScreen3);
		*reinterpret_cast <float*>(0xB6EC14) = vecBoneScreen3.x / pos.x;
		*reinterpret_cast <float*>(0xB6EC10) = vecBoneScreen3.y / pos.y;
	}
	if (GetTickCount64() - dwStartTick3 > 160 && dwStartTick3 !=0)
	{
		dwStartTick3 = 0;
		*reinterpret_cast <float*>(0xB6EC10) = CrossY;
		*reinterpret_cast <float*>(0xB6EC14) = CrossX;
	}
}

bool __cdecl CAimbot::hkAddBullet(CEntity* pCreator, eWeaponType weaponType, CVector vecPosition, CVector vecVelocity)
{
	if (pCreator == FindPlayerPed() && pAimbot->iTargetPlayer3 != -1 && g_Config.g_Aimbot.bAimbotEnabledSilent[34] && rand() % 100 <= g_Config.g_Aimbot.iAimbotConfig[34][SILENT])
	{
		CPed* pPed = CPools::GetPed(pSAMP->getPlayers()->pRemotePlayer[pAimbot->iTargetPlayer3]->pPlayerData->pSAMP_Actor->ulGTAEntityHandle);
		if (pPed)
		{
			CVector vecBone3;
			Utils::getBonePosition(pPed, (ePedBones)pAimbot->iTargetBone3, &vecBone3);
			vecVelocity = vecBone3 - vecPosition;

			pSecure->memcpy_safe((void*)0x736212, g_Config.g_Aimbot.bWallShot || (g_Config.g_Aimbot.bIgnoreMaxDistance && g_Config.g_Aimbot.bWallShot) ? "\x6A\x00\x6A\x00" : "\x6A\x01\x6A\x01", 4);
		}
	}
	else Memory::memcpy_safe((void*)0x736212, "\x6A\x01\x6A\x01", 4);

	return pAimbot->oAddBullet(pCreator, weaponType, vecPosition, vecVelocity);
}

float __cdecl CAimbot::hkTargetWeaponRangeMultiplier(CEntity* pVictim, CEntity* pOwner)
{
	if (pOwner == FindPlayerPed() && (g_Config.g_Aimbot.bIgnoreMaxDistance))
		return 100.f;

	return pAimbot->oTargetWeaponRangeMultiplier(pVictim, pOwner);
}

void CAimbot::Triggerbot()
{
	if (g_Config.g_Aimbot.bTriggerbot && bCrosshair && isKeyDown(g_Config.g_Hotkeys.iTrigger))
	{
		static ULONGLONG iTick = GetTickCount64();
		if (g_Config.g_Aimbot.bTriggerDelay && GetTickCount64() - iTick < (ULONGLONG)g_Config.g_Aimbot.iTriggerDelay)
			return;

		if (g_Config.g_Aimbot.bTriggerSync)
		{
			if (g_Config.g_Aimbot.bAimbotEnabledSilent[pSAMP->getPlayers()->pLocalPlayer->byteCurrentWeapon] && iTargetPlayer != -1)
			{
				pKeyHook->g_GameKeyState[BUTTON_CIRCLE] = { 0xFF, true };
				iTick = GetTickCount64();
			}
		}
		else
		{
			CVector vecCamera, vecOrigin, vecTarget;
			if (pSAMP->getPlayers()->pLocalPlayer->byteCurrentWeapon != 34)
			{
				Utils::getBonePosition(FindPlayerPed(), BONE_RIGHTWRIST, &vecOrigin);
				TheCamera.Find3rdPersonCamTargetVector(100.f, vecOrigin, &vecCamera, &vecTarget);
			}
			else
			{
				CVector vecFront = TheCamera.m_aCams[0].m_vecFront;
				vecFront.Normalise();
				vecCamera = *TheCamera.GetGameCamPosition();
				vecCamera += (vecFront * 2.0f);
				vecTarget = vecCamera + (vecFront * 100.f);
			}

			CColPoint pCollision; CEntity* pCollisionEntity = NULL;
			bool bCollision = CWorld::ProcessLineOfSight(vecCamera, vecTarget, pCollision, pCollisionEntity, !g_Config.g_Aimbot.bTriggerWallshot, !g_Config.g_Aimbot.bTriggerWallshot, true, true, true, true, false, true);
			if (bCollision && pCollisionEntity && pCollisionEntity->m_nType == ENTITY_TYPE_PED)
			{
				for (int i = 0; i < SAMP_MAX_PLAYERS; i++)
				{
					if (!pSAMP->isPlayerStreamed(i))
						continue;

					CPed* pPed = CPools::GetPed(pSAMP->getPlayers()->pRemotePlayer[i]->pPlayerData->pSAMP_Actor->ulGTAEntityHandle);
					if (!pPed || pPed == FindPlayerPed())
						continue;

					if (pCollisionEntity != pPed)
						continue;

					if (!pPed->IsAlive())
						continue;

					if (g_Config.g_Aimbot.bTeamProtect && pSAMP->getPlayerColor(i) == pSAMP->getPlayerColor(pSAMP->getPlayers()->sLocalPlayerID))
						continue;

					if (g_Config.g_Aimbot.bIgnoreAFK && pSAMP->getPlayers()->pRemotePlayer[i]->pPlayerData->iAFKState == 2)
							continue;

					float fDistanceFromEnemy = Math::vect3_dist(&pSAMP->getPlayers()->pRemotePlayer[i]->pPlayerData->pSAMP_Actor->pGTA_Ped->base.matrix[12], &pSAMP->getPlayers()->pLocalPlayer->pSAMP_Actor->pGTA_Ped->base.matrix[12]);
					if (!g_Config.g_Aimbot.bIgnoreMaxDistance && fDistanceFromEnemy > fWeaponRange[pSAMP->getPlayers()->pLocalPlayer->byteCurrentWeapon])
							continue;

					pKeyHook->g_GameKeyState[BUTTON_CIRCLE] = { 0xFF, true };
					iTick = GetTickCount64();
					break;
				}
			}
		}
	}
}