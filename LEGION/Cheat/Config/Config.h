#pragma once

struct stConfig
{
	struct stAimbot
	{
		bool bTriggerbot{ false };

		int iAimbotConfig[35][9];

		bool bAimbotEnabledSmooth[35]; 
		bool bAimbotEnabledSilent[35]; 
		bool bAimbotEnabledFlick[35];

		float fSilentAccuracy{ 100.f };
		bool bDisable1st{ false };
		bool bGTrinagle{ false };

		bool bSmoothIsFire{ false };
		bool bSmoothLockY{ false };
		bool bSmoothLockY2{ false };
		bool bStopOnBody{ false };
		bool bStopOnBody2{ false };

		bool bTriggerDelay{ false };
		int iTriggerDelay{ 0 };
		bool bTriggerSync{ false };
		bool bTriggerWallshot{ false };

		bool bBoneHead{ false };
		bool bBoneNeck{ false };
		bool bBoneCenter{ false };
		bool bBoneElbows{ false };
		bool bBoneStomach{ false }; 
		bool bBoneKnees{ false };
		bool bBoneShoulders{ false };

		bool bBoneHead2{ false };
		bool bBoneNeck2{ false };
		bool bBoneCenter2{ false };
		bool bBoneElbows2{ false };
		bool bBoneStomach2{ false };
		bool bBoneKnees2{ false };
		bool bBoneShoulders2{ false };

		bool bBoneHead3{ false };
		bool bBoneNeck3{ false };
		bool bBoneCenter3{ false };
		bool bBoneElbows3{ false };
		bool bBoneStomach3{ false };
		bool bBoneKnees3{ false };
		bool bBoneShoulders3{ false };

		bool bTeamProtect{ false };
		bool bWallShot{ false };
		bool bIgnoreMaxDistance{ false };
		bool bIgnoreAFK{ false };
		bool bIsStun{ false };
		bool bShootInCar{ false };

		bool bDrawDebug{ false };
		float fOutlineThickness{ 2.f };
	} g_Aimbot;

	struct stCombat
	{
		bool bNoReload{ false };
		bool bAllowCBug{ false };
		bool bRapidFire{ false };
		float fFastPistols{ 1.f };
		float fFastSmgs{ 1.f };
		float fFastShotguns{ 1.f };
		float fFastRifles{ 1.f };
		float fFastSniperRifles{ 1.f };
		float fFastOther{ 1.f };
		bool bRecoilctrl{ false };
		float fRecoil{ 100.0f };
		bool bWeaponSwitcher{ false };
		bool bFastSwitch{ false };
		bool bFastScroll{ false };
	} g_Combat;

	struct stPlayer
	{
		bool bAntiStun{ false };
		int iAntiStunChance{ 1 };
		int iFastRotation{ 0 };
		bool bFastAnims{ false };
		float fFastRun{ 1.f };
		float fFastClimb{ 1.f };
		float fFastJump{ 1.f };
		float fFastFall{ 1.f };
		float fFastSwim{ 1.f };
		float fFastStuns{ 1.f };
		float fFastGunMov{ 1.f };
		float fFastFight{ 1.f };
		bool bAirBreak{ false };
		int iAirBreak{ 3 };
		bool bMapRun{ false };
		int iMapRun{ 3 };
		bool bInfiniteRun{ false };
		bool bInfiniteOxygen{ false };
		bool bNoFall{ false };
		bool bMegaJump{ false };
		float fMegaJump{ 1.f };
		bool bChangeSkin{ false };
		int iSkinID{ -1 };
		bool bFastRespawn{ false };
		bool bInvisible{ false };
		bool bFakeLag{ false };
		int iFakeLag{ 1 };
		bool bHPHeal{ false };
		bool bGM{ false };
		bool bSbiv{ false };
		bool bAntiafk{ false };
	} g_Player;

	struct stVehicle
	{
		bool bSH{ false };
		float bSHpower{ 1.0 };
		float bSHLimit{ 50.0 };
		bool bFlip{ false };
		bool bRepair{ false };
		bool bSpeedometr{ false };
		bool bGMCar{ false };
		bool bAutoBikeSpam{ false };
		bool bDontFall{ false };
	} g_Vehicle;

	struct stVisuals
	{
		bool bNameTagsESP{ false };
		bool bWeaponESP{ false };
		bool bBoneESP{ false };
		bool bDistanceESP{ false };
		float fESPThickness{ 1.0f };
		bool bClistBones{ false };

		bool bDMGInformer{ false };
		int iFontSize{ 30 };
		float fDMGTick{ 1.5f };
		ImVec4 colorDMG{ 1.f, 1.f, 1.f, 1.f };

		bool bNoDrugsEffect{ false };

		bool bAspectRatio{ false };
		float fAspectRatio{ 1.3333334f };

		bool bWeatherChanger{ false };
		int iWeather{ 0 };
		bool bTimeChanger{ false };
		int iTime{ 0 };

		bool bNoPostFX{ false };
		bool bFPS{ false };
		bool bHpHud{ false };
		float HPx{ 1735.0 };
		float HPy{ 158.0 };

		bool bSmallIcons{ false };
		float oIcon{ 0.9 };
		float pIcon{ 0.4 };
		bool b160hp{ false };
	}  g_Visuals;

	struct stStyle
	{
		ImVec4 vecTheme[ImGuiCol_COUNT];
		int iTheme{ 0 };
		int iCheckbox{ 1 };
	} g_Style;

	struct stHotkeys
	{
		std::array<int, 5> iWeaponSwitch{ 0, 0, 0, 0, 0 };
		int iAutoBikeSpam{ 0 };
		int iScroll{ 0 };
		int iTrigger{ 0 };
		int iSH{ 0 };
		int iRepair{ 0 };
		int iSbiv{ 0 };
		int iActivate{ VK_HOME };
	} g_Hotkeys;
};

class CConfig
{
public:
	CConfig(const char* szName);
	void Load(size_t index);
	void Save(size_t index);
	void Add(const char* szName);
	void Remove(size_t index);
	void Rename(size_t item, const char* szName);
	void Reset();
	void listConfigs();

	constexpr auto& getConfigs()
	{
		return Configs;
	}
private:
	std::filesystem::path Path;
	std::vector<std::string> Configs;
};

extern CConfig* pConfig;
extern struct stConfig g_Config;