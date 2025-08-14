#pragma once

class CVisuals
{
public:
	CVisuals()
		: fps(0), lastTime(0), frameCount(0) // Инициализация переменных
	{
		oCalculateAspectRatio = (tCalculateAspectRatio)0x6FF420;
		DetourRestoreAfterWith();
		DetourTransactionBegin();
		DetourUpdateThread(GetCurrentThread());
		pSecure->SDetourAttach(&(PVOID&)oCalculateAspectRatio, hkCalculateAspectRatio);
		DetourTransactionCommit();
	}

	~CVisuals()
	{
		DetourRestoreAfterWith();
		DetourTransactionBegin();
		DetourUpdateThread(GetCurrentThread());
		DetourDetach(&(PVOID&)oCalculateAspectRatio, hkCalculateAspectRatio);
		DetourTransactionCommit();
	}

	CPed* pPedSelf;

	void Render();
	void Update();

	bool isPlayerVisible(int iPlayerID, bool bDistance);
	ImColor getESPColor(int iPlayerID);

	void ESP_NameTags(int iPlayerID, CPed* pPed);
	void ESP_Bones(int iPlayerID, CPed* pPed);
	void ESP_Distance(int iPlayerID, CPed* pPed);

	void NoDrugsEffect();
	void WeatherChanger();
	void NoPostFX();
	void HPBAR160();
	void SmallIcons();

	struct stDMGInformer
	{
		CVector vecPos = { 0, 0, 0 };
		int iWeapon = 0;
		float ypos = 500;
		ULONGLONG dwTick = 0;
	} g_DMGInformer[10];

	float fHitmarkerAlpha;

private:
	typedef float(__cdecl* tCalculateAspectRatio)();
	static float __cdecl hkCalculateAspectRatio();
	tCalculateAspectRatio oCalculateAspectRatio;
	int fps; // Текущий FPS
	DWORD lastTime; // Время последнего обновления FPS
	int frameCount; // Количество кадров
};

extern CVisuals* pVisuals;
