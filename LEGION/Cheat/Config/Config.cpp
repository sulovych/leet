#include "D:\LEGION\LEGION\main.h"

struct stConfig g_Config;
CConfig* pConfig;

using json = nlohmann::basic_json<std::map, std::vector, std::string, bool, std::int64_t, std::uint64_t, float>;
using value_t = json::value_t;

CConfig::CConfig(const char* szName)
{
	memset(g_Config.g_Aimbot.bAimbotEnabledSmooth, false, sizeof(g_Config.g_Aimbot.bAimbotEnabledSmooth));
    memset(g_Config.g_Aimbot.bAimbotEnabledFlick, false, sizeof(g_Config.g_Aimbot.bAimbotEnabledFlick));
    memset(g_Config.g_Aimbot.bAimbotEnabledSilent, false, sizeof(g_Config.g_Aimbot.bAimbotEnabledSilent));
    for (int i = 22; i <= 34; i++)
    {
        g_Config.g_Aimbot.iAimbotConfig[i][FOV_SMOOTH] = 1;
        g_Config.g_Aimbot.iAimbotConfig[i][SMOOTH] = 1;
        g_Config.g_Aimbot.iAimbotConfig[i][FOV_FLICK] = 1;
        g_Config.g_Aimbot.iAimbotConfig[i][FLICK] = 1;
        g_Config.g_Aimbot.iAimbotConfig[i][FOV_SILENT] = 1;
        g_Config.g_Aimbot.iAimbotConfig[i][SILENT] = 1;
    }

	if (PWSTR pathToDocuments; SUCCEEDED(SHGetKnownFolderPath(FOLDERID_Documents, 0, nullptr, &pathToDocuments)))
	{
		Path = pathToDocuments;
		Path /= szName;
		CoTaskMemFree(pathToDocuments);
	}

    listConfigs();
}

#define WRITE(name, valueName) to_json(j[name], o.valueName, dummy.valueName)

template <typename T>
static void to_json(json& j, const T& o, const T& dummy)
{
    if (o != dummy)
        j = o;
}

static void to_json(json& j, const ImVec4& o, const ImVec4& dummy)
{
    j[0] = o.x;
    j[1] = o.y;
    j[2] = o.z;
    j[3] = o.w;
}

static void to_json(json& j, const stConfig::stAimbot& o, const stConfig::stAimbot& dummy = {})
{
    for (int i = 22; i <= 34; i++)
    {
        WRITE(mapWeapons[i].szName + " FOV_SMOOTH", iAimbotConfig[i][FOV_SMOOTH]);
        WRITE(mapWeapons[i].szName + " SMOOTH", iAimbotConfig[i][SMOOTH]);
        WRITE(mapWeapons[i].szName + " FOV_FLICK", iAimbotConfig[i][FOV_FLICK]);
        WRITE(mapWeapons[i].szName + " FLICK", iAimbotConfig[i][FLICK]);
        WRITE(mapWeapons[i].szName + " FOV_SILENT", iAimbotConfig[i][FOV_SILENT]);
        WRITE(mapWeapons[i].szName + " SILENT", iAimbotConfig[i][SILENT]);
        WRITE(mapWeapons[i].szName + " SmoothON", bAimbotEnabledSmooth[i]);
        WRITE(mapWeapons[i].szName + " FlickON", bAimbotEnabledFlick[i]);
        WRITE(mapWeapons[i].szName + " SilentON", bAimbotEnabledSilent[i]);
    }

    WRITE("bTriggerbot", bTriggerbot);
    WRITE("bDisable1st", bDisable1st);
    WRITE("bGTrinagle", bGTrinagle);
    WRITE("bSmoothIsFire", bSmoothIsFire);
    WRITE("bSmoothLockY",  bSmoothLockY);
    WRITE("bSmoothLockY2", bSmoothLockY2);
    WRITE("bStopOnBody", bStopOnBody);
    WRITE("bStopOnBody2", bStopOnBody2);
    WRITE("bTriggerDelay", bTriggerDelay);
    WRITE("iTriggerDelay", iTriggerDelay);
    WRITE("bTriggerSync", bTriggerSync);
    WRITE("bTriggerWallshot", bTriggerWallshot);
    WRITE("bTeamProtect", bTeamProtect);
    WRITE("bWallShot", bWallShot);
    WRITE("bIgnoreMaxDistance", bIgnoreMaxDistance);
    WRITE("bIgnoreAFK", bIgnoreAFK);
    WRITE("bIsStun", bIsStun);
    WRITE("bShootInCar", bShootInCar);
    WRITE("bDrawDebug", bDrawDebug);
    WRITE("fOutlineThickness", fOutlineThickness);

    WRITE("bBoneHead", bBoneHead); 
    WRITE("bBoneNeck", bBoneNeck); 
    WRITE("bBoneCenter", bBoneCenter); 
    WRITE("bBoneElbows", bBoneElbows); 
    WRITE("bBoneStomach", bBoneStomach); 
    WRITE("bBoneKnees", bBoneKnees); 
    WRITE("bBoneShoulders", bBoneShoulders);

    WRITE("bBoneHead2", bBoneHead2);
    WRITE("bBoneNeck2", bBoneNeck2);
    WRITE("bBoneCenter2", bBoneCenter2);
    WRITE("bBoneElbows2", bBoneElbows2);
    WRITE("bBoneStomach2", bBoneStomach2);
    WRITE("bBoneKnees2", bBoneKnees2);
    WRITE("bBoneShoulders2", bBoneShoulders2);

    WRITE("bBoneHead3", bBoneHead3);
    WRITE("bBoneNeck3", bBoneNeck3);
    WRITE("bBoneCenter3", bBoneCenter3);
    WRITE("bBoneElbows3", bBoneElbows3);
    WRITE("bBoneStomach3", bBoneStomach3);
    WRITE("bBoneKnees3", bBoneKnees3);
    WRITE("bBoneShoulders3", bBoneShoulders3);
}

static void to_json(json& j, const stConfig::stCombat& o, const stConfig::stCombat& dummy = {})
{
    WRITE("bNoReload", bNoReload);
    WRITE("bAllowCBug", bAllowCBug);
    WRITE("bRapidFire", bRapidFire);
    WRITE("fFastPistols", fFastPistols);
    WRITE("fFastSmgs", fFastSmgs);
    WRITE("fFastShotguns", fFastShotguns);
    WRITE("fFastRifles", fFastRifles);
    WRITE("fFastSniperRifles", fFastSniperRifles);
    WRITE("fFastOther", fFastOther);
    WRITE("bRecoilctrl", bRecoilctrl);
    WRITE("fRecoil", fRecoil);
    WRITE("bWeaponSwitcher", bWeaponSwitcher);
    WRITE("bFastSwitch", bFastSwitch);
    WRITE("bAutoScroll", bFastScroll);
}

static void to_json(json& j, const stConfig::stPlayer& o, const stConfig::stPlayer& dummy = {})
{
    WRITE("bAntiStun", bAntiStun);
    WRITE("iAntiStunChance", iAntiStunChance);
    WRITE("iFastRotation", iFastRotation);
    WRITE("bFastAnims", bFastAnims);
    WRITE("fFastRun", fFastRun);
    WRITE("fFastClimb", fFastClimb);
    WRITE("fFastJump", fFastJump);
    WRITE("fFastFall", fFastFall);
    WRITE("fFastSwim", fFastSwim);
    WRITE("fFastStuns", fFastStuns);
    WRITE("fFastGunMov", fFastGunMov);
    WRITE("fFastFight", fFastFight);
    WRITE("bAirBreak", bAirBreak);
    WRITE("iAirBreak", iAirBreak);
    WRITE("bMapRun", bMapRun);
    WRITE("iMapRun", iMapRun);
    WRITE("bInfiniteRun", bInfiniteRun);
    WRITE("bInfiniteOxygen", bInfiniteOxygen);
    WRITE("bNoFall", bNoFall);
    WRITE("bMegaJump", bMegaJump);
    WRITE("fMegaJump", fMegaJump);
    WRITE("bChangeSkin", bChangeSkin);
    WRITE("iSkinID", iSkinID);
    WRITE("bFastRespawn", bFastRespawn);
    WRITE("bInvisible", bInvisible);
    WRITE("bFakeLag", bFakeLag);
    WRITE("iFakeLag", iFakeLag);
    WRITE("bHPHeal", bHPHeal);
    WRITE("bGM", bGM);
    WRITE("bSbiv", bSbiv);
    WRITE("bAntiafk", bAntiafk);
}

static void to_json(json& j, const stConfig::stVehicle& o, const stConfig::stVehicle& dummy = {})
{
    WRITE("bSH", bSH);
    WRITE("bSHpower", bSHpower);
    WRITE("bSHLimit", bSHLimit);
    WRITE("bFlip", bFlip);
    WRITE("bRepair", bRepair);
    WRITE("bSpeedometr", bSpeedometr);
    WRITE("bGMCar", bGMCar);
    WRITE("bAutoBikeSpam", bAutoBikeSpam);
    WRITE("bDontFall", bDontFall);
}

static void to_json(json& j, const stConfig::stVisuals& o, const stConfig::stVisuals& dummy = {})
{
    WRITE("bNameTagsESP", bNameTagsESP);
    WRITE("bWeaponESP", bWeaponESP);
    WRITE("bBoneESP", bBoneESP);
    WRITE("bDistanceESP", bDistanceESP);
    WRITE("fESPThickness", fESPThickness);
    WRITE("bClistBones", bClistBones);
    WRITE("bDMGInformer", bDMGInformer);
    WRITE("iFontSize", iFontSize);
    WRITE("fDMGTick", fDMGTick);
    WRITE("colorDMG", colorDMG);
    WRITE("bNoDrugsEffect", bNoDrugsEffect);
    WRITE("bAspectRatio", bAspectRatio);
    WRITE("fAspectRatio", fAspectRatio);
    WRITE("bWeatherChanger", bWeatherChanger);
    WRITE("iWeather", iWeather);
    WRITE("bTimeChanger", bTimeChanger);
    WRITE("iTime", iTime);
    WRITE("bHpHud", bHpHud);
    WRITE("HPx", HPx);
    WRITE("HPy", HPy);
    WRITE("bSmallIcons", bSmallIcons);
    WRITE("oIcon", oIcon);
    WRITE("pIcon", pIcon);
    WRITE("b160hp", b160hp);
    WRITE("bFPS", bFPS);
    WRITE("bNoPostFX", bNoPostFX);
}

static void to_json(json& j, const stConfig::stStyle& o, const stConfig::stStyle& dummy = {})
{
    for (int i = 0; i < ImGuiCol_COUNT; i++)
        WRITE(ImGui::GetStyleColorName(i), vecTheme[i]);
    WRITE("iTheme", iTheme);
    WRITE("iCheckbox", iCheckbox);
}

static void to_json(json& j, const stConfig::stHotkeys& o, const stConfig::stHotkeys& dummy = {})
{
    WRITE("iWeaponSwitch", iWeaponSwitch);
    WRITE("iAutoBikeSpam", iAutoBikeSpam);
    WRITE("iScroll", iScroll);
    WRITE("iTrigger", iTrigger);
    WRITE("iSH", iSH);
    WRITE("iRepair", iRepair);
    WRITE("iSbiv", iSbiv);
    WRITE("iActivate", iActivate);
}

void removeEmptyObjects(json& j)
{
    for (auto it = j.begin(); it != j.end();) {
        auto& val = it.value();
        if (val.is_object() || val.is_array())
            removeEmptyObjects(val);
        if (val.empty() && !j.is_array())
            it = j.erase(it);
        else
            ++it;
    }
}

template <value_t Type, typename T>
static typename std::enable_if_t<!std::is_same_v<T, bool>> read(const json& j, const char* key, T& o)
{
    if (!j.contains(key))
        return;

    if (const auto& val = j[key]; val.type() == Type)
        val.get_to(o);
}

static void read(const json& j, const char* key, bool& o)
{
    if (!j.contains(key))
        return;

    if (const auto& val = j[key]; val.type() == value_t::boolean)
        val.get_to(o);
}

static void read(const json& j, const char* key, float& o)
{
    if (!j.contains(key))
        return;

    if (const auto& val = j[key]; val.type() == value_t::number_float)
        val.get_to(o);
}

static void read(const json& j, const char* key, int& o)
{
    if (!j.contains(key))
        return;

    if (const auto& val = j[key]; val.is_number_integer())
        val.get_to(o);
}

template <typename T, size_t Size>
static void read(const json& j, const char* key, std::array<T, Size>& o)
{
    if (!j.contains(key))
        return;

    if (const auto& val = j[key]; val.type() == value_t::array && val.size() == o.size()) {
        for (std::size_t i = 0; i < val.size(); ++i) {
            if (!val[i].empty())
                val[i].get_to(o[i]);
        }
    }
}

static void read(const json& j, const char* key, ImVec4& o)
{
    std::array<float, 4> temp;
    read(j, key, temp);
    o = ImVec4(temp[0], temp[1], temp[2], temp[3]);
}

static void from_json(const json& j, stConfig::stAimbot& r)
{
    for (int i = 22; i <= 34; i++)
    {
        read(j, (mapWeapons[i].szName + " FOV_SMOOTH").c_str(), r.iAimbotConfig[i][FOV_SMOOTH]);
        read(j, (mapWeapons[i].szName + " SMOOTH").c_str(), r.iAimbotConfig[i][SMOOTH]);
        read(j, (mapWeapons[i].szName + " FOV_FLICK").c_str(), r.iAimbotConfig[i][FOV_FLICK]);
        read(j, (mapWeapons[i].szName + " FLICK").c_str(), r.iAimbotConfig[i][FLICK]);
        read(j, (mapWeapons[i].szName + " FOV_SILENT").c_str(), r.iAimbotConfig[i][FOV_SILENT]);
        read(j, (mapWeapons[i].szName + " SILENT").c_str(), r.iAimbotConfig[i][SILENT]);
        read(j, (mapWeapons[i].szName + " SmoothON").c_str(), r.bAimbotEnabledSmooth[i]);
        read(j, (mapWeapons[i].szName + " FlickON").c_str(), r.bAimbotEnabledFlick[i]);
        read(j, (mapWeapons[i].szName + " SilentON").c_str(), r.bAimbotEnabledSilent[i]);
    }

    read(j, "bTriggerbot", r.bTriggerbot);
    read(j, "bDisable1st", r.bDisable1st);
    read(j, "bGTrinagle", r.bGTrinagle);
    read(j, "bSmoothIsFire", r.bSmoothIsFire);
    read(j, "bSmoothLockY", r.bSmoothLockY);
    read(j, "bSmoothLockY2", r.bSmoothLockY2);
    read(j, "bStopOnBody", r.bStopOnBody);
    read(j, "bStopOnBody", r.bStopOnBody2);
    read(j, "bTriggerDelay", r.bTriggerDelay);
    read(j, "iTriggerDelay", r.iTriggerDelay);
    read(j, "bTriggerWallshot", r.bTriggerWallshot);
    read(j, "bTriggerSync", r.bTriggerSync);
    read(j, "bTeamProtect", r.bTeamProtect);
    read(j, "bWallShot", r.bWallShot);
    read(j, "bIgnoreMaxDistance", r.bIgnoreMaxDistance);
    read(j, "bIgnoreAFK", r.bIgnoreAFK);
    read(j, "bIsStun", r.bIsStun); 
    read(j, "bShootInCar", r.bShootInCar);
    read(j, "bDrawDebug", r.bDrawDebug);
    read(j, "fOutlineThickness", r.fOutlineThickness);

    read(j, "bBoneHead", r.bBoneHead);
    read(j, "bBoneNeck", r.bBoneNeck);
    read(j, "bBoneCenter", r.bBoneCenter);
    read(j, "bBoneElbows", r.bBoneElbows);
    read(j, "bBoneStomach", r.bBoneStomach);
    read(j, "bBoneKnees", r.bBoneKnees);
    read(j, "bBoneShoulders", r.bBoneShoulders);

    read(j, "bBoneHead2", r.bBoneHead2);
    read(j, "bBoneNeck2", r.bBoneNeck2);
    read(j, "bBoneCenter2", r.bBoneCenter2);
    read(j, "bBoneElbows2", r.bBoneElbows2);
    read(j, "bBoneStomach2", r.bBoneStomach2);
    read(j, "bBoneKnees2", r.bBoneKnees2);
    read(j, "bBoneShoulders2", r.bBoneShoulders2);

    read(j, "bBoneHead3", r.bBoneHead3);
    read(j, "bBoneNeck3", r.bBoneNeck3);
    read(j, "bBoneCenter3", r.bBoneCenter3);
    read(j, "bBoneElbows3", r.bBoneElbows3);
    read(j, "bBoneStomach3", r.bBoneStomach3);
    read(j, "bBoneKnees3", r.bBoneKnees3);
    read(j, "bBoneShoulders3", r.bBoneShoulders3);
}

static void from_json(const json& j, stConfig::stCombat& r)
{
   read(j, "bNoReload", r.bNoReload);
   read(j, "bAllowCBug", r.bAllowCBug);
   read(j, "bRapidFire", r.bRapidFire);
   read(j, "fFastPistols", r.fFastPistols);
   read(j, "fFastSmgs", r.fFastSmgs);
   read(j, "fFastShotguns", r.fFastShotguns);
   read(j, "fFastRifles", r.fFastRifles);
   read(j, "fFastSniperRifles", r.fFastSniperRifles);
   read(j, "fFastOther", r.fFastOther);
   read(j, "bRecoilctrl", r.bRecoilctrl);
   read(j, "fRecoil", r.fRecoil);
   read(j, "bWeaponSwitcher", r.bWeaponSwitcher);
   read(j, "bFastSwitch", r.bFastSwitch);
   read(j, "bAutoScroll", r.bFastScroll);
}

static void from_json(const json& j, stConfig::stPlayer& r)
{
    read(j, "bAntiStun", r.bAntiStun);
    read(j, "iAntiStunChance", r.iAntiStunChance);
    read(j, "iFastRotation", r.iFastRotation);
    read(j, "bFastAnims", r.bFastAnims);
    read(j, "fFastRun", r.fFastRun);
    read(j, "fFastClimb", r.fFastClimb);
    read(j, "fFastJump", r.fFastJump);
    read(j, "fFastFall", r.fFastFall);
    read(j, "fFastSwim", r.fFastSwim);
    read(j, "fFastStuns", r.fFastStuns);
    read(j, "fFastGunMov", r.fFastGunMov);
    read(j, "fFastFight", r.fFastFight);
    read(j, "bAirBreak", r.bAirBreak);
    read(j, "iAirBreak", r.iAirBreak);
    read(j, "bMapRun", r.bMapRun);
    read(j, "iMapRun", r.iMapRun);
    read(j, "bInfiniteRun", r.bInfiniteRun);
    read(j, "bInfiniteOxygen", r.bInfiniteOxygen);
    read(j, "bNoFall", r.bNoFall);
    read(j, "bMegaJump", r.bMegaJump);
    read(j, "fMegaJump", r.fMegaJump);
    read(j, "bChangeSkin", r.bChangeSkin);
    read(j, "iSkinID", r.iSkinID);
    read(j, "bFastRespawn", r.bFastRespawn);
    read(j, "bInvisible", r.bInvisible);
    read(j, "bFakeLag", r.bFakeLag);
    read(j, "iFakeLag", r.iFakeLag);
    read(j, "bHPHeal", r.bHPHeal);
    read(j, "bGM", r.bGM);
    read(j, "bSbiv", r.bSbiv);
    read(j, "bAntiafk", r.bAntiafk);
}

static void from_json(const json& j, stConfig::stVehicle& r)
{
    read(j, "bSH", r.bSH);
    read(j, "bSHpower", r.bSHpower);
    read(j, "bSHLimit", r.bSHLimit);
    read(j, "bFlip", r.bFlip);
    read(j, "bRepair", r.bRepair);
    read(j, "bSpeedometr", r.bSpeedometr);
    read(j, "bGMCar", r.bGMCar);
    read(j, "bAutoBikeSpam", r.bAutoBikeSpam);
    read(j, "bDontFall", r.bDontFall);
}

static void from_json(const json& j, stConfig::stVisuals& r)
{
    read(j, "bNameTagsESP", r.bNameTagsESP);
    read(j, "bWeaponESP", r.bWeaponESP);
    read(j, "bBoneESP", r.bBoneESP);
    read(j, "bDistanceESP", r.bDistanceESP);
    read(j, "fESPThickness", r.fESPThickness);
    read(j, "bClistBones", r.bClistBones);
    read(j, "bDMGInformer", r.bDMGInformer);
    read(j, "iFontSize", r.iFontSize);
    read(j, "fDMGTick", r.fDMGTick);
    read(j, "colorDMG", r.colorDMG);
    read(j, "bNoDrugsEffect", r.bNoDrugsEffect);
    read(j, "bAspectRatio", r.bAspectRatio);
    read(j, "fAspectRatio", r.fAspectRatio);
    read(j, "bWeatherChanger", r.bWeatherChanger);
    read(j, "iWeather", r.iWeather);
    read(j, "bTimeChanger", r.bTimeChanger);
    read(j, "iTime", r.iTime);
    read(j, "bHpHud", r.bHpHud);
    read(j, "HPx", r.HPx);
    read(j, "HPy", r.HPy);
    read(j, "bSmallIcons", r.bSmallIcons);
    read(j, "oIcon", r.oIcon);
    read(j, "pIcon", r.pIcon);
    read(j, "b160hp", r.b160hp);
    read(j, "bFPS", r.bFPS);
    read(j, "bNoPostFX", r.bNoPostFX);
}

static void from_json(const json& j, stConfig::stStyle& r)
{
    for (int i = 0; i < ImGuiCol_COUNT; i++)
        read(j, ImGui::GetStyleColorName(i), r.vecTheme[i]);
    read(j, "iTheme", r.iTheme);
    read(j, "iCheckbox", r.iCheckbox);
}

static void from_json(const json& j, stConfig::stHotkeys& r)
{
    read(j, "iWeaponSwitch", r.iWeaponSwitch);
    read(j, "iAutoBikeSpam", r.iAutoBikeSpam);
    read(j, "iScroll", r.iScroll);
    read(j, "iTrigger", r.iTrigger);
    read(j, "iSH", r.iSH);
    read(j, "iRepair", r.iRepair);
    read(j, "iSbiv", r.iSbiv);
    read(j, "iActivate", r.iActivate);
}

void CConfig::Load(size_t index)
{
    json j;

    if (std::ifstream in{ Path / (const char8_t*)Configs[index].c_str() }; in.good())
        in >> j;
    else return;

    Reset();

    read<value_t::object>(j, "Aimbot", g_Config.g_Aimbot);
    read<value_t::object>(j, "Combat", g_Config.g_Combat);
    read<value_t::object>(j, "Player", g_Config.g_Player);
    read<value_t::object>(j, "Vehicle", g_Config.g_Vehicle);
    read<value_t::object>(j, "Visuals", g_Config.g_Visuals);
    read<value_t::object>(j, "Style", g_Config.g_Style);
    read<value_t::object>(j, "Hotkeys", g_Config.g_Hotkeys);
}

void CConfig::Save(size_t index)
{
    std::error_code ec;
    std::filesystem::create_directory(Path, ec);

    if (std::ofstream out{ Path / (const char8_t*)Configs[index].c_str() }; out.good()) 
    {
        json j;
        j["Aimbot"] = g_Config.g_Aimbot;
        j["Combat"] = g_Config.g_Combat;
        j["Player"] = g_Config.g_Player;
        j["Vehicle"] = g_Config.g_Vehicle;
        j["Visuals"] = g_Config.g_Visuals;
        j["Style"] = g_Config.g_Style;
        j["Hotkeys"] = g_Config.g_Hotkeys;

        removeEmptyObjects(j);
        out << std::setw(2) << j;
    }
}

void CConfig::Add(const char* szName)
{
    if (*szName && std::find(Configs.cbegin(), Configs.cend(), szName) == Configs.cend()) 
    {
        Configs.emplace_back(szName);
        Save(Configs.size() - 1);
    }
}

void CConfig::Remove(size_t index)
{
    std::error_code ec;
    std::filesystem::remove(Path / (const char8_t*)Configs[index].c_str(), ec);
    Configs.erase(Configs.cbegin() + index);
}

void CConfig::Rename(size_t item, const char* szName)
{
    std::error_code ec;
    std::filesystem::rename(Path / (const char8_t*)Configs[item].c_str(), Path / (const char8_t*)szName, ec);
    Configs[item] = szName;
}

void CConfig::Reset()
{
    g_Config.g_Aimbot = {};
    g_Config.g_Combat = {};
    g_Config.g_Player = {};
    g_Config.g_Vehicle = {};
    g_Config.g_Visuals = {};
    g_Config.g_Style = {};
    g_Config.g_Hotkeys = {};
}

void CConfig::listConfigs()
{
    Configs.clear();

    std::error_code ec;
    std::transform(std::filesystem::directory_iterator{ Path, ec },
        std::filesystem::directory_iterator{ },
        std::back_inserter(Configs),
        [](const auto& entry) { return std::string{ (const char*)entry.path().filename().u8string().c_str() }; });
}