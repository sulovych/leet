#include "D:\LEGION\LEGION\main.h"

CVisuals* pVisuals;

float __cdecl CVisuals::hkCalculateAspectRatio()
{
	if (g_Config.g_Visuals.bAspectRatio && g_Config.g_Visuals.fAspectRatio >= 0.2f && g_Config.g_Visuals.fAspectRatio <= 2.0f && (!FrontEndMenuManager.m_bMenuAccessWidescreen || !TheCamera.m_bWideScreenOn))
	{
		pSecure->Write(0xC3EFA4, g_Config.g_Visuals.fAspectRatio);
		return g_Config.g_Visuals.fAspectRatio;
	}

	return pVisuals->oCalculateAspectRatio();
}

void CVisuals::Render()
{
	DWORD currentTime = GetTickCount64();
	frameCount++;

	// Обновление FPS каждые 1000 мс
	if (currentTime - lastTime >= 1000) {
		fps = frameCount; // Устанавливаем FPS
		frameCount = 0; // Сброс счетчика кадров
		lastTime = currentTime; // Обновляем время
	}

	if (isKeyPressed(VK_F8))
	{
		Sleep(160);
			return;
	}

	if (g_Config.g_Visuals.bNameTagsESP || g_Config.g_Visuals.bWeaponESP  || g_Config.g_Visuals.bBoneESP || g_Config.g_Visuals.bDistanceESP)
	{
		for (int i = 0; i < SAMP_MAX_PLAYERS; i++)
		{
			if (!pSAMP->isPlayerStreamed(i))
				continue;

			CPed* pPed = CPools::GetPed(pSAMP->getPlayers()->pRemotePlayer[i]->pPlayerData->pSAMP_Actor->ulGTAEntityHandle);
			if (!pPed)
				continue;

			if (g_Config.g_Visuals.bNameTagsESP || g_Config.g_Visuals.bWeaponESP)
				ESP_NameTags(i, pPed);
			if (g_Config.g_Visuals.bBoneESP)
				ESP_Bones(i, pPed);
			if (g_Config.g_Visuals.bDistanceESP)
				ESP_Distance(i, pPed);
		}
	}

	if (g_Config.g_Visuals.bDMGInformer)
	{
		for (auto i = 0; i < _countof(g_DMGInformer); i++)
		{
			if (g_DMGInformer[i].dwTick >= GetTickCount64())
			{
				CVector vecScreen;
				g_DMGInformer[i].ypos -= 1;
				Utils::CalcScreenCoors(&g_DMGInformer[i].vecPos, &vecScreen);
				if (g_DMGInformer[i].ypos < 200.f)
					continue;
				char szDamage[16];
				sprintf(szDamage, "%0.1f", fWeaponDamage[g_DMGInformer[i].iWeapon]);
				pRender->DrawString(pRender->pESPFont, szDamage, {1350, g_DMGInformer[i].ypos, 0}, (float)g_Config.g_Visuals.iFontSize, g_Config.g_Visuals.colorDMG, true);
				ImColor colorHitmarker = { 255, 0, 0, 255 };
				pRender->DrawLine(CVector(vecScreen.x - 10, vecScreen.y - 10, 0), CVector(vecScreen.x - 2.5f, vecScreen.y - 2.5f, 0), colorHitmarker, 1.1f);
				pRender->DrawLine(CVector(vecScreen.x - 10, vecScreen.y + 10, 0), CVector(vecScreen.x - 2.5f, vecScreen.y + 2.5f, 0), colorHitmarker, 1.1f);
				pRender->DrawLine(CVector(vecScreen.x + 10, vecScreen.y - 10, 0), CVector(vecScreen.x + 2.5f, vecScreen.y - 2.5f, 0), colorHitmarker, 1.1f);
				pRender->DrawLine(CVector(vecScreen.x + 10, vecScreen.y + 10, 0), CVector(vecScreen.x + 2.5f, vecScreen.y + 2.5f, 0), colorHitmarker, 1.1f);

			}
			else g_DMGInformer[i] = { };
		}			
	}
	if (g_Config.g_Visuals.bHpHud)
	{
		CPed* pPedSelf = FindPlayerPed();
		char HParr[16];
		char ARMarr[16];
		sprintf(HParr, "%.0f", pPedSelf->m_fHealth);
		sprintf(ARMarr, "%.0f", pPedSelf->m_fArmour);
		pRender->DrawString(pRender->pHPFont, HParr, { g_Config.g_Visuals.HPx, g_Config.g_Visuals.HPy, 1 }, 25, g_Config.g_Style.vecTheme[ImGuiCol_HP], true);
		if (pPedSelf->m_fArmour > 1)
			pRender->DrawString(pRender->pHPFont, ARMarr, { g_Config.g_Visuals.HPx, g_Config.g_Visuals.HPy - 53, 1 }, 25, g_Config.g_Style.vecTheme[ImGuiCol_HP], true);
	}
	if (g_Config.g_Vehicle.bSpeedometr && FindPlayerVehicle(-1, false))
	{
		CVehicle* pVehicle = FindPlayerVehicle(-1, false);
		char Sarr[16];
		sprintf(Sarr, "%.1f", sqrtf(pVehicle->m_vecMoveSpeed.x* pVehicle->m_vecMoveSpeed.x+ pVehicle->m_vecMoveSpeed.y* pVehicle->m_vecMoveSpeed.y+ pVehicle->m_vecMoveSpeed.z* pVehicle->m_vecMoveSpeed.z)*100);
		pRender->DrawString(pRender->pHPFont, Sarr, { 1735 ,668, 1 }, 25, g_Config.g_Style.vecTheme[ImGuiCol_HP], true);
	}	
	if (g_Config.g_Visuals.bFPS)
	{
		float x = 1900.0;
		float  y = 8.0;
		pRender->DrawRectFilled({ x - 25, y, 0 }, { x + 20, y + 18, 0 }, 0xFF000000);
		char szFPS[16];
		sprintf(szFPS, "%d", fps);
		pRender->DrawString(pRender->pHPFont, szFPS, { x, y, 0 }, 16, 0xFF00FF00, true);
	}
}

void CVisuals::Update()
{
	NoDrugsEffect();
	WeatherChanger();
	HPBAR160();
	NoPostFX();
	SmallIcons();
}

bool CVisuals::isPlayerVisible(int iPlayerID, bool bDistance)
{
	CPed* pPed = CPools::GetPed(pSAMP->getPlayers()->pRemotePlayer[iPlayerID]->pPlayerData->pSAMP_Actor->ulGTAEntityHandle);
	CMatrix matEnt = *pPed->GetMatrix();
	CVector vecBone = *Utils::getBonePosition(pPed, BONE_HEAD, &vecBone);
	if (!CWorld::GetIsLineOfSightClear(*TheCamera.GetGameCamPosition(), vecBone, true, false, false, true, true, false, false) || bDistance && Utils::getDistanceFromCamera(matEnt.pos) > pSAMP->getInfo()->pSettings->fNameTagsDistance)
		return false;
	return true;
}

ImColor CVisuals::getESPColor(int iPlayerID)
{
	CPed* pPed = CPools::GetPed(pSAMP->getPlayers()->pRemotePlayer[iPlayerID]->pPlayerData->pSAMP_Actor->ulGTAEntityHandle);
	return pSAMP->getPlayerColor(iPlayerID);
}

void CVisuals::ESP_NameTags(int iPlayerID, CPed* pPed)
{
	if (isPlayerVisible(iPlayerID, true))
		return;

	CVector vecHead, vecHeadScreen;
	Utils::getBonePosition(pPed, BONE_HEAD, &vecHead);
	vecHead.z += 0.2f + (Utils::getDistanceFromCamera(pPed->GetMatrix()->pos) * 0.0475f);
	Utils::CalcScreenCoors(&vecHead, &vecHeadScreen);
	if (vecHeadScreen.z < 1.f)
		return;

	if (g_Config.g_Visuals.bNameTagsESP)
	{
		if (pSAMP->getPlayers()->pRemotePlayer[iPlayerID]->pPlayerData->iAFKState == 2)
			pRender->DrawString(pRender->pESPFont, "AFK", { vecHeadScreen.x - 37.f, vecHeadScreen.y + 16.f, 0 }, 12.f, 0xFF808080, true);

		char szName[64];
		sprintf(szName, "%s (%d)", pSAMP->getPlayerName(iPlayerID), iPlayerID);
		pRender->DrawString(pRender->pESPFont, szName, vecHeadScreen, 15.f, pSAMP->getPlayerColor(iPlayerID), true);

		float fHealth = pSAMP->getPlayers()->pRemotePlayer[iPlayerID]->pPlayerData->fActorHealth;
		float fArmor = pSAMP->getPlayers()->pRemotePlayer[iPlayerID]->pPlayerData->fActorArmor;
		
		if (fHealth > 100.0f)
			fHealth = 100.0f;

		fHealth *= 40.f / 100.0f;
		fHealth -= (40.f / 2.f);

		ImColor colorHealthBar = *(ImU32*)(pSAMP->g_dwSAMP_Addr + 0x68B0C), colorHealthBarBG = *(ImU32*)(pSAMP->g_dwSAMP_Addr + 0x68B33);

		pRender->DrawRectFilled({ vecHeadScreen.x - 21.f, (fArmor > 0.0f) ? vecHeadScreen.y + 25.f : vecHeadScreen.y + 17.f, 0 }, { vecHeadScreen.x + 21.f, (fArmor > 0.0f) ? vecHeadScreen.y + 31.f : vecHeadScreen.y + 23.f, 0 }, 0xFF000000);
		pRender->DrawRectFilled({ vecHeadScreen.x - 20.f, (fArmor > 0.0f) ? vecHeadScreen.y + 26.f : vecHeadScreen.y + 18.f, 0 }, { vecHeadScreen.x + 20.f, (fArmor > 0.0f) ? vecHeadScreen.y + 30.f : vecHeadScreen.y + 22.f, 0 }, ImColor(colorHealthBarBG.Value.z, colorHealthBarBG.Value.y, colorHealthBarBG.Value.x, colorHealthBarBG.Value.w));
		pRender->DrawRectFilled({ vecHeadScreen.x - 20.f, (fArmor > 0.0f) ? vecHeadScreen.y + 26.f : vecHeadScreen.y + 18.f, 0 }, { vecHeadScreen.x + fHealth, (fArmor > 0.0f) ? vecHeadScreen.y + 30.f : vecHeadScreen.y + 22.f, 0 }, ImColor(colorHealthBar.Value.z, colorHealthBar.Value.y, colorHealthBar.Value.x, colorHealthBar.Value.w));
		

		if (fArmor > 0.0f)
		{
			ImColor colorArmorBar = *(ImU32*)(pSAMP->g_dwSAMP_Addr + 0x68DD5), colorArmorBarBG = *(ImU32*)(pSAMP->g_dwSAMP_Addr + 0x68E00);

			if (fArmor > 100.0f)
				fArmor = 100.0f;

			fArmor *= 40.f / 100.0f;
			fArmor -= (40.f / 2);

			pRender->DrawRectFilled({ vecHeadScreen.x - 21.f, vecHeadScreen.y + 17.f, 0 }, { vecHeadScreen.x + 21.f, vecHeadScreen.y + 23.f, 0 }, 0xFF000000);
			pRender->DrawRectFilled({ vecHeadScreen.x - 20.f, vecHeadScreen.y + 18.f, 0 }, { vecHeadScreen.x + 20.f, vecHeadScreen.y + 22.f, 0 }, ImColor(colorArmorBarBG.Value.z, colorArmorBarBG.Value.y, colorArmorBarBG.Value.x, colorArmorBarBG.Value.w));
			pRender->DrawRectFilled({ vecHeadScreen.x - 20.f, vecHeadScreen.y + 18.f, 0 }, { vecHeadScreen.x + fArmor, vecHeadScreen.y + 22.f, 0 }, ImColor(colorArmorBar.Value.z, colorArmorBar.Value.y, colorArmorBar.Value.x, colorArmorBar.Value.w));
		}
	}

	if (g_Config.g_Visuals.bWeaponESP)
	{
		ID3DXSprite* pSprite = pSAMP->getDeathList()->pSprite;
		ID3DXFont* pWeaponFont = pSAMP->getDeathList()->pWeaponFont1;
		RECT rect = { (LONG)vecHeadScreen.x + 20, (LONG)vecHeadScreen.y + 16, (LONG)vecHeadScreen.y + 1, (LONG)vecHeadScreen.y + 1 };

		pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
		pWeaponFont->DrawText(pSprite, "G", -1, &rect, DT_NOCLIP | DT_LEFT, 0xFF000000);
		pWeaponFont->DrawText(pSprite, pSAMP->getWeaponSpriteID(pPed->m_aWeapons[pPed->m_nActiveWeaponSlot].m_nType), -1, &rect, DT_NOCLIP | DT_LEFT, 0xFFFFFFFF);
		pSprite->End();
	}
}

void CVisuals::ESP_Bones(int iPlayerID, CPed* pPed)
{
	CVector vecBone[55];
	for (int iBone = BONE_PELVIS1; iBone <= BONE_RIGHTFOOT; iBone++)
	{
		switch (iBone)
		{
		case 7 : case 6: case 4: case 22: case 32: case 23: case 33: case 24: case 34: case 3: case 2: case 52: case 42: case 53: case 43: case 54: case 44: case 51: case 41: case 8:
			Utils::getBonePosition(pPed, (ePedBones)iBone, &vecBone[iBone]);
			break;
		}
	}

	ImColor colorESP = g_Config.g_Visuals.bClistBones ? getESPColor(iPlayerID) : ImColor(0xFFFFFFFF);
	pRender->D3DLine(vecBone[BONE_HEAD1], vecBone[BONE_HEAD2], colorESP, g_Config.g_Visuals.fESPThickness);
	pRender->D3DLine(vecBone[BONE_HEAD], vecBone[BONE_HEAD2], colorESP, g_Config.g_Visuals.fESPThickness);
	pRender->D3DLine(vecBone[BONE_HEAD], vecBone[BONE_HEAD1], colorESP, g_Config.g_Visuals.fESPThickness);
	pRender->D3DLine(vecBone[BONE_HEAD], vecBone[BONE_UPPERTORSO], colorESP, g_Config.g_Visuals.fESPThickness);
	pRender->D3DLine(vecBone[BONE_UPPERTORSO], vecBone[BONE_RIGHTSHOULDER], colorESP, g_Config.g_Visuals.fESPThickness);
	pRender->D3DLine(vecBone[BONE_UPPERTORSO], vecBone[BONE_LEFTSHOULDER], colorESP, g_Config.g_Visuals.fESPThickness);
	pRender->D3DLine(vecBone[BONE_LEFTSHOULDER], vecBone[BONE_LEFTELBOW], colorESP, g_Config.g_Visuals.fESPThickness);
	pRender->D3DLine(vecBone[BONE_RIGHTSHOULDER], vecBone[BONE_RIGHTELBOW], colorESP, g_Config.g_Visuals.fESPThickness);
	pRender->D3DLine(vecBone[BONE_LEFTELBOW], vecBone[BONE_LEFTWRIST], colorESP, g_Config.g_Visuals.fESPThickness);
	pRender->D3DLine(vecBone[BONE_RIGHTELBOW], vecBone[BONE_RIGHTWRIST], colorESP, g_Config.g_Visuals.fESPThickness);
	pRender->D3DLine(vecBone[BONE_UPPERTORSO], vecBone[BONE_SPINE1], colorESP, g_Config.g_Visuals.fESPThickness);
	pRender->D3DLine(vecBone[BONE_SPINE1], vecBone[BONE_PELVIS], colorESP, g_Config.g_Visuals.fESPThickness);
	pRender->D3DLine(vecBone[BONE_RIGHTHIP], vecBone[BONE_RIGHTKNEE], colorESP, g_Config.g_Visuals.fESPThickness);
	pRender->D3DLine(vecBone[BONE_LEFTHIP], vecBone[BONE_LEFTKNEE], colorESP, g_Config.g_Visuals.fESPThickness);
	pRender->D3DLine(vecBone[BONE_LEFTHIP], vecBone[BONE_PELVIS], colorESP, g_Config.g_Visuals.fESPThickness);
	pRender->D3DLine(vecBone[BONE_RIGHTHIP], vecBone[BONE_PELVIS], colorESP, g_Config.g_Visuals.fESPThickness);
	pRender->D3DLine(vecBone[BONE_RIGHTKNEE], vecBone[BONE_RIGHTANKLE], colorESP, g_Config.g_Visuals.fESPThickness);
	pRender->D3DLine(vecBone[BONE_LEFTKNEE], vecBone[BONE_LEFTANKLE], colorESP, g_Config.g_Visuals.fESPThickness);
	pRender->D3DLine(vecBone[BONE_RIGHTANKLE], vecBone[BONE_RIGHTFOOT], colorESP, g_Config.g_Visuals.fESPThickness);
	pRender->D3DLine(vecBone[BONE_LEFTANKLE], vecBone[BONE_LEFTFOOT], colorESP, g_Config.g_Visuals.fESPThickness);
}

void CVisuals::ESP_Distance(int iPlayerID, CPed* pPed)
{
	CVector vecFoot = pPed->GetPosition(), vecFootScreen;
	vecFoot.z -= 1.2f;

	Utils::CalcScreenCoors(&vecFoot, &vecFootScreen);
	if (vecFootScreen.z < 1.f)
		return;

	float distance = Utils::getDistance(pPed->GetPosition()); 
	char szDistance[32];
	sprintf(szDistance, "%.1fm", distance);

	if (distance > 35.28)
	pRender->DrawString(pRender->pHPFont, szDistance, vecFootScreen, 18.f, 0xFF00FF00, true);
	else 
	pRender->DrawString(pRender->pHPFont, szDistance, vecFootScreen, 18.f, 0xFFFFFFFF, true);
}

void CVisuals::NoDrugsEffect()
{
	static bool bDrugEffect = false;
	if (g_Config.g_Visuals.bNoDrugsEffect)
	{
		pSecure->memcpy_safe((void*)0x71D76C, "\x90\x90\x90\x90\x90", 5);
		bDrugEffect = true;
	}
	else if (bDrugEffect)
	{
		Memory::memcpy_safe((void*)0x71D76C, "\xA3\x58\x3C\xC7\x00", 5);
		bDrugEffect = false;
	}
}

void CVisuals::WeatherChanger()
{
	if (g_Config.g_Visuals.bWeatherChanger)
		CWeather::ForceWeatherNow(g_Config.g_Visuals.iWeather);

	if (g_Config.g_Visuals.bTimeChanger)
		CClock::SetGameClock(g_Config.g_Visuals.iTime, 0, 0);
}

void CVisuals::HPBAR160()
{
	if (g_Config.g_Visuals.b160hp)
		*reinterpret_cast<float*>(12030944) = 910.4;
	else *reinterpret_cast<float*>(12030944) = 569.0;
}

void CVisuals::NoPostFX()
{
	static bool bFPSBoost = false;
	if (g_Config.g_Visuals.bNoPostFX)
	{
		ImGui::GetStyle().AntiAliasedLines = false;
		ImGui::GetStyle().AntiAliasedFill = false;
		pSecure->memcpy_safe((void*)0x53E227, "\xC3", 1);
		bFPSBoost = true;
	}
	else if (bFPSBoost)
	{
		ImGui::GetStyle().AntiAliasedLines = true;
		ImGui::GetStyle().AntiAliasedFill = true;
		Memory::memcpy_safe((void*)0x53E227, "\xE9", 1);
		bFPSBoost = false;
	}
}

template<typename T>
void WriteMemory(void* addr, T value) {
	DWORD oldProt = 0;
	VirtualProtect(addr, sizeof(T), PAGE_EXECUTE_READWRITE, &oldProt);
	*reinterpret_cast<T*>(addr) = value;
	VirtualProtect(addr, sizeof(T), oldProt, NULL);
}

float size = g_Config.g_Visuals.oIcon * 8;
float playersSizeX = g_Config.g_Visuals.pIcon / 640;
float playersSizeY = playersSizeX * 1.42857152;
float borderX = playersSizeX + 0.0001;
float borderY = playersSizeY + 0.0001;

float size1 = 1.0 * 8;
float playersSizeX1 = 1.0 / 640;
float playersSizeY1 = playersSizeX1 * 1.42857152;
float borderX1 = playersSizeX1 + 0.00001;
float borderY1 = playersSizeY1 + 0.00001;

void CVisuals::SmallIcons()
{
	if (g_Config.g_Visuals.bSmallIcons)
	{
		// Map Icons
		WriteMemory<void*>(reinterpret_cast<void*>(0x586047), &size);
		WriteMemory<void*>(reinterpret_cast<void*>(0x586060), &size);

		// radar_centre
		WriteMemory<void*>(reinterpret_cast<void*>(0x5886DC), &size);

		// Box Player
		WriteMemory<void*>(reinterpret_cast<void*>(0x584192), &playersSizeX); // PlayerBoxX
		WriteMemory<void*>(reinterpret_cast<void*>(0x5841B2), &playersSizeY); // PlayerBoxY
		WriteMemory<void*>(reinterpret_cast<void*>(0x58410D), &borderX); // PlayerBoxBorderX
		WriteMemory<void*>(reinterpret_cast<void*>(0x58412D), &borderY); // PlayerBoxBorderY

		// Down Triangle
		WriteMemory<void*>(reinterpret_cast<void*>(0x5842E8), &playersSizeX); // DownTriangleX
		WriteMemory<void*>(reinterpret_cast<void*>(0x5842C8), &playersSizeY); // DownTriangleY
		WriteMemory<void*>(reinterpret_cast<void*>(0x58424B), &borderX); // DownTriangleBorderX
		WriteMemory<void*>(reinterpret_cast<void*>(0x584209), &borderY); // DownTrianglexBorderY

		// Up Triangle
		WriteMemory<void*>(reinterpret_cast<void*>(0x584436), &playersSizeX); // UpTriangleX
		WriteMemory<void*>(reinterpret_cast<void*>(0x58440E), &playersSizeY); // UpTriangleY
		WriteMemory<void*>(reinterpret_cast<void*>(0x58439E), &borderX); // UpTriangleBorderX
		WriteMemory<void*>(reinterpret_cast<void*>(0x584348), &borderY); // UpTriangleBorderY
	}
	else
	{
		// Map Icons
		WriteMemory<void*>(reinterpret_cast<void*>(0x586047), &size1);
		WriteMemory<void*>(reinterpret_cast<void*>(0x586060), &size1);

		// radar_centre
		WriteMemory<void*>(reinterpret_cast<void*>(0x5886DC), &size1);

		// Box Player
		WriteMemory<void*>(reinterpret_cast<void*>(0x584192), &playersSizeX1); // PlayerBoxX
		WriteMemory<void*>(reinterpret_cast<void*>(0x5841B2), &playersSizeY1); // PlayerBoxY
		WriteMemory<void*>(reinterpret_cast<void*>(0x58410D), &borderX1); // PlayerBoxBorderX
		WriteMemory<void*>(reinterpret_cast<void*>(0x58412D), &borderY1); // PlayerBoxBorderY

		// Down Triangle
		WriteMemory<void*>(reinterpret_cast<void*>(0x5842E8), &playersSizeX1); // DownTriangleX
		WriteMemory<void*>(reinterpret_cast<void*>(0x5842C8), &playersSizeY1); // DownTriangleY
		WriteMemory<void*>(reinterpret_cast<void*>(0x58424B), &borderX1); // DownTriangleBorderX
		WriteMemory<void*>(reinterpret_cast<void*>(0x584209), &borderY1); // DownTrianglexBorderY

		// Up Triangle
		WriteMemory<void*>(reinterpret_cast<void*>(0x584436), &playersSizeX1); // UpTriangleX
		WriteMemory<void*>(reinterpret_cast<void*>(0x58440E), &playersSizeY1); // UpTriangleY
		WriteMemory<void*>(reinterpret_cast<void*>(0x58439E), &borderX1); // UpTriangleBorderX
		WriteMemory<void*>(reinterpret_cast<void*>(0x584348), &borderY1); // UpTriangleBorderY
	}
}