#pragma once

namespace Player
{
	extern CPed* pPedSelf;
	extern bool bExitVehicle;
	extern ULONGLONG dwExitTick;

	void Update();
	void AirBreak();
	void AntiStun();
	void FastAnims();
	void InfiniteRun();
	void InfiniteOxygen();
	void NoFall();
	void MegaJump();
	void ChangeSkin();
	void FastRespawn();
	void BikeSpam();
	void HPHeal();
	void GM();
	void SpeedHack();
	void Repair();
	void GMCar();
	void DontFall();
	void Sbiv();
	void AntiAFK();
}