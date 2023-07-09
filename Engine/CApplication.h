#pragma once

#include "CSingleton.h"
#include "Header.h"
#include "CGraphicShader.h"

class CApplication
	: CSingleton<CApplication>
{
private:
	HWND mHwnd;
	UINT AppWidth;
	UINT AppHeight;

	//CGraphicDevice* pGraphicDevice;

public:
	CApplication();
	~CApplication();

	void AppRun();
	void AppInit();
	void AppUpdate();
	void AppRender();
	void SetWindow(HWND hwnd, UINT width, UINT height);
};