#include "D:\LEGION\LEGION\main.h"

CTextures* pTextures;

CTextures::CTextures(IDirect3DDevice9* pDevice)
{
	D3DXCreateTextureFromFileInMemoryEx(pDevice, &byteLogo, sizeof(byteLogo), 210, 63, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &tLogo);
    D3DXCreateTextureFromFileInMemoryEx(pDevice, &byteAIM, sizeof(byteAIM), 24, 24, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &tAIM);
    D3DXCreateTextureFromFileInMemoryEx(pDevice, &bytePlayer, sizeof(bytePlayer), 24, 24, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &tPlayer);
    D3DXCreateTextureFromFileInMemoryEx(pDevice, &byteCar, sizeof(byteCar), 29, 26, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &tCar);
    D3DXCreateTextureFromFileInMemoryEx(pDevice, &byteVisual, sizeof(byteVisual), 28, 28, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &tVisual);
    D3DXCreateTextureFromFileInMemoryEx(pDevice, &byteExtra, sizeof(byteExtra), 28, 28, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &tExtra);
  
    D3DXCreateTextureFromFileInMemoryEx(pDevice, &byteSkin, sizeof(byteSkin), 112, 233, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &tSkin);
    D3DXCreateTextureFromFileInMemoryEx(pDevice, &byteConfig, sizeof(byteConfig), 20, 20, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &tConfig);

    D3DXCreateTextureFromFileInMemoryEx(pDevice, &bytePistol, sizeof(bytePistol), 57, 28, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &tPistol);
    D3DXCreateTextureFromFileInMemoryEx(pDevice, &bytePumpgun, sizeof(bytePumpgun), 90, 27, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &tPumpgun);
    D3DXCreateTextureFromFileInMemoryEx(pDevice, &byteSMG, sizeof(byteSMG), 70, 27, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &tSMG);
    D3DXCreateTextureFromFileInMemoryEx(pDevice, &byteRifle, sizeof(byteRifle), 90, 27, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &tRifle);
    D3DXCreateTextureFromFileInMemoryEx(pDevice, &byteSniper, sizeof(byteSniper), 90, 27, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &tSniper);
}

CTextures::~CTextures()
{
    tLogo->Release();
    tAIM->Release();
    tPlayer->Release();
    tCar->Release();
    tVisual->Release();
    tExtra->Release();
    
    tSkin->Release();
    tConfig->Release();

    tPistol->Release();
    tPumpgun->Release();
    tSMG->Release();
    tRifle ->Release();
    tSniper->Release();
}