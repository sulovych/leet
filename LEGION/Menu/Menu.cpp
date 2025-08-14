#include "D:\LEGION\LEGION\main.h"
#include "../ImGui/imgui_internal.h"

CMenu* pMenu;
std::vector<int> idList;

void CMenu::Update()
{
	if (!FrontEndMenuManager.m_bMenuActive)
	{
		if (bOpen)
		{
			fFadeAlpha = min(fFadeAlpha + ImGui::GetIO().DeltaTime * 6.0f, 1.0f);
			ImGui::GetStyle().Alpha = fFadeAlpha;
			pSAMP->toggleSAMPCursor(1);
			ImGui::GetIO().MouseDrawCursor = true;
		}
		else if (iToggle == 0)
		{
			fFadeAlpha = 0.f;
			pSAMP->toggleSAMPCursor(0);
			ImGui::GetIO().MouseDrawCursor = false;
			iToggle = 3;
		}
	}
	else if (bOpen) pSAMP->toggleSAMPCursor(0);
}

void CMenu::Theme()
{
	ImGuiStyle& style = ImGui::GetStyle();

	style.Alpha = 1.0f;
	style.WindowPadding = { 8, 8 };
	style.WindowMinSize = { 32, 32 };
	style.PopupRounding = 3.3f;
	style.WindowTitleAlign = { 0.5f, 0.5f };
	style.FramePadding = { 4, 3 };
	style.ChildRounding = 3.3f;
	style.FrameRounding = 3.5f;
	style.ItemSpacing = { 8, 4 };
	style.TouchExtraPadding = { 0, 0 };
	style.IndentSpacing = 21.0f;
	style.ColumnsMinSpacing = 0.0f;
	style.ScrollbarSize = 6.0f;
	style.ScrollbarRounding = 0.0f;
	style.GrabMinSize = 5.0f;
	style.GrabRounding = 2.7f;
	style.ButtonTextAlign = { 0.5f, 0.5f };
	style.DisplayWindowPadding = { 22, 22 };
	style.DisplaySafeAreaPadding = { 4, 4 };
	style.AntiAliasedLines = true;
	style.AntiAliasedFill = true;
	style.CurveTessellationTol = 1.f;

	HKEY hKey;
	LPCSTR subkey = "Korsar soft\\Legion";
	RegOpenKeyEx(HKEY_CURRENT_USER, subkey, 0, KEY_READ, &hKey);
	DWORD dataSize = sizeof(DWORD);
	DWORD valueType;
	DWORD readValue = 0;
	RegQueryValueEx(hKey, "Autoload", NULL, &valueType, reinterpret_cast<BYTE*>(&readValue), &dataSize);
		if (readValue != 1)
		{
			g_Config.g_Style.vecTheme[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
			g_Config.g_Style.vecTheme[ImGuiCol_TextDisabled] = ImVec4(0.604f, 0.604f, 0.604f, 1.00f);
			g_Config.g_Style.vecTheme[ImGuiCol_WindowBg] = ImVec4(0.087f, 0.087f, 0.087f, 0.983f);
			g_Config.g_Style.vecTheme[ImGuiCol_ChildBg] = ImVec4(0.148f, 0.166f, 0.219f, 0.433f);
			g_Config.g_Style.vecTheme[ImGuiCol_PopupBg] = ImVec4(0.129f, 0.172f, 0.175f, 1.0f);
			g_Config.g_Style.vecTheme[ImGuiCol_Border] = ImVec4(0.202f, 0.202f, 0.202f, 0.00f);
			g_Config.g_Style.vecTheme[ImGuiCol_BorderShadow] = ImVec4(0.0f, 0.0f, 0.0f, 1.00f);
			g_Config.g_Style.vecTheme[ImGuiCol_FrameBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.444f);
			g_Config.g_Style.vecTheme[ImGuiCol_FrameBgHovered] = ImVec4(0.0f, 0.0f, 0.0f, 0.443f);
			g_Config.g_Style.vecTheme[ImGuiCol_FrameBgActive] = ImVec4(0.081f, 0.081f, 0.081f, 0.443f);
			g_Config.g_Style.vecTheme[ImGuiCol_TitleBg] = ImVec4(0.0f, 0.0f, 0.0f, 1.00f);
			g_Config.g_Style.vecTheme[ImGuiCol_TitleBgActive] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
			g_Config.g_Style.vecTheme[ImGuiCol_TitleBgCollapsed] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
			g_Config.g_Style.vecTheme[ImGuiCol_MenuBarBg] = ImVec4(0.0043f, 1.0f, 0.908f, 0.092f);
			g_Config.g_Style.vecTheme[ImGuiCol_ScrollbarBg] = ImVec4(0.483f, 0.483f, 0.483f, 0.175f);
			g_Config.g_Style.vecTheme[ImGuiCol_ScrollbarGrab] = ImVec4(0.075f, 0.653f, 0.578f, 1.00f);
			g_Config.g_Style.vecTheme[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.136f, 0.523f, 0.538f, 1.00f);
			g_Config.g_Style.vecTheme[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.003f, 0.791f, 0.638f, 1.00f);
			g_Config.g_Style.vecTheme[ImGuiCol_CheckMark] = ImVec4(1.00f, 0.0f, 0.0f, 0.351f);
			g_Config.g_Style.vecTheme[ImGuiCol_SliderGrab] = ImVec4(0.137f, 0.537f, 0.446f, 1.00f);
			g_Config.g_Style.vecTheme[ImGuiCol_SliderGrabActive] = ImVec4(0.173f, 0.686f, 0.502f, 1.00f);
			g_Config.g_Style.vecTheme[ImGuiCol_Button] = ImVec4(0.043f, 1.0f, 0.91f, 0.094f);
			g_Config.g_Style.vecTheme[ImGuiCol_ButtonHovered] = ImVec4(0.212f, 0.791f, 0.602f, 0.329f);
			g_Config.g_Style.vecTheme[ImGuiCol_ButtonActive] = ImVec4(0.041f, 0.343f, 0.472f, 0.538f);
			g_Config.g_Style.vecTheme[ImGuiCol_Header] = ImVec4(0.188f, 0.227f, 0.296f, 1.00f);
			g_Config.g_Style.vecTheme[ImGuiCol_HeaderHovered] = ImVec4(0.160f, 0.560f, 0.427f, 0.208f);
			g_Config.g_Style.vecTheme[ImGuiCol_HeaderActive] = ImVec4(0.212f, 0.792f, 0.6f, 0.208f);
			g_Config.g_Style.vecTheme[ImGuiCol_Separator] = ImVec4(0.0f, 0.0f, 0.0f, 0.5f);
			g_Config.g_Style.vecTheme[ImGuiCol_SeparatorHovered] = ImVec4(0.0f, 0.0f, 0.0f, 0.5f);
			g_Config.g_Style.vecTheme[ImGuiCol_SeparatorActive] = ImVec4(0.0f, 0.0f, 0.0f, 0.5f);
			g_Config.g_Style.vecTheme[ImGuiCol_ResizeGrip] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
			g_Config.g_Style.vecTheme[ImGuiCol_ResizeGripHovered] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
			g_Config.g_Style.vecTheme[ImGuiCol_ResizeGripActive] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
			g_Config.g_Style.vecTheme[ImGuiCol_Tab] = ImVec4(0.149f, 0.165f, 0.220f, 0.431f);
			g_Config.g_Style.vecTheme[ImGuiCol_TabHovered] = ImVec4(0.149f, 0.165f, 0.220f, 0.431f);
			g_Config.g_Style.vecTheme[ImGuiCol_TabActive] = ImVec4(0.149f, 0.165f, 0.220f, 0.431f);
			g_Config.g_Style.vecTheme[ImGuiCol_TabUnfocused] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
			g_Config.g_Style.vecTheme[ImGuiCol_TabUnfocusedActive] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
			g_Config.g_Style.vecTheme[ImGuiCol_TextSelectedBg] = ImVec4(0.212f, 0.792f, 0.6f, 0.307f);
			g_Config.g_Style.vecTheme[ImGuiCol_CheckBoxBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.411f);
			g_Config.g_Style.vecTheme[ImGuiCol_Logo] = ImVec4(0.267f, 0.901f, 0.673f, 1.00f);
			g_Config.g_Style.vecTheme[ImGuiCol_HP] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
		}			
	RegCloseKey(hKey);

	for (int i = 0; i < ImGuiCol_COUNT; i++)
		ImGui::GetStyle().Colors[i] = g_Config.g_Style.vecTheme[i];
}

void CMenu::ActiveButton()
{
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.f, 0.f, 0.f, 0.f));
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.f, 0.f, 0.f, 0.f));
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.f, 0.f, 0.f, 0.f));
	ImGui::PushStyleColor(ImGuiCol_Text, ImGui::GetStyleColorVec4(ImGuiCol_Text));
}

void CMenu::NormalButton()
{
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.f, 0.f, 0.f, 0.f));
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.f, 0.f, 0.f, 0.f));
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.f, 0.f, 0.f, 0.f));
	ImGui::PushStyleColor(ImGuiCol_Text, ImGui::GetStyleColorVec4(ImGuiCol_TextDisabled));
}

void CMenu::Tooltip(const char* szText)
{
	if (strlen(szText) && ImGui::IsItemHovered())
	{
		ImGui::BeginTooltip();
		ImGui::TextUnformatted(szText);
		ImGui::EndTooltip();
	}
}

void CMenu::Render()
{
	if (!pMenu->bOpen)
		return;

	ImGui::SetNextWindowSize({ 665, 372 });
	ImGui::SetNextWindowPos({ ImGui::GetIO().DisplaySize.x * 0.5f, ImGui::GetIO().DisplaySize.y * 0.5f }, ImGuiCond_Once, { 0.5f, 0.5f });

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 16, 16 });
	ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, { 1, 1 });
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 7.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 4.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, { 14, -10 });

	if (ImGui::Begin("LEGION", &bOpen, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar))
	{
		ImGui::BeginGroup();
		ImGui::SetCursorPosX(3); ImGui::SetCursorPosY(14);
		ImGui::Image(pTextures->tLogo, { 109, 21 }, { 0, 0 }, { 1, 1 }, ImGui::GetStyle().Colors[ImGuiCol_Logo]); 
		ImGui::PushFont(pFont_M);

		ImGui::SetCursorPosX(12 + 105); ImGui::SetCursorPosY(14);
		ImGui::TabButton("##Weapon", &iCurrentTab, 0, { 90, 35 }); ImGui::SetCursorPosX(15 + 105); ImGui::SetCursorPosY(20); ImGui::Image(pTextures->tAIM, { 24, 24 }, { 0, 0 }, { 1, 1 }, ImGui::GetStyle().Colors[ImGuiCol_Text]);
		 ImGui::SameLine(); ImGui::TextDisabled("Weapon");
		
		ImGui::SameLine(91 + 105); ImGui::SetCursorPosY(14);
		ImGui::TabButton("##Player", &iCurrentTab, 1, { 90, 35 }); ImGui::SameLine(93 + 105); ImGui::SetCursorPosY(20); ImGui::Image(pTextures->tPlayer, { 24, 24 }, { 0, 0 }, { 1, 1 }, ImGui::GetStyle().Colors[ImGuiCol_Text]);
		ImGui::SameLine(); ImGui::TextDisabled("Player");
		
		ImGui::SameLine(186 + 105); ImGui::SetCursorPosY(14);
		ImGui::TabButton("##Car", &iCurrentTab, 2, { 90, 35 }); ImGui::SameLine(188 + 105); ImGui::SetCursorPosY(20); ImGui::Image(pTextures->tCar, { 29, 26 }, { 0, 0 }, { 1, 1 }, ImGui::GetStyle().Colors[ImGuiCol_Text]);
		 ImGui::SameLine(); ImGui::TextDisabled("Vehicle");
		
		ImGui::SameLine(281 + 105); ImGui::SetCursorPosY(14);
		ImGui::TabButton("##Visual", &iCurrentTab, 3, { 90, 35 }); ImGui::SameLine(283 + 105); ImGui::SetCursorPosY(20); ImGui::Image(pTextures->tVisual, { 28, 28 }, { 0, 0 }, { 1, 1 }, ImGui::GetStyle().Colors[ImGuiCol_Text]);
		 ImGui::SameLine(); ImGui::TextDisabled("Visual");
		
		ImGui::SameLine(376 + 105); ImGui::SetCursorPosY(14);
		ImGui::TabButton("##Config", &iCurrentTab, 4, { 90, 35 });  ImGui::SameLine(378 + 105); ImGui::SetCursorPosY(20); ImGui::Image(pTextures->tExtra, { 28, 28 }, { 0, 0 }, { 1, 1 }, ImGui::GetStyle().Colors[ImGuiCol_Text]);
		 ImGui::SameLine(); ImGui::TextDisabled("Config");

		ImGui::PopFont();
		ImGui::EndGroup();
		ImGui::PopStyleVar(5);

		switch (iCurrentTab)
		{
		case 0:
		{
			ImGui::SetCursorPosX(12); ImGui::SetCursorPosY(54);
			ImGui::TabButton("##Pistol", &WeaponTab, 0, { 101, 35 });  ImGui::SameLine(); ImGui::SetCursorPosX(14); ImGui::SetCursorPosY(60); ImGui::Image(pTextures->tPistol, { 57, 28 }, { 0, 0 }, { 1, 1 }, ImGui::GetStyle().Colors[ImGuiCol_Text]); 
			ImGui::SetCursorPosX(12); ImGui::SetCursorPosY(94);
			ImGui::TabButton("##Pumpgun", &WeaponTab, 1, { 101, 35 });  ImGui::SameLine(); ImGui::SetCursorPosX(14); ImGui::SetCursorPosY(100); ImGui::Image(pTextures->tPumpgun, { 90, 27 }, { 0, 0 }, { 1, 1 }, ImGui::GetStyle().Colors[ImGuiCol_Text]);
			ImGui::SetCursorPosX(12); ImGui::SetCursorPosY(134);
			ImGui::TabButton("##SMG", &WeaponTab, 2, { 101, 35 });  ImGui::SameLine(); ImGui::SetCursorPosX(14); ImGui::SetCursorPosY(140); ImGui::Image(pTextures->tSMG, { 70, 27 }, { 0, 0 }, { 1, 1 }, ImGui::GetStyle().Colors[ImGuiCol_Text]);
			ImGui::SetCursorPosX(12); ImGui::SetCursorPosY(174);
			ImGui::TabButton("##Rifle", &WeaponTab, 3, { 101, 35 });  ImGui::SameLine(); ImGui::SetCursorPosX(14); ImGui::SetCursorPosY(180); ImGui::Image(pTextures->tRifle, { 90, 27 }, { 0, 0 }, { 1, 1 }, ImGui::GetStyle().Colors[ImGuiCol_Text]);
			ImGui::SetCursorPosX(12); ImGui::SetCursorPosY(214);
			ImGui::TabButton("##Sniper", &WeaponTab, 4, { 101, 35 });  ImGui::SameLine(); ImGui::SetCursorPosX(14); ImGui::SetCursorPosY(220); ImGui::Image(pTextures->tSniper, { 90, 27 }, { 0, 0 }, { 1, 1 }, ImGui::GetStyle().Colors[ImGuiCol_Text]);


			ImGui::SetCursorPosY(54);
			ImGui::SetCursorPosX(116);
			ImGui::BeginGroup();
			ImGui::BeginChild("##Aim", { 190, 300 }, true, ImGuiWindowFlags_NoTitleBar);
			{
				switch (WeaponTab)
				{
					case 0:
					case 1:
					case 2:
					case 3:
					case 4:
					{
					for (auto i : mapWeapons)
					{
						if (i.second.iCategory != WeaponTab)
							continue;
						if (i.first == 24 || i.first == 25 || i.first == 29 || i.first == 31 || i.first == 33)
						{
							ImGui::Checkbox("Vector Aim", &g_Config.g_Aimbot.bAimbotEnabledSmooth[i.first]); ImGui::SameLine(110); ImGui::TextDisabled("(?)"); Tooltip("Only with crosshair"); ImGui::SameLine(160);  ImGui::Image(pTextures->tConfig, { 19, 19 }, { 0, 0 }, { 1, 1 }, ImGui::GetStyle().Colors[ImGuiCol_Text]);  ImGui::SameLine(160); ImGui::Button("##SettingsSmooth", { 20, 0 });
							if (ImGui::BeginPopupContextItem(0, 0))
							{
								ImGui::Checkbox("Aim on key", &g_Config.g_Aimbot.bSmoothIsFire);
								ImGui::Checkbox("Disable in stun", &g_Config.g_Aimbot.bIsStun);
								ImGui::Checkbox("Use Y axis", &g_Config.g_Aimbot.bSmoothLockY);
								ImGui::Checkbox("Stop on body", &g_Config.g_Aimbot.bStopOnBody);
								ImGui::EndPopup();
							}
							ImGui::Spacing(); ImGui::Spacing();
							ImGui::SliderInt("Vector FOV", &g_Config.g_Aimbot.iAimbotConfig[i.first][FOV_SMOOTH], 1, 200, "%d px");
							if (ImGui::IsItemActive())
								ImGui::GetOverlayDrawList()->AddCircle({ pAimbot->vecCrosshair.x, pAimbot->vecCrosshair.y }, g_Config.g_Aimbot.iAimbotConfig[i.first][FOV_SMOOTH] * 1.5f, (ImColor{ 0.f, 1.f, 0.f }), 64, g_Config.g_Aimbot.fOutlineThickness);
							ImGui::Dummy(ImVec2(0.0f, 2.0f));
							ImGui::SliderInt("Smoothness##vector", &g_Config.g_Aimbot.iAimbotConfig[i.first][SMOOTH], 1, 100, "%d%%");
							ImGui::Spacing(); ImGui::Separator(); ImGui::Spacing();
							ImGui::Checkbox("Flickshot", &g_Config.g_Aimbot.bAimbotEnabledFlick[i.first]); ImGui::SameLine(110); ImGui::TextDisabled("(?)"); Tooltip("Only with No crosshair"); ImGui::SameLine(160); ImGui::Image(pTextures->tConfig, { 19, 19 }, { 0, 0 }, { 1, 1 }, ImGui::GetStyle().Colors[ImGuiCol_Text]);  ImGui::SameLine(160); ImGui::Button("##SettingsFlick", { 20, 0 });
							if (ImGui::BeginPopupContextItem(0, 0))
							{
								ImGui::Checkbox("Aim on key", &g_Config.g_Aimbot.bSmoothIsFire);
								ImGui::Checkbox("Disable in stun", &g_Config.g_Aimbot.bIsStun);
								ImGui::Checkbox("Use Y axis", &g_Config.g_Aimbot.bSmoothLockY2);
								ImGui::Checkbox("Stop on body", &g_Config.g_Aimbot.bStopOnBody2);
								ImGui::EndPopup();
							}
							ImGui::Spacing(); ImGui::Spacing();
							ImGui::SliderInt("Flick FOV", &g_Config.g_Aimbot.iAimbotConfig[i.first][FOV_FLICK], 1, 350, "%d px");
							if (ImGui::IsItemActive())
								ImGui::GetOverlayDrawList()->AddCircle({ pAimbot->vecCrosshair.x, pAimbot->vecCrosshair.y }, g_Config.g_Aimbot.iAimbotConfig[i.first][FOV_FLICK] * 1.5f, (ImColor{ 0.f, 1.f, 1.f }), 64, g_Config.g_Aimbot.fOutlineThickness);
							ImGui::Dummy(ImVec2(0.0f, 2.0f));
							ImGui::SliderInt("Smoothness##flick", &g_Config.g_Aimbot.iAimbotConfig[i.first][FLICK], 1, 100, "%d%%");
							ImGui::Spacing();  ImGui::Separator(); ImGui::Spacing();

							ImGui::Checkbox("Silent Aim", &g_Config.g_Aimbot.bAimbotEnabledSilent[i.first]);  ImGui::SameLine(160); ImGui::Image(pTextures->tConfig, { 19, 19 }, { 0, 0 }, { 1, 1 }, ImGui::GetStyle().Colors[ImGuiCol_Text]);  ImGui::SameLine(160); ImGui::Button("##SettingsSilent", { 20, 0 });
							if (ImGui::BeginPopupContextItem(0, 0))
							{
								ImGui::Checkbox("Legit silent", &g_Config.g_Aimbot.bDisable1st); ImGui::SameLine(130); ImGui::TextDisabled("(?)"); Tooltip("Disable when crosshair is not expanded");
								ImGui::Checkbox("Set target", &g_Config.g_Aimbot.bGTrinagle); ImGui::SameLine(130); ImGui::TextDisabled("(?)"); Tooltip("Set green triangle over the player");
								ImGui::EndPopup();
							}
							ImGui::Spacing(); ImGui::Spacing();
							ImGui::SliderInt("Silent FOV", &g_Config.g_Aimbot.iAimbotConfig[i.first][FOV_SILENT], 1, 150, "%d px");
							if (ImGui::IsItemActive())
								ImGui::GetOverlayDrawList()->AddCircle({ pAimbot->vecCrosshair.x, pAimbot->vecCrosshair.y }, g_Config.g_Aimbot.iAimbotConfig[i.first][FOV_SILENT] * 1.5f, (ImColor{ 1.f, 0.f, 0.f }), 64, g_Config.g_Aimbot.fOutlineThickness);
							ImGui::Dummy(ImVec2(0.0f, 2.0f));
							ImGui::SliderInt("Hitchance", &g_Config.g_Aimbot.iAimbotConfig[i.first][SILENT], 0, 100, "%d%%", ImGuiSliderFlags_ClampOnInput);
						
							for (auto j : mapWeapons)
							{
								if (j.second.iCategory == WeaponTab && j.first != i.first)
								{
									g_Config.g_Aimbot.bAimbotEnabledSmooth[j.first] = g_Config.g_Aimbot.bAimbotEnabledSmooth[i.first];
									g_Config.g_Aimbot.iAimbotConfig[j.first][FOV_SMOOTH] = g_Config.g_Aimbot.iAimbotConfig[i.first][FOV_SMOOTH];
									g_Config.g_Aimbot.iAimbotConfig[j.first][SMOOTH] = g_Config.g_Aimbot.iAimbotConfig[i.first][SMOOTH];
									g_Config.g_Aimbot.bAimbotEnabledFlick[j.first] = g_Config.g_Aimbot.bAimbotEnabledFlick[i.first];
									g_Config.g_Aimbot.iAimbotConfig[j.first][FOV_FLICK] = g_Config.g_Aimbot.iAimbotConfig[i.first][FOV_FLICK];
									g_Config.g_Aimbot.iAimbotConfig[j.first][FLICK] = g_Config.g_Aimbot.iAimbotConfig[i.first][FLICK];
									g_Config.g_Aimbot.bAimbotEnabledSilent[j.first] = g_Config.g_Aimbot.bAimbotEnabledSilent[i.first];
									g_Config.g_Aimbot.iAimbotConfig[j.first][FOV_SILENT] = g_Config.g_Aimbot.iAimbotConfig[i.first][FOV_SILENT];
									g_Config.g_Aimbot.iAimbotConfig[j.first][SILENT] = g_Config.g_Aimbot.iAimbotConfig[i.first][SILENT];
								}
							}
						}
					}
					break;
					}
				}
				ImGui::EndChild();
			}
			ImGui::EndGroup();

			ImGui::SameLine();
			ImGui::BeginGroup();
			ImGui::BeginChild("##Combat Assistance", { 190, 300 }, true, ImGuiWindowFlags_NoTitleBar);
			{
				ImGui::Checkbox("Ignore my color", &g_Config.g_Aimbot.bTeamProtect);
				ImGui::Checkbox("Ignore AFK", &g_Config.g_Aimbot.bIgnoreAFK);
				ImGui::Checkbox("Ignore distance", &g_Config.g_Aimbot.bIgnoreMaxDistance);
				ImGui::Checkbox("Damage players in car", &g_Config.g_Aimbot.bShootInCar);
				ImGui::Checkbox("Wallshot", &g_Config.g_Aimbot.bWallShot);

				ImGui::Spacing(); ImGui::Separator(); ImGui::Spacing();

				ImGui::Checkbox("Autoshot", &g_Config.g_Aimbot.bTriggerbot); ImGui::SameLine(160); ImGui::Image(pTextures->tConfig, { 19, 19 }, { 0, 0 }, { 1, 1 }, ImGui::GetStyle().Colors[ImGuiCol_Text]);  ImGui::SameLine(160); ImGui::Button("##SettingsTrigger", { 20, 0 });
				if (ImGui::BeginPopupContextItem(0, 0))
				{
					ImGui::Spacing();
					ImGui::PushItemWidth(170); ImGui::Hotkey("Hotkey", &g_Config.g_Hotkeys.iTrigger); ImGui::PopItemWidth();
					ImGui::Checkbox("Delay", &g_Config.g_Aimbot.bTriggerDelay); ImGui::SameLine(110); ImGui::PushItemWidth(70);
					ImGui::DragInt("##TriggerDelay", &g_Config.g_Aimbot.iTriggerDelay, 1, 0, 500, "%d ms", ImGuiSliderFlags_ClampOnInput);
					ImGui::Checkbox("Trough wall", &g_Config.g_Aimbot.bTriggerWallshot);
					ImGui::EndPopup();
				}
				ImGui::Checkbox("No reload", &g_Config.g_Combat.bNoReload);
				ImGui::Checkbox("Recoil control", &g_Config.g_Combat.bRecoilctrl); ImGui::SameLine(160); ImGui::Image(pTextures->tConfig, { 19, 19 }, { 0, 0 }, { 1, 1 }, ImGui::GetStyle().Colors[ImGuiCol_Text]);  ImGui::SameLine(160); ImGui::Button("##SettingsRecoil", { 20, 0 });
				ImGui::SetNextWindowSize(ImVec2(177, 39));
				if (ImGui::BeginPopupContextItem(0, 0))
				{
					ImGui::Spacing();
					ImGui::PushItemWidth(150); ImGui::SliderFloat("Recoil", &g_Config.g_Combat.fRecoil, 0.0f, 100.0f, "%.0f%%", ImGuiSliderFlags_ClampOnInput); ImGui::PopItemFlag();
					ImGui::EndPopup();
				}
				ImGui::Checkbox("Shoot rate", &g_Config.g_Combat.bRapidFire); ImGui::SameLine(160);	ImGui::Image(pTextures->tConfig, { 19, 19 }, { 0, 0 }, { 1, 1 }, ImGui::GetStyle().Colors[ImGuiCol_Text]);  ImGui::SameLine(160); ImGui::Button("##SettingsFast Guns", { 20, 0 });
				ImGui::SetNextWindowSize(ImVec2(230, 186));
				if (ImGui::BeginPopupContextItem(0, 0))
				{
					ImGui::Spacing();
					ImGui::SliderFloat("Pistols", &g_Config.g_Combat.fFastPistols, 1.0f, 5.0f, "%0.2f", ImGuiSliderFlags_ClampOnInput);
					ImGui::Dummy(ImVec2(0.0f, 2.0f));
					ImGui::SliderFloat("SMGs", &g_Config.g_Combat.fFastSmgs, 1.0f, 5.0f, "%0.2f", ImGuiSliderFlags_ClampOnInput);
					ImGui::Dummy(ImVec2(0.0f, 2.0f));
					ImGui::SliderFloat("Shotguns", &g_Config.g_Combat.fFastShotguns, 1.0f, 5.0f, "%0.2f", ImGuiSliderFlags_ClampOnInput);
					ImGui::Dummy(ImVec2(0.0f, 2.0f));
					ImGui::SliderFloat("Assault Rifles", &g_Config.g_Combat.fFastRifles, 1.0f, 5.0f, "%0.2f", ImGuiSliderFlags_ClampOnInput);
					ImGui::Dummy(ImVec2(0.0f, 2.0f));
					ImGui::SliderFloat("Sniper Rifles", &g_Config.g_Combat.fFastSniperRifles, 1.0f, 5.0f, "%0.2f", ImGuiSliderFlags_ClampOnInput);
					ImGui::Dummy(ImVec2(0.0f, 2.0f));
					ImGui::SliderFloat("Other", &g_Config.g_Combat.fFastOther, 1.0f, 5.0f, "%0.2f", ImGuiSliderFlags_ClampOnInput);
					ImGui::EndPopup();
				}
				ImGui::Checkbox("Weapon Switcher", &g_Config.g_Combat.bWeaponSwitcher); ImGui::SameLine(160); ImGui::Image(pTextures->tConfig, { 19, 19 }, { 0, 0 }, { 1, 1 }, ImGui::GetStyle().Colors[ImGuiCol_Text]);  ImGui::SameLine(160); ImGui::Button("##SettingsWeaponSwitcher", { 20, 0 });
				if (ImGui::BeginPopupContextItem(0, 0))
				{
					ImGui::Spacing();
					static int iComboWeapon = 0;
					ImGui::PushItemWidth(140); ImGui::Combo("##WeaponCombo", &iComboWeapon, szCategory, 5); ImGui::PopItemWidth(); ImGui::SameLine();
					ImGui::PushItemWidth(100); ImGui::Hotkey("##WeaponHotkey", &g_Config.g_Hotkeys.iWeaponSwitch[iComboWeapon]); ImGui::PopItemWidth();
					ImGui::Checkbox("Fast Switch", &g_Config.g_Combat.bFastSwitch);
					ImGui::EndPopup();
				}
				ImGui::Checkbox("Fast Scroll", &g_Config.g_Combat.bFastScroll); ImGui::SameLine(160); ImGui::Image(pTextures->tConfig, { 19, 19 }, { 0, 0 }, { 1, 1 }, ImGui::GetStyle().Colors[ImGuiCol_Text]);  ImGui::SameLine(160); ImGui::Button("##SettingsFast Scroll", { 20, 0 });
				if (ImGui::BeginPopupContextItem(0, 0))
				{
					ImGui::Spacing();
					ImGui::PushItemWidth(182); ImGui::Hotkey("Hotkey", &g_Config.g_Hotkeys.iScroll); ImGui::PopItemWidth();
					ImGui::EndPopup();
				}
				ImGui::Checkbox("Allow +C-bug", &g_Config.g_Combat.bAllowCBug);

				ImGui::EndChild();
			}
			ImGui::EndGroup();

			ImGui::SameLine();

			ImGui::BeginGroup();
			ImGui::BeginChild("##Bones", { 127, 300 }, true, ImGuiWindowFlags_NoTitleBar);
			{
				static int BonesTab{ 1 };
				switch (BonesTab)
				{
				case 1:
				{
					ImGui::TextDisabled("Smooth bones");
					ImGui::Dummy({ 0, 8 });
					ImGui::Image(pTextures->tSkin, { 112, 233 }, { 0, 0 }, { 1, 1 }, ImVec4{ 1.f,1.f,1.f,1.f });
					ImGui::SetCursorPosX(53);  ImGui::SetCursorPosY(47);
					ImGui::Checkbox2("##Head", &g_Config.g_Aimbot.bBoneHead);
					ImGui::SetCursorPosX(53);
					ImGui::Checkbox2("##Neck", &g_Config.g_Aimbot.bBoneNeck);
					ImGui::SetCursorPosX(27); ImGui::SetCursorPosY(73);
					ImGui::Checkbox2("##Shoulders", &g_Config.g_Aimbot.bBoneShoulders);  ImGui::SameLine(80); ImGui::Checkbox2("##Shoulders_2", &g_Config.g_Aimbot.bBoneShoulders);
					ImGui::SetCursorPosX(53);  ImGui::SetCursorPosY(91);
					ImGui::Checkbox2("##Center", &g_Config.g_Aimbot.bBoneCenter);
					ImGui::SetCursorPosX(21); ImGui::SetCursorPosY(102);
					ImGui::Checkbox2("##Elbows", &g_Config.g_Aimbot.bBoneElbows); ImGui::SameLine(88); ImGui::Checkbox2("##Elbows_2", &g_Config.g_Aimbot.bBoneElbows);
					ImGui::Dummy({ 0, 2 }); ImGui::SetCursorPosX(53);
					ImGui::Checkbox2("##Stomach", &g_Config.g_Aimbot.bBoneStomach);
					ImGui::Dummy({ 0, 32 }); ImGui::SetCursorPosX(39);
					ImGui::Checkbox2("##Knees", &g_Config.g_Aimbot.bBoneKnees);  ImGui::SameLine(72); ImGui::Checkbox2("##Knees_2", &g_Config.g_Aimbot.bBoneKnees);

					ImGui::SetCursorPosX(43); ImGui::SetCursorPosY(272);
					if (ImGui::ArrowButton("##iLeft", ImGuiDir_Left))
						BonesTab = (BonesTab == 1) ? 3 : BonesTab - 1;
					ImGui::SameLine(65);
					if (ImGui::ArrowButton("##iRight", ImGuiDir_Right))
						BonesTab = (BonesTab == 3) ? 1 : BonesTab + 1;

					break;
				}
				case 2:
				{
					ImGui::TextDisabled("Flick bones");
					ImGui::Dummy({ 0, 8 });
					ImGui::Image(pTextures->tSkin, { 112, 233 }, { 0, 0 }, { 1, 1 }, ImVec4{ 1.f,1.f,1.f,1.f });
					ImGui::SetCursorPosX(53);  ImGui::SetCursorPosY(47);
					ImGui::Checkbox2("##Head2", &g_Config.g_Aimbot.bBoneHead2);
					ImGui::SetCursorPosX(53);
					ImGui::Checkbox2("##Neck2", &g_Config.g_Aimbot.bBoneNeck2);
					ImGui::SetCursorPosX(27); ImGui::SetCursorPosY(73);
					ImGui::Checkbox2("##Shoulders2", &g_Config.g_Aimbot.bBoneShoulders2);  ImGui::SameLine(80); ImGui::Checkbox2("##Shoulders2_2", &g_Config.g_Aimbot.bBoneShoulders2);
					ImGui::SetCursorPosX(53);  ImGui::SetCursorPosY(91);
					ImGui::Checkbox2("##Center2", &g_Config.g_Aimbot.bBoneCenter2);
					ImGui::SetCursorPosX(21); ImGui::SetCursorPosY(102);
					ImGui::Checkbox2("##Elbows2", &g_Config.g_Aimbot.bBoneElbows2); ImGui::SameLine(88); ImGui::Checkbox2("##Elbows2_2", &g_Config.g_Aimbot.bBoneElbows2);
					ImGui::Dummy({ 0, 2 }); ImGui::SetCursorPosX(53);
					ImGui::Checkbox2("##Stomach2", &g_Config.g_Aimbot.bBoneStomach2);
					ImGui::Dummy({ 0, 32 }); ImGui::SetCursorPosX(39);
					ImGui::Checkbox2("##Knees2", &g_Config.g_Aimbot.bBoneKnees2);  ImGui::SameLine(72); ImGui::Checkbox2("##Knees2_2", &g_Config.g_Aimbot.bBoneKnees2);

					ImGui::SetCursorPosX(43); ImGui::SetCursorPosY(272);
					if (ImGui::ArrowButton("##iLeft", ImGuiDir_Left))
						BonesTab = (BonesTab == 1) ? 3 : BonesTab - 1;
					ImGui::SameLine(65);
					if (ImGui::ArrowButton("##iRight", ImGuiDir_Right))
						BonesTab = (BonesTab == 3) ? 1 : BonesTab + 1;

					break;
				}
				case 3:
				{
					ImGui::TextDisabled("Silent bones");
					ImGui::Dummy({ 0, 8 });
					ImGui::Image(pTextures->tSkin, { 112, 233 }, { 0, 0 }, { 1, 1 }, ImVec4{ 1.f,1.f,1.f,1.f });
					ImGui::SetCursorPosX(53);  ImGui::SetCursorPosY(47);
					ImGui::Checkbox2("##Head3", &g_Config.g_Aimbot.bBoneHead3);
					ImGui::SetCursorPosX(53);
					ImGui::Checkbox2("##Neck3", &g_Config.g_Aimbot.bBoneNeck3);
					ImGui::SetCursorPosX(27); ImGui::SetCursorPosY(73);
					ImGui::Checkbox2("##Shoulders3", &g_Config.g_Aimbot.bBoneShoulders3);  ImGui::SameLine(80); ImGui::Checkbox2("##Shoulders2_3", &g_Config.g_Aimbot.bBoneShoulders3);
					ImGui::SetCursorPosX(53);  ImGui::SetCursorPosY(91);
					ImGui::Checkbox2("##Center3", &g_Config.g_Aimbot.bBoneCenter3);
					ImGui::SetCursorPosX(21); ImGui::SetCursorPosY(102);
					ImGui::Checkbox2("##Elbows3", &g_Config.g_Aimbot.bBoneElbows3); ImGui::SameLine(88); ImGui::Checkbox2("##Elbows2_3", &g_Config.g_Aimbot.bBoneElbows3);
					ImGui::Dummy({ 0, 2 }); ImGui::SetCursorPosX(53);
					ImGui::Checkbox2("##Stomach3", &g_Config.g_Aimbot.bBoneStomach3);
					ImGui::Dummy({ 0, 32 }); ImGui::SetCursorPosX(39);
					ImGui::Checkbox2("##Knees3", &g_Config.g_Aimbot.bBoneKnees3);  ImGui::SameLine(72); ImGui::Checkbox2("##Knees2_3", &g_Config.g_Aimbot.bBoneKnees3);

					ImGui::SetCursorPosX(43); ImGui::SetCursorPosY(272);
					if (ImGui::ArrowButton("##iLeft", ImGuiDir_Left))
						BonesTab = (BonesTab == 1) ? 3 : BonesTab - 1;
					ImGui::SameLine(65);
					if (ImGui::ArrowButton("##iRight", ImGuiDir_Right))
						BonesTab = (BonesTab == 3) ? 1 : BonesTab + 1;

					break;
				}
				}
				ImGui::EndChild();
			}
			ImGui::EndGroup();
		
			break;
		}
		case 1:
		{
			ImGui::SetCursorPosY(54);
			ImGui::SetCursorPosX(116);
			ImGui::BeginGroup();
			ImGui::BeginChild("##Player1", { 268, 300 }, true, ImGuiWindowFlags_NoTitleBar);
			{
				ImGui::PushItemWidth(90);
				ImGui::Checkbox("Anti Stun", &g_Config.g_Player.bAntiStun); ImGui::SameLine(167); ImGui::SliderInt("Chance", &g_Config.g_Player.iAntiStunChance, 1, 100, "%d%%");
				ImGui::Checkbox("Remove Animation", &g_Config.g_Player.bSbiv); ImGui::SameLine(184); ImGui::PushItemWidth(74); ImGui::Hotkey("##Sbiv", &g_Config.g_Hotkeys.iSbiv); ImGui::PopItemWidth();
				ImGui::Checkbox("Fast Anims", &g_Config.g_Player.bFastAnims); ImGui::SameLine(237); ImGui::Image(pTextures->tConfig, { 19, 19 }, { 0, 0 }, { 1, 1 }, ImGui::GetStyle().Colors[ImGuiCol_Text]);  ImGui::SameLine(237); ImGui::Button("##SettingsFast Anims", { 20, 0 });
				ImGui::SetNextWindowSize(ImVec2(230, 243));
				if (ImGui::BeginPopupContextItem(0, 0))
				{
					ImGui::Spacing(); 
					ImGui::SliderFloat("Run", &g_Config.g_Player.fFastRun, 1.0f, 2.0f, "%0.2f");
					ImGui::Dummy(ImVec2(0.0f, 2.0f));
					ImGui::SliderFloat("Climb", &g_Config.g_Player.fFastClimb, 1.0f, 2.0f, "%0.2f");
					ImGui::Dummy(ImVec2(0.0f, 2.0f));
					ImGui::SliderFloat("Jump", &g_Config.g_Player.fFastJump, 1.0f, 2.0f, "%0.2f");
					ImGui::Dummy(ImVec2(0.0f, 2.0f));
					ImGui::SliderFloat("Fall", &g_Config.g_Player.fFastFall, 1.0f, 2.0f, "%0.2f");
					ImGui::Dummy(ImVec2(0.0f, 2.0f));
					ImGui::SliderFloat("Swim", &g_Config.g_Player.fFastSwim, 1.0f, 5.0f, "%0.2f");
					ImGui::Dummy(ImVec2(0.0f, 2.0f));
					ImGui::SliderFloat("Stuns", &g_Config.g_Player.fFastStuns, 1.0f, 2.0f, "%0.2f");
					ImGui::Dummy(ImVec2(0.0f, 2.0f));
					ImGui::SliderFloat("Gun moves", &g_Config.g_Player.fFastGunMov, 1.0f, 2.0f, "%0.2f");
					ImGui::Dummy(ImVec2(0.0f, 2.0f));
					ImGui::SliderFloat("Fight", &g_Config.g_Player.fFastFight, 1.0f, 2.0f, "%0.2f");
					ImGui::EndPopup();
				}
				ImGui::Checkbox("Infinite Run", &g_Config.g_Player.bInfiniteRun);
				ImGui::Checkbox("Infinite Oxygen", &g_Config.g_Player.bInfiniteOxygen);
				ImGui::Checkbox("Fast Spawn", &g_Config.g_Player.bFastRespawn);
				
				ImGui::Checkbox("Change Skin", &g_Config.g_Player.bChangeSkin); ImGui::SameLine(210); ImGui::PushItemWidth(45); ImGui::InputInt("##SkinID", &g_Config.g_Player.iSkinID, 0, 311); ImGui::PopItemWidth();
				ImGui::Checkbox("HP Heal", &g_Config.g_Player.bHPHeal);
				ImGui::Spacing(); ImGui::Separator(); ImGui::Spacing();
				if (ImGui::Button("Suicide", { 70, 25 }))
					*reinterpret_cast<float*>(*reinterpret_cast<DWORD*>(0xB6F5F0) + 0x540) = 0.0;

				ImGui::PopItemWidth();
				ImGui::EndChild();
			}
			ImGui::EndGroup();

			ImGui::SameLine();
			ImGui::BeginGroup();
			ImGui::BeginChild("##Player2", { 268, 300 }, true, ImGuiWindowFlags_NoTitleBar);
			{
				ImGui::PushItemWidth(90);
				if (ImGui::Checkbox("Air Break", &g_Config.g_Player.bAirBreak))
					g_Config.g_Player.bMapRun = false;
				ImGui::SameLine(167); ImGui::SliderInt("##AirBreak", &g_Config.g_Player.iAirBreak, 1, 100);
				if (ImGui::Checkbox("Map Run", &g_Config.g_Player.bMapRun))
					g_Config.g_Player.bAirBreak = false;
				ImGui::SameLine(167); ImGui::SliderInt("##MapRun", &g_Config.g_Player.iMapRun, 1, 100);
				ImGui::Checkbox("No Fall", &g_Config.g_Player.bNoFall);
				ImGui::Checkbox("Jump Force", &g_Config.g_Player.bMegaJump); ImGui::SameLine(167); ImGui::SliderFloat("##Jump", &g_Config.g_Player.fMegaJump, 1.0f, 5.0f, "%0.1f");
				ImGui::Checkbox("Gode Mode", &g_Config.g_Player.bGM); 
				ImGui::Checkbox("Invisible", &g_Config.g_Player.bInvisible);
				ImGui::PushItemWidth(70);
				ImGui::Checkbox("Fake Lag", &g_Config.g_Player.bFakeLag); ImGui::SameLine(187); ImGui::DragInt("##FakeLag", &g_Config.g_Player.iFakeLag, 1, 1, 500, "%d ms");
				ImGui::Checkbox("Anti-AFK", &g_Config.g_Player.bAntiafk);
				ImGui::PopItemWidth();
				ImGui::EndChild();
			}
			ImGui::EndGroup();

			break;
		}
		case 2:
		{
			ImGui::SetCursorPosY(54);
			ImGui::SetCursorPosX(116);
			ImGui::BeginGroup();
			ImGui::BeginChild("##Vehicle", { 280, 300 }, true, ImGuiWindowFlags_NoTitleBar);
			{
				ImGui::Checkbox("Speedhack", &g_Config.g_Vehicle.bSH); ImGui::SameLine(252); ImGui::Image(pTextures->tConfig, { 19, 19 }, { 0, 0 }, { 1, 1 }, ImGui::GetStyle().Colors[ImGuiCol_Text]);  ImGui::SameLine(252); ImGui::Button("##SettingsSH", { 20, 0 });
				ImGui::SetNextWindowSize(ImVec2(193, 125));
				if (ImGui::BeginPopupContextItem(0, 0))
				{
					ImGui::Spacing();
					ImGui::PushItemWidth(173); ImGui::Hotkey("Hotkey", &g_Config.g_Hotkeys.iSH); ImGui::PopItemWidth();
					ImGui::Dummy(ImVec2(0.0f, 2.0f));
					ImGui::PushItemWidth(173); ImGui::SliderFloat("Acceleration Power", &g_Config.g_Vehicle.bSHpower, 1.f, 100.f, "%.0f%%", ImGuiSliderFlags_ClampOnInput);
					ImGui::Dummy(ImVec2(0.0f, 2.0f));
					ImGui::SliderFloat("Speed Limit", &g_Config.g_Vehicle.bSHLimit, 50.f, 250.f, "%.0fkm/h%", ImGuiSliderFlags_ClampOnInput);  ImGui::PopItemWidth();
					ImGui::Checkbox("Speedometer", &g_Config.g_Vehicle.bSpeedometr);
					ImGui::EndPopup();
				}
				ImGui::Checkbox("Flip  &", &g_Config.g_Vehicle.bFlip); ImGui::SameLine(80); ImGui::Checkbox("Repair", &g_Config.g_Vehicle.bRepair); ImGui::SameLine(177); ImGui::PushItemWidth(97); ImGui::Hotkey("##RepairHotkey", &g_Config.g_Hotkeys.iRepair);  ImGui::PopItemWidth();
				ImGui::Checkbox("GM Car", &g_Config.g_Vehicle.bGMCar);
				ImGui::Checkbox("Bike/Bicycle key Spam", &g_Config.g_Vehicle.bAutoBikeSpam); ImGui::SameLine(); ImGui::PushItemWidth(97); ImGui::Hotkey("##Spam Hotkey", &g_Config.g_Hotkeys.iAutoBikeSpam); ImGui::PopItemWidth();
				ImGui::Checkbox("Don't fall off bike", &g_Config.g_Vehicle.bDontFall);
			}
			ImGui::EndChild();
			ImGui::EndGroup();
			break;
		}
		case 3:
		{
			ImGui::SetCursorPosY(54);
			ImGui::SetCursorPosX(116);
			ImGui::BeginGroup();
			ImGui::BeginChild("##PlayerESP", { 268, 300 }, true, ImGuiWindowFlags_NoTitleBar);
			{
				ImGui::PushItemWidth(90);
				ImGui::Checkbox("ESP Name", &g_Config.g_Visuals.bNameTagsESP); 
				ImGui::Checkbox("ESP Bones", &g_Config.g_Visuals.bBoneESP); ImGui::SameLine(240); ImGui::Image(pTextures->tConfig, { 19, 19 }, { 0, 0 }, { 1, 1 }, ImGui::GetStyle().Colors[ImGuiCol_Text]);  ImGui::SameLine(240); ImGui::Button("##SettingsBones", { 20, 0 });
				ImGui::SetNextWindowSize(ImVec2(120, 70));
				if (ImGui::BeginPopupContextItem(0, 0))
				{
					ImGui::Spacing(); ImGui::Spacing(); ImGui::PushItemWidth(90);
					ImGui::SliderFloat("Thickness##ESP", &g_Config.g_Visuals.fESPThickness, 1.0f, 3.0f, "%0.1f", ImGuiSliderFlags_ClampOnInput);
					ImGui::Checkbox("Clist colored", &g_Config.g_Visuals.bClistBones); ImGui::PopItemWidth();
					ImGui::EndPopup();
				}
				ImGui::Checkbox("ESP Weapon", &g_Config.g_Visuals.bWeaponESP);
				ImGui::Checkbox("ESP Distance", &g_Config.g_Visuals.bDistanceESP);
				ImGui::Spacing(); ImGui::Separator(); ImGui::Spacing();
				ImGui::Checkbox("Aspect Ratio", &g_Config.g_Visuals.bAspectRatio); ImGui::SameLine(170);  ImGui::SliderFloat("##AspectRatio", &g_Config.g_Visuals.fAspectRatio, 0.2f, 2.0f, "%0.1f", ImGuiSliderFlags_ClampOnInput);
				ImGui::Checkbox("Weather Changer", &g_Config.g_Visuals.bWeatherChanger); ImGui::SameLine(170); ImGui::SliderInt("##Weather", &g_Config.g_Visuals.iWeather, 0, 45,"%d ID", ImGuiSliderFlags_ClampOnInput);
				ImGui::Checkbox("Time Changer", &g_Config.g_Visuals.bTimeChanger); ImGui::SameLine(170); ImGui::SliderInt("##Time", &g_Config.g_Visuals.iTime, 0, 24, "%d ID", ImGuiSliderFlags_ClampOnInput);
				ImGui::Checkbox("HP HUD", &g_Config.g_Visuals.bHpHud); ImGui::SameLine(240); ImGui::Image(pTextures->tConfig, { 19, 19 }, { 0, 0 }, { 1, 1 }, ImGui::GetStyle().Colors[ImGuiCol_Text]);  ImGui::SameLine(240); ImGui::Button("##SettingsHP HUD", { 20, 0 });
				if (ImGui::BeginPopupContextItem(0, 0))
				{
					ImGui::Spacing();
					ImGui::PushItemWidth(90); ImGui::TextDisabled("X "); ImGui::SameLine(); ImGui::InputFloat("##X", &g_Config.g_Visuals.HPx);
					ImGui::TextDisabled("Y "); ImGui::SameLine(); ImGui::InputFloat("##Y", &g_Config.g_Visuals.HPy); ImGui::PopItemWidth();
					ImGui::EndPopup();
				}
				ImGui::Checkbox("Show FPS", &g_Config.g_Visuals.bFPS);
				ImGui::Checkbox("Small Radar Icons", &g_Config.g_Visuals.bSmallIcons); ImGui::SameLine(240); ImGui::Image(pTextures->tConfig, { 19, 19 }, { 0, 0 }, { 1, 1 }, ImGui::GetStyle().Colors[ImGuiCol_Text]);  ImGui::SameLine(240); ImGui::Button("##SettingsSmall Icons", { 20, 0 });
				ImGui::SetNextWindowSize(ImVec2(120, 70));
				if (ImGui::BeginPopupContextItem(0, 0))
				{
					ImGui::Spacing();ImGui::PushItemWidth(100); 
					ImGui::SliderFloat("Players##Radar", &g_Config.g_Visuals.pIcon, 0.1f, 1.0f, "%0.1f"); 
					ImGui::Dummy(ImVec2(0.0f, 2.0f));
					ImGui::SliderFloat("Other##Radar", &g_Config.g_Visuals.oIcon, 0.1f, 1.0f, "%0.1f"); ImGui::PopItemWidth();
					ImGui::EndPopup();
				}
				ImGui::EndChild();
			}
			ImGui::EndGroup();

			ImGui::SameLine();

			ImGui::BeginGroup();
			ImGui::BeginChild("##Visuals", { 268, 300 }, true, ImGuiWindowFlags_NoTitleBar);
			{
				ImGui::PushItemWidth(90);
				ImGui::Checkbox("NoPostFX", &g_Config.g_Visuals.bNoPostFX);
				ImGui::Checkbox("Damage Informer", &g_Config.g_Visuals.bDMGInformer); ImGui::SameLine(240); ImGui::Image(pTextures->tConfig, { 19, 19 }, { 0, 0 }, { 1, 1 }, ImGui::GetStyle().Colors[ImGuiCol_Text]);  ImGui::SameLine(240); ImGui::Button("##SettingsDMG", { 20, 0 });
				if (ImGui::BeginPopupContextItem(0, 0))
				{
					ImGui::Spacing();
					ImGui::TextUnformatted("Font Size"); ImGui::SameLine(150); ImGui::PushItemWidth(70);
					ImGui::SliderInt("##DMGFont", &g_Config.g_Visuals.iFontSize, 13, 25, "%d px", ImGuiSliderFlags_ClampOnInput);
					ImGui::TextUnformatted("Time on screen"); ImGui::SameLine(150); ImGui::PushItemWidth(70);
					ImGui::DragFloat("##DMGTick", &g_Config.g_Visuals.fDMGTick, 0.05f, 0.1f, 10.0f, "%.1f s");
					ImGui::PushItemWidth(161);
					ImGui::ColorEdit4("Text", (float*)&g_Config.g_Visuals.colorDMG, ImGuiColorEditFlags_AlphaBar);
					ImGui::PopItemWidth();
					ImGui::EndPopup();
				}
				ImGui::Checkbox("No Drugs Effect", &g_Config.g_Visuals.bNoDrugsEffect);
				ImGui::Checkbox("160 HP Bar", &g_Config.g_Visuals.b160hp);
				ImGui::Spacing(); ImGui::Separator(); ImGui::Spacing();
				ImGui::Checkbox("Draw FOV & Bullet", &g_Config.g_Aimbot.bDrawDebug); ImGui::SameLine(170); ImGui::SliderFloat("Thickness##Outline", &g_Config.g_Aimbot.fOutlineThickness, 1.0f, 5.0f, " % 0.1f");
				ImGui::EndChild();
			}
			ImGui::EndGroup();

			break;
		}
		case 4:
		{
			ImGui::SetCursorPosY(54);
			ImGui::SetCursorPosX(116);
			ImGui::BeginGroup();
			ImGui::BeginChild("##Config", { 256, 300 }, true, ImGuiWindowFlags_NoTitleBar);
			{
				ImGui::Columns(2, NULL, false);
				ImGui::SetColumnOffset(1, 170);
				ImGui::PushItemWidth(160);

				if (ImGui::Button("Autoload disable", { 159, 25 })) Cheat::Record0();

				auto& vecConfigs = pConfig->getConfigs();

				if (static_cast<std::size_t>(iCurrentConfig) >= vecConfigs.size())
					iCurrentConfig = -1;

				static std::string szBuffer;

				if (ImGui::ListBox("", &iCurrentConfig, [](void* data, int idx, const char** out_text) {
					auto& vector = *static_cast<std::vector<std::string>*>(data);
					*out_text = vector[idx].c_str();
					return true;
					}, &vecConfigs, vecConfigs.size(), 7) && iCurrentConfig != -1)
					szBuffer = vecConfigs[iCurrentConfig];

				ImGui::PushID(0);
				if (ImGui::InputTextWithHint("", "Name", szBuffer.data(), szBuffer.capacity() + 1, ImGuiInputTextFlags_EnterReturnsTrue))
				{
					if (iCurrentConfig != -1)
						pConfig->Rename(iCurrentConfig, szBuffer.c_str());
				}
				ImGui::PopID();
				ImGui::NextColumn();

				if (ImGui::Button("Update", { 70, 25 }))
					pConfig->listConfigs();
				if (ImGui::Button("Create", { 70, 25 }))
					pConfig->Add(szBuffer.c_str());
				
				if (iCurrentConfig != -1)
				{
					ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 2);
					if (ImGui::Button("Autoload", { 70, 25 })) Cheat::Record1(iCurrentConfig);
					if (ImGui::Button("Load", { 70, 25 }))
					{
						pConfig->Load(iCurrentConfig);
						for (int i = 0; i < ImGuiCol_COUNT; i++)
							ImGui::GetStyle().Colors[i] = g_Config.g_Style.vecTheme[i];
					}
					if (ImGui::Button("Save", { 70, 25 }))
						pConfig->Save(iCurrentConfig);
					if (ImGui::Button("Delete", { 70, 25 }))
					{
						pConfig->Remove(iCurrentConfig);
						iCurrentConfig = -1;
						szBuffer.clear();
					}
				}
				ImGui::Columns(1);
				ImGui::Spacing(); ImGui::Separator(); ImGui::Spacing();
				ImGui::PushItemWidth(190); ImGui::Hotkey("Menu Hotkey", &g_Config.g_Hotkeys.iActivate); ImGui::PopItemWidth();
				ImGui::Spacing(); ImGui::Separator(); ImGui::Spacing();
					if (ImGui::Button("Unload", { 70, 0 }))
						ImGui::OpenPopup("Unload");
					if (ImGui::BeginPopupModal("Unload", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoTitleBar))
					{
						ImGui::Text("[!] Close any recording software before press Unload [!]");
						ImGui::Dummy({ 0,10 });
						if (ImGui::Button("Unload", ImVec2(160.f, 20.f))) Cheat::Unload();
						ImGui::SameLine();
						if (ImGui::Button("Close", ImVec2(160.5f, 20.f))) ImGui::CloseCurrentPopup();
						ImGui::EndPopup();
					}
					if (ImGui::Button("Kill GTA", { 70, 0 }))
						system("taskkill /IM gta_sa.exe /F");

				ImGui::EndChild();
			}	
			ImGui::EndGroup();

			ImGui::SameLine(379);
			ImGui::BeginGroup();
			ImGui::BeginChild("##Style", { 270, 300 }, true, ImGuiWindowFlags_NoTitleBar);
			{
				ImGui::Spacing();
				for (int i = 0; i < ImGuiCol_COUNT; i++)
				{
					ImGui::PushID(i);
					ImGui::Text(ImGui::GetStyleColorName(i));
					ImGui::SameLine(165);
					ImGui::PushItemWidth(90);
					ImGui::ColorEdit4("##Color", (float*)&ImGui::GetStyle().Colors[i], ImGuiColorEditFlags_DisplayHex | ImGuiColorEditFlags_AlphaBar);
					ImGui::PopItemWidth();
					if (memcmp(&ImGui::GetStyle().Colors[i], &g_Config.g_Style.vecTheme[i], sizeof(ImVec4)) != 0)
						g_Config.g_Style.vecTheme[i] = ImGui::GetStyle().Colors[i];
					ImGui::PopID();
				}
				ImGui::EndChild();
				ImGui::EndGroup();
			}
			break;
		}
		}
		ImGui::End();
	}
}