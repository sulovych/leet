#include "D:\LEGION\LEGION\main.h"
#include "D:\LEGION\LEGION\Menu\Menu.h"

CPed* Player::pPedSelf;

void Player::Update()
{
	pPedSelf = FindPlayerPed();
	if (!pPedSelf->IsAlive())
		return;

	AirBreak();
	AntiStun();
	FastAnims();
	InfiniteRun();
	InfiniteOxygen();
	NoFall();
	MegaJump();
	ChangeSkin();
	FastRespawn();
	HPHeal();
	GM();
	SpeedHack();
	Repair();
	GMCar();
	Sbiv();
	DontFall();
	AntiAFK();
}

void Player::AirBreak()
{
	if (g_Config.g_Player.bAirBreak || g_Config.g_Player.bMapRun)
	{
		float fCameraRotation = *(float*)0xB6F178;
		float fSpeed = g_Config.g_Player.bAirBreak ? g_Config.g_Player.iAirBreak / 10.f : g_Config.g_Player.iMapRun / 10.f;
		CVector* nVec = &pPedSelf->m_matrix->pos;
		pPedSelf->m_fCurrentRotation = pPedSelf->m_fAimingRotation = -fCameraRotation;
		pPedSelf->m_vecMoveSpeed.z = 0.f;

		CVehicle* pVehicle = FindPlayerVehicle(-1, false);
		if (pVehicle)
		{
			nVec = &pVehicle->m_matrix->pos;
			float fDiff = Utils::vecLength(pVehicle->m_matrix->pos - *nVec);
			pVehicle->m_matrix->SetRotateZOnly(-fCameraRotation);
			pVehicle->m_matrix->pos.x = nVec->x - sinf(fCameraRotation) * fDiff;
			pVehicle->m_matrix->pos.y = nVec->y - cosf(fCameraRotation) * fDiff;
			pVehicle->m_vecMoveSpeed.x = pVehicle->m_vecMoveSpeed.y = pVehicle->m_vecMoveSpeed.z = 0.f;
		}
		else if (g_Config.g_Player.bAirBreak)
			pPedSelf->m_nPedFlags.bIsStanding = pPedSelf->m_nPedFlags.bWasStanding = pPedSelf->m_nPedFlags.bStayInSamePlace = true;
		else pPedSelf->m_nPedFlags.bIsStanding = true;

		if (isKeyDown('W'))
			nVec->x += sinf(fCameraRotation) * fSpeed, nVec->y += cosf(fCameraRotation) * fSpeed;
		if (isKeyDown('S'))
			nVec->x -= sinf(fCameraRotation) * fSpeed, nVec->y -= cosf(fCameraRotation) * fSpeed;
		if (isKeyDown('D'))
			nVec->x += cosf(fCameraRotation) * fSpeed, nVec->y -= sinf(fCameraRotation) * fSpeed;
		if (isKeyDown('A'))
			nVec->x -= cosf(fCameraRotation) * fSpeed, nVec->y += sinf(fCameraRotation) * fSpeed;

		if (g_Config.g_Player.bAirBreak)
		{
			if (isKeyDown(VK_SPACE))
				nVec->z += fSpeed;
			if (isKeyDown(VK_CONTROL))
				nVec->z -= fSpeed;
		}

		if (g_Config.g_Player.bMapRun)
		{
			CVector vecTarget = pPedSelf->GetPosition();
			float fPosZ = CWorld::FindGroundZForCoord(vecTarget.x, vecTarget.y) + 1.0f;

			CColPoint pCollision;
			CEntity* pCollisionEntity = NULL;
			bool bCollision = CWorld::ProcessLineOfSight(*nVec, vecTarget, pCollision, pCollisionEntity, 1, 0, 0, 1, 1, 0, 0, 0);
			if (bCollision)
				fPosZ = pCollision.m_vecPoint.z + 1.0f;

			float fCheckZ = CWorld::FindGroundZForCoord(vecTarget.x, vecTarget.y);
			if (fPosZ < fCheckZ)
				fPosZ = fCheckZ + 1.0f;

			float fWaterLevel;
			if (((bool(__cdecl*)(float, float, float, float*, bool, CVector*))0x6EB690)(vecTarget.x, vecTarget.y, vecTarget.z, &fWaterLevel, 1, new CVector()))
			{
				if (fPosZ < fWaterLevel)
					fPosZ = fWaterLevel + 1.0f;
			}
			nVec->z = fPosZ;
		}
	}
}

void Player::AntiStun()
{
	if (g_Config.g_Player.bAntiStun && rand() % 100 < g_Config.g_Player.iAntiStunChance)
		pPedSelf->m_nPedFlags.bUpperBodyDamageAnimsOnly = true;
	else pPedSelf->m_nPedFlags.bUpperBodyDamageAnimsOnly = false;
}

void Player::FastAnims()
{
	if (!g_Config.g_Player.bFastAnims)
		return;

	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(pPedSelf, "WOMAN_RUN", g_Config.g_Player.fFastRun);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(pPedSelf, "WOMAN_RUNBUSY", g_Config.g_Player.fFastRun);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(pPedSelf, "WOMAN_RUNPANIC", g_Config.g_Player.fFastRun);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(pPedSelf, "WOMAN_RUNSEXY", g_Config.g_Player.fFastRun);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(pPedSelf, "WOMAN_RUNFATOLD", g_Config.g_Player.fFastRun);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(pPedSelf, "SPRINT_CIVI", g_Config.g_Player.fFastRun);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(pPedSelf, "SPRINT_PANIC", g_Config.g_Player.fFastRun);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(pPedSelf, "SWAT_RUN", g_Config.g_Player.fFastRun);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(pPedSelf, "FATSPRINT", g_Config.g_Player.fFastRun);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(pPedSelf, "IDLE_TIRED", g_Config.g_Player.fFastRun);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(pPedSelf, "MUSCLERUN", g_Config.g_Player.fFastRun);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(pPedSelf, "MUSCLESPRINT", g_Config.g_Player.fFastRun);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(pPedSelf, "RUN_PLAYER", g_Config.g_Player.fFastRun);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(pPedSelf, "RUN_ARMED", g_Config.g_Player.fFastRun);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(pPedSelf, "RUN_1ARMED", g_Config.g_Player.fFastRun);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(pPedSelf, "RUN_ROCKET", g_Config.g_Player.fFastRun);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(pPedSelf, "walk_rocket", g_Config.g_Player.fFastRun);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(pPedSelf, "WALK_start_rocket", g_Config.g_Player.fFastRun);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(pPedSelf, "RUN_GANG1", g_Config.g_Player.fFastRun);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(pPedSelf, "JOG_FEMALEA", g_Config.g_Player.fFastRun);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(pPedSelf, "JOG_MALEA", g_Config.g_Player.fFastRun);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(pPedSelf, "RUN_CIVI", g_Config.g_Player.fFastRun);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(pPedSelf, "RUN_CSAW", g_Config.g_Player.fFastRun);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(pPedSelf, "RUN_FAT", g_Config.g_Player.fFastRun);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(pPedSelf, "RUN_FATOLD", g_Config.g_Player.fFastRun);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(pPedSelf, "RUN_OLD", g_Config.g_Player.fFastRun);

	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(pPedSelf, "CLIMB_PULL", g_Config.g_Player.fFastClimb);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(pPedSelf, "CLIMB_STAND", g_Config.g_Player.fFastClimb);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(pPedSelf, "CLIMB_STAND_FINISH", g_Config.g_Player.fFastClimb);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(pPedSelf, "CLIMB_JUMP", g_Config.g_Player.fFastClimb);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(pPedSelf, "CLIMB_JUMP_B", g_Config.g_Player.fFastClimb);

	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(pPedSelf, "JUMP_GLIDE", g_Config.g_Player.fFastJump);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(pPedSelf, "JUMP_LAND", g_Config.g_Player.fFastJump);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(pPedSelf, "JUMP_LAUNCH", g_Config.g_Player.fFastJump);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(pPedSelf, "JUMP_LAUNCH_R", g_Config.g_Player.fFastJump);

	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(pPedSelf, "FALL_LAND", g_Config.g_Player.fFastFall);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(pPedSelf, "FALL_FRONT", g_Config.g_Player.fFastFall);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(pPedSelf, "FALL_COLLAPSE", g_Config.g_Player.fFastFall);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(pPedSelf, "GETUP_FRONT", g_Config.g_Player.fFastFall);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(pPedSelf, "KO_SKID_FRONT", g_Config.g_Player.fFastFall);

	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(pPedSelf, "SWIM_BREAST", g_Config.g_Player.fFastSwim);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(pPedSelf, "SWIM_CRAWL", g_Config.g_Player.fFastSwim);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(pPedSelf, "SWIM_DIVE_UNDER", g_Config.g_Player.fFastSwim);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(pPedSelf, "SWIM_GLIDE", g_Config.g_Player.fFastSwim);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(pPedSelf, "SWIM_JUMPOUT", g_Config.g_Player.fFastSwim);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(pPedSelf, "SWIM_UNDER", g_Config.g_Player.fFastSwim);

	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(pPedSelf, "DAM_ARML_FRMBK", g_Config.g_Player.fFastStuns);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(pPedSelf, "DAM_ARML_FRMFT", g_Config.g_Player.fFastStuns);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(pPedSelf, "DAM_ARML_FRMLT", g_Config.g_Player.fFastStuns);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(pPedSelf, "DAM_ARMR_FRMBK", g_Config.g_Player.fFastStuns);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(pPedSelf, "DAM_ARMR_FRMFT", g_Config.g_Player.fFastStuns);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(pPedSelf, "DAM_ARMR_FRMRT", g_Config.g_Player.fFastStuns);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(pPedSelf, "DAM_LEGL_FRMBK", g_Config.g_Player.fFastStuns);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(pPedSelf, "DAM_LEGL_FRMFT", g_Config.g_Player.fFastStuns);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(pPedSelf, "DAM_LEGL_FRMLT", g_Config.g_Player.fFastStuns);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(pPedSelf, "DAM_LEGR_FRMBK", g_Config.g_Player.fFastStuns);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(pPedSelf, "DAM_LEGR_FRMFT", g_Config.g_Player.fFastStuns);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(pPedSelf, "DAM_LEGR_FRMRT", g_Config.g_Player.fFastStuns);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(pPedSelf, "DAM_STOMACH_FRMBK", g_Config.g_Player.fFastStuns);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(pPedSelf, "DAM_STOMACH_FRMFT", g_Config.g_Player.fFastStuns);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(pPedSelf, "DAM_STOMACH_FRMLT", g_Config.g_Player.fFastStuns);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(pPedSelf, "DAM_STOMACH_FRMRT", g_Config.g_Player.fFastStuns);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(pPedSelf, "SHOT_RIGHTP", g_Config.g_Player.fFastStuns);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(pPedSelf, "SHOT_LEFTP", g_Config.g_Player.fFastStuns);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(pPedSelf, "SHOT_PARTIAL_B", g_Config.g_Player.fFastStuns);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(pPedSelf, "SHOT_PARTIAL", g_Config.g_Player.fFastStuns);

	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(pPedSelf, "CROUCH_ROLL_R", g_Config.g_Player.fFastGunMov);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(pPedSelf, "CROUCH_ROLL_L", g_Config.g_Player.fFastGunMov);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(pPedSelf, "GUNCROUCHFWD", g_Config.g_Player.fFastGunMov);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(pPedSelf, "GUNCROUCHBWD", g_Config.g_Player.fFastGunMov);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(pPedSelf, "GUNMOVE_BWD", g_Config.g_Player.fFastGunMov);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(pPedSelf, "GUNMOVE_FWD", g_Config.g_Player.fFastGunMov);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(pPedSelf, "GUNMOVE_R", g_Config.g_Player.fFastGunMov);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(pPedSelf, "GUNMOVE_L", g_Config.g_Player.fFastGunMov);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(pPedSelf, "GUN_2_IDLE", g_Config.g_Player.fFastGunMov);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(pPedSelf, "GUN_BUTT", g_Config.g_Player.fFastGunMov);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(pPedSelf, "GUN_BUTT_CROUCH", g_Config.g_Player.fFastGunMov);

	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(pPedSelf, "BAT_1", g_Config.g_Player.fFastFight);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(pPedSelf, "BAT_2", g_Config.g_Player.fFastFight);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(pPedSelf, "BAT_3", g_Config.g_Player.fFastFight);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(pPedSelf, "BAT_4", g_Config.g_Player.fFastFight);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(pPedSelf, "FIGHTB_1", g_Config.g_Player.fFastFight);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(pPedSelf, "FIGHTB_2", g_Config.g_Player.fFastFight);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(pPedSelf, "FIGHTB_3", g_Config.g_Player.fFastFight);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(pPedSelf, "FIGHTB_G", g_Config.g_Player.fFastFight);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(pPedSelf, "FIGHTB_M", g_Config.g_Player.fFastFight);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(pPedSelf, "FIGHTC_1", g_Config.g_Player.fFastFight);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(pPedSelf, "FIGHTC_2", g_Config.g_Player.fFastFight);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(pPedSelf, "FIGHTC_3", g_Config.g_Player.fFastFight);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(pPedSelf, "FIGHTC_G", g_Config.g_Player.fFastFight);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(pPedSelf, "FIGHTC_M", g_Config.g_Player.fFastFight);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(pPedSelf, "FIGHTD_1", g_Config.g_Player.fFastFight);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(pPedSelf, "FIGHTD_2", g_Config.g_Player.fFastFight);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(pPedSelf, "FIGHTD_3", g_Config.g_Player.fFastFight);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(pPedSelf, "FIGHTD_G", g_Config.g_Player.fFastFight);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(pPedSelf, "FIGHTD_M", g_Config.g_Player.fFastFight);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(pPedSelf, "FIGHTKICK", g_Config.g_Player.fFastFight);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(pPedSelf, "FIGHTKICK_B", g_Config.g_Player.fFastFight);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(pPedSelf, "FIGHTA_1", g_Config.g_Player.fFastFight);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(pPedSelf, "FIGHTA_2", g_Config.g_Player.fFastFight);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(pPedSelf, "FIGHTA_3", g_Config.g_Player.fFastFight);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(pPedSelf, "FIGHTA_G", g_Config.g_Player.fFastFight);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(pPedSelf, "FIGHTA_M", g_Config.g_Player.fFastFight);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(pPedSelf, "BAT_HIT_1", g_Config.g_Player.fFastFight);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(pPedSelf, "BAT_HIT_2", g_Config.g_Player.fFastFight);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(pPedSelf, "BAT_HIT_3", g_Config.g_Player.fFastFight);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(pPedSelf, "HITB_1", g_Config.g_Player.fFastFight);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(pPedSelf, "HITB_2", g_Config.g_Player.fFastFight);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(pPedSelf, "HITB_3", g_Config.g_Player.fFastFight);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(pPedSelf, "HITC_1", g_Config.g_Player.fFastFight);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(pPedSelf, "HITC_2", g_Config.g_Player.fFastFight);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(pPedSelf, "HITC_3", g_Config.g_Player.fFastFight);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(pPedSelf, "HITD_1", g_Config.g_Player.fFastFight);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(pPedSelf, "HITD_2", g_Config.g_Player.fFastFight);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(pPedSelf, "HITD_3", g_Config.g_Player.fFastFight);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(pPedSelf, "HIT_FIGHTKICK", g_Config.g_Player.fFastFight);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(pPedSelf, "HIT_FIGHTKICK_B", g_Config.g_Player.fFastFight);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(pPedSelf, "HITA_1", g_Config.g_Player.fFastFight);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(pPedSelf, "HITA_2", g_Config.g_Player.fFastFight);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(pPedSelf, "HITA_3", g_Config.g_Player.fFastFight);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(pPedSelf, "HIT_BACK", g_Config.g_Player.fFastFight);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(pPedSelf, "HIT_BEHIND", g_Config.g_Player.fFastFight);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(pPedSelf, "HIT_FRONT", g_Config.g_Player.fFastFight);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(pPedSelf, "HIT_GUN_BUTT", g_Config.g_Player.fFastFight);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(pPedSelf, "HIT_L", g_Config.g_Player.fFastFight);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(pPedSelf, "HIT_R", g_Config.g_Player.fFastFight);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(pPedSelf, "HIT_WALK", g_Config.g_Player.fFastFight);
	plugin::Command<plugin::Commands::SET_CHAR_ANIM_SPEED>(pPedSelf, "HIT_WALL", g_Config.g_Player.fFastFight);
}

void Player::InfiniteRun()
{
	if (g_Config.g_Player.bInfiniteRun && pPedSelf->m_pPlayerData->m_fTimeCanRun < 100.f)
		FindPlayerPed()->ResetSprintEnergy();
}

void Player::InfiniteOxygen()
{
	if (g_Config.g_Player.bInfiniteOxygen && pPedSelf->m_pPlayerData->m_fBreath < 100.f)
		FindPlayerPed()->ResetPlayerBreath();
}

void Player::NoFall()
{
	if (!g_Config.g_Player.bNoFall)
		return;

	bool bOutResult = false; CEntity* pOutEntity;
	if (Utils::isPlayingAnimation(pPedSelf, "FALL_FALL") && pPedSelf->GetPosition().z - CWorld::FindGroundZFor3DCoord(pPedSelf->GetPosition().x, pPedSelf->GetPosition().y, pPedSelf->GetPosition().z, &bOutResult, &pOutEntity) < 1.5f)
	{
		Utils::DisembarkInstantly();
		pPedSelf->m_vecMoveSpeed.x = pPedSelf->m_vecMoveSpeed.y = pPedSelf->m_vecMoveSpeed.z = 0.f;
	}
}

void Player::MegaJump()
{
	static bool bMegaJump = false;
	if (g_Config.g_Player.bMegaJump)
	{
		pSecure->Write(0x8703C0, 8.5f * g_Config.g_Player.fMegaJump);
		bMegaJump = true;
	}
	else if (bMegaJump)
	{
		*(float*)0x8703C0 = 8.5f;
		bMegaJump = false;
	}
}

void Player::ChangeSkin()
{
	int iSkin = g_Config.g_Player.iSkinID;
	if (g_Config.g_Player.bChangeSkin && iSkin >= 0 && iSkin <= 311 && iSkin != 74 && pPedSelf->m_nModelIndex != iSkin)
	{
		CStreaming::RequestModel(iSkin, 0);
		CStreaming::LoadAllRequestedModels(false);
		pPedSelf->SetModelIndex(iSkin);
	}
}

void Player::FastRespawn()
{
	if (g_Config.g_Player.bFastRespawn && pPedSelf->m_fHealth == 0)
		pPedSelf->m_fHealth = 99;
}

void Player::BikeSpam()
{
	if (g_Config.g_Vehicle.bAutoBikeSpam && FindPlayerVehicle(-1, false))
	{
		int16_t* i16KeyState = (int16_t*)0xB73458;
		if (isKeyDown(g_Config.g_Hotkeys.iAutoBikeSpam) && reinterpret_cast<CVehicleModelInfo*>(CModelInfo::ms_modelInfoPtrs[FindPlayerVehicle(-1, false)->m_nModelIndex])->m_nVehicleType == VEHICLE_BMX)
		{
			if (i16KeyState[BUTTON_CROSS] == 0)
				pKeyHook->g_GameKeyState[BUTTON_CROSS] = { 0xFF, true };
			else pKeyHook->g_GameKeyState[BUTTON_CROSS] = { 0x0, true };
		}
		if (isKeyDown(g_Config.g_Hotkeys.iAutoBikeSpam) && reinterpret_cast<CVehicleModelInfo*>(CModelInfo::ms_modelInfoPtrs[FindPlayerVehicle(-1, false)->m_nModelIndex])->m_nVehicleType == VEHICLE_BIKE)
		{
			if (i16KeyState[BUTTON_LEFT_STICK_Y] == 0)
				pKeyHook->g_GameKeyState[BUTTON_LEFT_STICK_Y] = { -0x80, true };
			else pKeyHook->g_GameKeyState[BUTTON_LEFT_STICK_Y] = { 0x0, true };
		}
	}
}

void Player::HPHeal()
{
	static bool bHPHeal = false;
	if (g_Config.g_Player.bHPHeal)
	{ 
		static unsigned long dwStartTick{ GetTickCount() };
		if (GetTickCount64() - dwStartTick > 3500) 
		{
			if (pPedSelf->m_fHealth < 98)
			{
				*reinterpret_cast<float*>(*reinterpret_cast<DWORD*>(0xB6F5F0) + 0x540) += 2.0f;
				dwStartTick = GetTickCount64();
			}
			else if (pPedSelf->m_fHealth = 99)
			{
				*reinterpret_cast<float*>(*reinterpret_cast<DWORD*>(0xB6F5F0) + 0x540) += 1.0f;
				dwStartTick = GetTickCount64();
			}
			else if (pPedSelf->m_fHealth = 100)
				dwStartTick = GetTickCount64();
		}	
		bHPHeal = true;
	}
	else if (bHPHeal)
	{
		bHPHeal = false;
	}
}

void Player::GM()
{
	if (g_Config.g_Player.bGM)
	{
		pPedSelf->m_nPhysicalFlags.bFireProof = true;
		pPedSelf->m_nPhysicalFlags.bCollisionProof = true;
		pPedSelf->m_nPhysicalFlags.bMeeleProof = true;
		pPedSelf->m_nPhysicalFlags.bInvulnerable = true;
		pPedSelf->m_nPhysicalFlags.bExplosionProof = true;
		pPedSelf->m_nPhysicalFlags.bBulletProof = true;
		pPedSelf->m_nPhysicalFlags.bInvulnerable = true;
	}
	else
	{
		pPedSelf->m_nPhysicalFlags.bFireProof = false;
		pPedSelf->m_nPhysicalFlags.bCollisionProof = false;
		pPedSelf->m_nPhysicalFlags.bMeeleProof = false;
		pPedSelf->m_nPhysicalFlags.bInvulnerable = false;
		pPedSelf->m_nPhysicalFlags.bExplosionProof = false;
		pPedSelf->m_nPhysicalFlags.bBulletProof = false;
		pPedSelf->m_nPhysicalFlags.bInvulnerable = false;
	}
}

void Player::Sbiv()
{
	if (g_Config.g_Player.bSbiv && isKeyPressed(g_Config.g_Hotkeys.iSbiv))
	{
			pPedSelf->m_vecMoveSpeed.x = pPedSelf->m_vecMoveSpeed.y = pPedSelf->m_vecMoveSpeed.z = 0.f;
			Utils::DisembarkInstantly();
	}
}

void Player::SpeedHack()
{
	CVehicle* pVehicle = FindPlayerVehicle(-1, false);
	if (g_Config.g_Vehicle.bSH && (isKeyDown('W') || isKeyDown('S')) && FindPlayerVehicle(-1, false) && isKeyDown(g_Config.g_Hotkeys.iSH) && pVehicle->IsDriver(pPedSelf))
	{
		static unsigned long dwStartTick{ GetTickCount() };
		if (GetTickCount64() - dwStartTick > 13)
		{
			float VSpeed = sqrtf(pVehicle->m_vecMoveSpeed.x * pVehicle->m_vecMoveSpeed.x + pVehicle->m_vecMoveSpeed.y * pVehicle->m_vecMoveSpeed.y + pVehicle->m_vecMoveSpeed.z * pVehicle->m_vecMoveSpeed.z) * 100;
			if (VSpeed < g_Config.g_Vehicle.bSHLimit && VSpeed > 0)
			{
				VSpeed = VSpeed + g_Config.g_Vehicle.bSHpower/10;
				pVehicle->m_vecMoveSpeed.x = (VSpeed / 100) * (pVehicle->m_vecMoveSpeed.x / sqrtf(pVehicle->m_vecMoveSpeed.x * pVehicle->m_vecMoveSpeed.x + pVehicle->m_vecMoveSpeed.y * pVehicle->m_vecMoveSpeed.y + pVehicle->m_vecMoveSpeed.z * pVehicle->m_vecMoveSpeed.z));
				pVehicle->m_vecMoveSpeed.y = (VSpeed / 100) * (pVehicle->m_vecMoveSpeed.y / sqrtf(pVehicle->m_vecMoveSpeed.x * pVehicle->m_vecMoveSpeed.x + pVehicle->m_vecMoveSpeed.y * pVehicle->m_vecMoveSpeed.y + pVehicle->m_vecMoveSpeed.z * pVehicle->m_vecMoveSpeed.z));
				pVehicle->m_vecMoveSpeed.z = (VSpeed / 100) * (pVehicle->m_vecMoveSpeed.z / sqrtf(pVehicle->m_vecMoveSpeed.x * pVehicle->m_vecMoveSpeed.x + pVehicle->m_vecMoveSpeed.y * pVehicle->m_vecMoveSpeed.y + pVehicle->m_vecMoveSpeed.z * pVehicle->m_vecMoveSpeed.z));
				dwStartTick = GetTickCount64();
			}
		}
	}
}

void Player::Repair()
{
	CVehicle* pVehicle = FindPlayerVehicle(-1, false);
	if (isKeyPressed(g_Config.g_Hotkeys.iRepair) && FindPlayerVehicle(-1, false))
	{
		if (g_Config.g_Vehicle.bFlip)
		{
			CVector* nVec = &pPedSelf->m_matrix->pos;
			nVec = &pVehicle->m_matrix->pos;
			pVehicle->m_matrix->SetRotateZOnly(pPedSelf->m_fCurrentRotation);
			pVehicle->m_matrix->pos.y = nVec->y - cosf(pPedSelf->m_fCurrentRotation);
		}
		if (g_Config.g_Vehicle.bRepair)
		{
			pVehicle->m_fHealth = 1000.0f;
			pVehicle->Fix();
		}
	}
}

void Player::GMCar()
{
	if (g_Config.g_Vehicle.bGMCar && FindPlayerVehicle(-1, false))
	{
		CVehicle* pVehicle = FindPlayerVehicle(-1, false);
		pVehicle->m_fHealth = 1000.0f;
		pVehicle->m_nPhysicalFlags.bBulletProof = true;
		pVehicle->m_nPhysicalFlags.bExplosionProof = true;
		pVehicle->m_nPhysicalFlags.bFireProof = true;
		pVehicle->m_nPhysicalFlags.bMeeleProof = true;
		pVehicle->m_nPhysicalFlags.bCollisionProof = true;
		pVehicle->m_nPhysicalFlags.bInvulnerable = true;
		pVehicle->Fix();
	}
	else if (!g_Config.g_Vehicle.bGMCar && FindPlayerVehicle(-1, false))
	{
		CVehicle* pVehicle = FindPlayerVehicle(-1, false);
		pVehicle->m_nPhysicalFlags.bBulletProof = false;
		pVehicle->m_nPhysicalFlags.bExplosionProof = false;
		pVehicle->m_nPhysicalFlags.bFireProof = false;
		pVehicle->m_nPhysicalFlags.bMeeleProof = false;
		pVehicle->m_nPhysicalFlags.bCollisionProof = false;
		pVehicle->m_nPhysicalFlags.bInvulnerable = false;
	}
}

void Player::DontFall()
{
	if (g_Config.g_Vehicle.bDontFall)
		pPedSelf->m_nPedFlags.CantBeKnockedOffBike = true;
	else
		pPedSelf->m_nPedFlags.CantBeKnockedOffBike = false;
}

void Player::AntiAFK()
{
	*(std::uint8_t*)0x747FB6 = g_Config.g_Player.bAntiafk;
	*(std::uint8_t*)0x74805A = g_Config.g_Player.bAntiafk;
	std::memcpy((void*)0x74542B, g_Config.g_Player.bAntiafk ? "\x90\x90\x90\x90\x90\x90\x90\x90" : "\x50\x51\xFF\x15\x00\x83\x85\x00", 8);
	std::memcpy((void*)0x53EA88, g_Config.g_Player.bAntiafk ? "\x90\x90\x90\x90\x90\x90" : "\x0F\x84\x7B\x01\x00\x00", 6);
}