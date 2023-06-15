#pragma once

#include "CSingleton.h"
#include "Header.h"


class CApplication
	: CSingleton<CApplication>
{
private:
	HWND mHwnd;
	UINT AppWidth;
	UINT AppHeight;

	//std::unique_ptr<CGraphicDevice> pGraphicDevice;

public:
	CApplication();
	~CApplication();

	void AppRun();
	void AppInitialize();
	void AppUpdate();
	void AppRender();
	void SetWindow(HWND hwnd, UINT width, UINT height);

	//CGraphicDevice* GetDevice()
	//{
	//	//return pGraphicDevice.get();
	//}
};