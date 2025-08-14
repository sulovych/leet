#include "D:\LEGION\LEGION\main.h"

void Combat::Update()
{
	NoReload();
	AllowCBUG();
	FastGun();
	RecoilControl();
	FastScroll();
}

void Combat::NoReload()
{
	if (!g_Config.g_Combat.bNoReload)
		return;

	int iWeapon = FindPlayerPed()->m_aWeapons[FindPlayerPed()->m_nActiveWeaponSlot].m_nType;
	if (iWeapon >= 22 && iWeapon <= 42 && FindPlayerPed()->m_aWeapons[FindPlayerPed()->m_nActiveWeaponSlot].m_nAmmoInClip == 1)
		FindPlayerPed()->GiveWeapon((eWeaponType)iWeapon, 0, false);
}

void Combat::AllowCBUG()
{
	static bool bAllowCBug = false;
	if (g_Config.g_Combat.bAllowCBug)
	{
			pSecure->memcpy_safe((void*)(pSAMP->g_dwSAMP_Addr + 0x0168E0), "\xC3\x90", 2);
			pSecure->memcpy_safe((void*)(pSAMP->g_dwSAMP_Addr + 0x016FA0), "\xC3\x90", 2);
			pSecure->memcpy_safe((void*)(pSAMP->g_dwSAMP_Addr + 0x015530), "\xC3\x90", 2);
			pSecure->memcpy_safe((void*)(pSAMP->g_dwSAMP_Addr + 0x015F40), "\xC3\x90", 2);
		bAllowCBug = true;
	}
	else if (bAllowCBug)
	{
		Memory::memcpy_safe((void*)(pSAMP->g_dwSAMP_Addr + 0x0168E0), "\xE9\x49", 2);
		Memory::memcpy_safe((void*)(pSAMP->g_dwSAMP_Addr + 0x016FA0), "\x55\x8B", 2);
		Memory::memcpy_safe((void*)(pSAMP->g_dwSAMP_Addr + 0x015530), "\xE9\x18", 2);
		Memory::memcpy_safe((void*)(pSAMP->g_dwSAMP_Addr + 0x015F40), "\xE9\x2C", 2);
		bAllowCBug = false;
	}
}

void Combat::FastGun()
{
	if (!g_Config.g_Combat.bRapidFire)
		return;

	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(FindPlayerPed(), "PYTHON_CROUCHFIRE", g_Config.g_Combat.fFastPistols);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(FindPlayerPed(), "PYTHON_FIRE", g_Config.g_Combat.fFastPistols);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(FindPlayerPed(), "PYTHON_FIRE_POOR", g_Config.g_Combat.fFastPistols);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(FindPlayerPed(), "PYTHON_RELOAD", g_Config.g_Combat.fFastPistols);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(FindPlayerPed(), "PYTHON_CROUCHRELOAD", g_Config.g_Combat.fFastPistols);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(FindPlayerPed(), "COLT45_CROUCHFIRE", g_Config.g_Combat.fFastPistols);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(FindPlayerPed(), "COLT45_RELOAD", g_Config.g_Combat.fFastPistols);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(FindPlayerPed(), "COLT45_FIRE", g_Config.g_Combat.fFastPistols);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(FindPlayerPed(), "COLT45_CROUCHRELOAD", g_Config.g_Combat.fFastPistols);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(FindPlayerPed(), "SILENCED_CROUCH_FIRE", g_Config.g_Combat.fFastPistols);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(FindPlayerPed(), "SILENCED_FIRE", g_Config.g_Combat.fFastPistols);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(FindPlayerPed(), "SILENCED_RELOAD", g_Config.g_Combat.fFastPistols);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(FindPlayerPed(), "SILENCED_CROUCH_RELOAD", g_Config.g_Combat.fFastPistols);

	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(FindPlayerPed(), "TEC_crouchfire", g_Config.g_Combat.fFastSmgs);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(FindPlayerPed(), "TEC_fire", g_Config.g_Combat.fFastSmgs);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(FindPlayerPed(), "TEC_crouchreload", g_Config.g_Combat.fFastSmgs);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(FindPlayerPed(), "TEC_reload", g_Config.g_Combat.fFastSmgs);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(FindPlayerPed(), "UZI_crouchfire", g_Config.g_Combat.fFastSmgs);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(FindPlayerPed(), "UZI_fire", g_Config.g_Combat.fFastSmgs);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(FindPlayerPed(), "UZI_fire_POOR", g_Config.g_Combat.fFastSmgs);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(FindPlayerPed(), "UZI_crouchreload", g_Config.g_Combat.fFastSmgs);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(FindPlayerPed(), "UZI_reload", g_Config.g_Combat.fFastSmgs);

	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(FindPlayerPed(), "SHOTGUN_CROUCHFIRE", g_Config.g_Combat.fFastShotguns);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(FindPlayerPed(), "SHOTGUN_FIRE", g_Config.g_Combat.fFastShotguns);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(FindPlayerPed(), "SHOTGUN_FIRE_POOR", g_Config.g_Combat.fFastShotguns);

	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(FindPlayerPed(), "RIFLE_CROUCHFIRE", g_Config.g_Combat.fFastRifles);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(FindPlayerPed(), "RIFLE_FIRE", g_Config.g_Combat.fFastRifles);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(FindPlayerPed(), "RIFLE_FIRE_POOR", g_Config.g_Combat.fFastRifles);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(FindPlayerPed(), "RIFLE_CROUCHLOAD", g_Config.g_Combat.fFastRifles);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(FindPlayerPed(), "RIFLE_LOAD", g_Config.g_Combat.fFastRifles);

	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(FindPlayerPed(), "WEAPON_sniper", g_Config.g_Combat.fFastSniperRifles);

	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(FindPlayerPed(), "idle_rocket", g_Config.g_Combat.fFastOther);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(FindPlayerPed(), "Rocket_Fire", g_Config.g_Combat.fFastOther);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(FindPlayerPed(), "buddy_crouchfire", g_Config.g_Combat.fFastOther);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(FindPlayerPed(), "buddy_fire", g_Config.g_Combat.fFastOther);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(FindPlayerPed(), "buddy_fire_POOR", g_Config.g_Combat.fFastOther);
}

void Combat::RecoilControl()
{
	if (g_Config.g_Combat.bRecoilctrl)
	{
		float recoilValue = 0.0f;
		if (g_Config.g_Combat.fRecoil == 0) 
			recoilValue = 0.0f;
		else if (g_Config.g_Combat.fRecoil > 0 && g_Config.g_Combat.fRecoil <= 100) 
			recoilValue = g_Config.g_Combat.fRecoil / 100.0f; 

		unsigned char bytes[5];
		bytes[0] = 0xBE; 
		std::memcpy(bytes + 1, &recoilValue, sizeof(float)); 
		Memory::memcpy_safe((void*)0x8D610F, bytes, sizeof(bytes));
	}
	else
		Memory::memcpy_safe((void*)0x8D610F, "\xBE\x00\x00\x40\x3F", 5);
}

void Combat::WeaponSwitcher()
{
	if (g_Config.g_Combat.bWeaponSwitcher && !FindPlayerVehicle(-1, false))
	{
		for (size_t i = 0; i < g_Config.g_Hotkeys.iWeaponSwitch.size(); i++)
		{
			if (isKeyPressed(g_Config.g_Hotkeys.iWeaponSwitch[i]))
			{
				if (g_Config.g_Combat.bFastSwitch)
					FindPlayerPed()->SetCurrentWeapon(i + 2);
				else *(DWORD*)0xB7CDBC = i + 2;
			}
		}
	}
}

void Combat::FastScroll()
{
	if (g_Config.g_Combat.bFastScroll)
	{
		if ( FindPlayerPed()->m_nActiveWeaponSlot !=0 && (isKeyPressed(g_Config.g_Hotkeys.iScroll)) )
		FindPlayerPed()->m_nActiveWeaponSlot = 0;
	}
}