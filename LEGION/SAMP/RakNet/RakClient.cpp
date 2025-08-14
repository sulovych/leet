#include "D:\LEGION\LEGION\main.h"

CRakClient* pRakClient;

bool CRakClient::RPC(int uniqueID, BitStream* bitStream, PacketPriority priority, PacketReliability reliability, char orderingChannel, bool shiftTimestamp)
{
	Memory::memcpy_safe((void*)(pSAMP->g_dwSAMP_Addr + 0x3A560), "\x55\x8B\xEC\x6A\xFF", 5);
	return (tRPC(vTable[25]))(pSAMP->getInfo()->pRakClientInterface, &uniqueID, bitStream, priority, reliability, orderingChannel, shiftTimestamp);
}

bool CRakClient::Send(BitStream* bitStream, PacketPriority priority, PacketReliability reliability, char orderingChannel)
{
	Memory::memcpy_safe((void*)(pSAMP->g_dwSAMP_Addr + 0x33DC0), "\x6A\xFF\x68\x6B\x0C\xD1\x03", 7);
	Memory::memcpy_safe((void*)(pSAMP->g_dwSAMP_Addr + 0x37490), "\x53\x55\x56\x8D\xA9\xE9\x07\x00\x00", 9);
	return (tSend(vTable[6]))(pSAMP->getInfo()->pRakClientInterface, bitStream, priority, reliability, orderingChannel);
}

bool __fastcall CRakClient::hkRPC(void* _this, void* pUnknown, int* uniqueID, BitStream* bitStream, PacketPriority priority, PacketReliability reliability, char orderingChannel, bool shiftTimestamp)
{
	if (*uniqueID == 185)
	{
		DWORD dwAddress = 0x0;
		BYTE byteSize = 0, byteContent[4] = { 0x0 };

		bitStream->Read(dwAddress);
		bitStream->Read(byteSize);
		for (int i = 0; i < byteSize; i++)
			bitStream->Read(byteContent[i]);

		bitStream->SetWriteOffset(0x28);


		for (auto i = 0; i < byteSize; i++)
		{
			int iAddress = pSecure->isAddressSecured(dwAddress + i);
			if (iAddress != -1)
				bitStream->Write<BYTE>(pSecure->vecMemory[iAddress].origByte);
			else bitStream->Write<BYTE>(byteContent[i]);
		}
	}
	return pRakClient->oRPC(_this, uniqueID, bitStream, priority, reliability, orderingChannel, shiftTimestamp);
}

bool __fastcall CRakClient::hkSend(void* _this, void* Unknown, BitStream* bitStream, PacketPriority priority, PacketReliability reliability, char orderingChannel)
{
	BYTE packetId;
	bitStream->Read(packetId);

	bool bEditBulletSync = false;
	bool bEditAimSync = false;
	bool bEditFootSync = false;
	bool bEditVehicleSync = false;
	bool bEditStatusSync = false;

	if (g_Config.g_Player.bFakeLag)
	{
		static ULONGLONG dwSyncTick = GetTickCount64();
		if (GetTickCount64() - dwSyncTick > (ULONGLONG)g_Config.g_Player.iFakeLag)
			dwSyncTick = GetTickCount64();
		else if (!pSAMP->getPlayers()->pLocalPlayer->onFootData.stSampKeys.keys_aim)
			return false;
	}

	switch (packetId)
	{
		case ID_PLAYER_SYNC:
		{
			if  (g_Config.g_Player.bInvisible)
			{
				stOnFootData OnFootData;
				bitStream->ResetReadPointer();
				bitStream->Read(packetId);
				bitStream->Read((char*)&OnFootData, sizeof(stOnFootData));
					bEditFootSync = true;
					int iNearestVehicle = pSAMP->getNearestVehicle();
					if (iNearestVehicle != -1)
					{
						OnFootData.sSurfingVehicleID = iNearestVehicle;
						if (OnFootData.stSampKeys.keys_aim && OnFootData.stSampKeys.keys_secondaryFire__shoot)
						{
							OnFootData.fSurfingOffsets[2] = -35.0f;
							Math::vect3_zero(OnFootData.fMoveSpeed);
						}
						else
						{
							OnFootData.sSurfingVehicleID = iNearestVehicle;
							OnFootData.fSurfingOffsets[2] = sqrt((float)-1);
						}
					}
					else OnFootData.fPosition[2] = -35.0f;
				if (bEditFootSync)
				{
					bitStream->Reset();
					bitStream->Write((BYTE)ID_PLAYER_SYNC);
					bitStream->Write((PCHAR)&OnFootData, sizeof(stOnFootData));
				}
			}
			break;
		}
		case ID_VEHICLE_SYNC:
		{
			stInCarData InCar;
			memcpy(&InCar, &pSAMP->getPlayers()->pLocalPlayer->inCarData, sizeof(stInCarData));
			if (bEditVehicleSync)
			{
				bitStream->Reset();
				bitStream->Write((BYTE)ID_VEHICLE_SYNC);
				bitStream->Write((PCHAR)&InCar, sizeof(stInCarData));
			}
			break;
		}
		case ID_BULLET_SYNC:
		{
			if (g_Config.g_Visuals.bDMGInformer)
			{
				stBulletData BulletData;
				bitStream->ResetReadPointer();
				bitStream->Read(packetId);
				bitStream->Read((PCHAR)&BulletData, sizeof(stBulletData));
				if (BulletData.byteType == 1)
				{
					CVector vecOrigin(BulletData.fOrigin[0], BulletData.fOrigin[1], BulletData.fOrigin[2]);
					CVector vecTarget(BulletData.fTarget[0], BulletData.fTarget[1], BulletData.fTarget[2]);

					int iBefore = 0;
					for (int i = 1; i < _countof(pVisuals->g_DMGInformer); i++)
						if (pVisuals->g_DMGInformer[i].dwTick < pVisuals->g_DMGInformer[iBefore].dwTick)
							iBefore = i;

					pVisuals->g_DMGInformer[iBefore].iWeapon = pSAMP->getPlayers()->pLocalPlayer->byteCurrentWeapon;
					pVisuals->g_DMGInformer[iBefore].vecPos = vecTarget;
					pVisuals->g_DMGInformer[iBefore].dwTick = GetTickCount64() + (ULONGLONG)(g_Config.g_Visuals.fDMGTick * 1000.f);
				}
			}
			break;
		}
		case ID_AIM_SYNC:
		{
			if (g_Config.g_Visuals.bAspectRatio)
			{
				stAimData AimData;
				bitStream->ResetReadPointer();
				bitStream->Read(packetId);
				bitStream->Read((PCHAR)&AimData, sizeof(stAimData));
				bEditAimSync = true;
				AimData.byteAspectRatio = 0x55;
				if (bEditAimSync)
				{
					bitStream->Reset();
					bitStream->Write((BYTE)ID_AIM_SYNC);
					bitStream->Write((PCHAR)&AimData, sizeof(stAimData));
				}
			}
			break;
		}
	}
	return pRakClient->oSend(_this, bitStream, priority, reliability, orderingChannel);
}