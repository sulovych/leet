#pragma once

class CMenu
{
public:
	CMenu(IDirect3DDevice9* pDevice)
	{
		iToggle = 2;
		iCurrentTab = 0;
		WeaponTab = 0;
		iCurrentCategory = 0;
		bOpen = false;
		fFadeAlpha = 0.f;
		ImGui::CreateContext();
		ImGui::GetIO().IniFilename = NULL;
		ImGui_ImplWin32_Init(GetActiveWindow());
		ImGui_ImplDX9_Init(pDevice);
		pFont = ImGui::GetIO().Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\verdanab.ttf", 13.1f);
		pFont_M = ImGui::GetIO().Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\mvboli.ttf", 22.5f);
		Theme();
	};

	~CMenu()
	{
		ImGui_ImplDX9_Shutdown();
		ImGui_ImplWin32_Shutdown();
		ImGui::DestroyContext();
	};

	void Update();
	void Render();
	void Theme();

	int iToggle, iCurrentTab, iCurrentCategory, WeaponTab;
	bool bOpen;

	ImFont* pFont, *pFont_M;

private:
	void ActiveButton();
	void NormalButton();
	void Tooltip(const char* szText);

	float fFadeAlpha;
};

extern CMenu* pMenu;
