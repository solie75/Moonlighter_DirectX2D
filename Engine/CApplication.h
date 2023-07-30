#pragma once

#include "CSingleton.h"
#include "Header.h"
#include "CShader.h"

class CApplication
	: CSingleton<CApplication>
{
private:
	HWND mHwnd;
	UINT AppWidth;
	UINT AppHeight;

	//CDevice* pGraphicDevice;

public:
	CApplication();
	~CApplication();

	void AppRun();
	void AppInit();
	void AppUpdate();
	void AppLateUpdate();
	void AppRender();
	void SetWindow(HWND hwnd, UINT width, UINT height);
	void AppDestroy();
	void AppRelease();
};