#include "D:\LEGION\LEGION\main.h"

HKEY hKey, hKey2;
LPCSTR subkey = "Korsar soft\\Legion";

void Cheat::Render()
{
	if (FrontEndMenuManager.m_bMenuActive)
		return;

	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	pAimbot->Render();
	pVisuals->Render();
	pMenu->Render();

	ImGui::EndFrame();
	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
}

void Cheat::Update()
{
	pAimbot->Update();
	Combat::Update();
	Player::Update();
	pVisuals->Update();
	pMenu->Update();
}

static DWORD WINAPI UnloadThread(HMODULE hModule)
{
	if (pMenu) delete pMenu;
	if (pTextures) delete pTextures;
	if (pSAMP) delete pSAMP;
	FreeLibraryAndExitThread(hModule, 0);
}

void Cheat::Unload()
{
	if (pMenu->bOpen)
		pSAMP->toggleSAMPCursor(0);

	if (pHooks) delete pHooks;
	if (pD3DHook) delete pD3DHook;
	if (pKeyHook) delete pKeyHook;
	if (pRakClient)delete pRakClient;	
	if (pAimbot) delete pAimbot;
	if (pVisuals)delete pVisuals;

	CreateThread(NULL, NULL, LPTHREAD_START_ROUTINE(UnloadThread), g_hModule, NULL, NULL);
}

void Cheat::Record1(int iCurrentConfig)
{
	if (iCurrentConfig != -1)
	{
		RegCreateKeyEx(HKEY_CURRENT_USER, subkey, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &hKey, NULL);
		RegCreateKeyEx(HKEY_CURRENT_USER, subkey, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &hKey2, NULL);
		DWORD value = 1;
		DWORD value2 = iCurrentConfig;
		RegSetValueEx(hKey, "Autoload", 0, REG_DWORD, reinterpret_cast<const BYTE*>(&value), sizeof(value));
		RegSetValueEx(hKey2, "CurrCfg", 0, REG_DWORD, reinterpret_cast<const BYTE*>(&value2), sizeof(value2));
		RegCloseKey(hKey);
		RegCloseKey(hKey2);
	}
}

void Cheat::Record0()
{
	RegCreateKeyEx(HKEY_CURRENT_USER, subkey, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &hKey, NULL);
	RegCreateKeyEx(HKEY_CURRENT_USER, subkey, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &hKey2, NULL);
	DWORD value = 0;
	DWORD value2 = 0;
	RegSetValueEx(hKey, "Autoload", 0, REG_DWORD, reinterpret_cast<const BYTE*>(&value), sizeof(value));
	RegSetValueEx(hKey2, "CurrCfg", 0, REG_DWORD, reinterpret_cast<const BYTE*>(&value2), sizeof(value2));
	RegCloseKey(hKey);
	RegCloseKey(hKey2);
}

void Cheat::Autoload()
{
		RegOpenKeyEx(HKEY_CURRENT_USER, subkey, 0, KEY_READ, &hKey);
		RegOpenKeyEx(HKEY_CURRENT_USER, subkey, 0, KEY_READ, &hKey2);
		
			DWORD dataSize = sizeof(DWORD);
			DWORD dataSize2 = sizeof(DWORD);
			DWORD valueType, valueType2;
			DWORD readValue = 0, readValue2 = 0;
			RegQueryValueEx(hKey, "Autoload", NULL, &valueType, reinterpret_cast<BYTE*>(&readValue), &dataSize);
			RegQueryValueEx(hKey2, "CurrCfg", NULL, &valueType2, reinterpret_cast<BYTE*>(&readValue2), &dataSize2);
			if (valueType == REG_DWORD) {

				if (readValue == 1 && readValue2 != -1)
					pConfig->Load(readValue2);
			}
			RegCloseKey(hKey);
			RegCloseKey(hKey2);
		
}
