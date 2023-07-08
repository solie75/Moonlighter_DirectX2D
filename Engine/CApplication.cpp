#include "CApplication.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"

CApplication::CApplication()
	: AppHeight(-1)
	, AppWidth(-1)
	, mHwnd(NULL)
{
}

CApplication::~CApplication()
{
}

void CApplication::AppRun()
{
	AppUpdate();
	AppRender();
}

void CApplication::AppInit()
{
	CGraphicDevice::GetInst()->GraphicInit(mHwnd, AppWidth, AppHeight);
	CKeyMgr::GetInst()->Init(mHwnd);
	
}

void CApplication::AppUpdate()
{
}

void CApplication::AppRender()
{
	// Manager Render
	CTimeMgr::GetInst()->Render(mHwnd);

	pGraphicDevice->ClearRenderTarget();
}

void CApplication::SetWindow(HWND hwnd, UINT width, UINT height)
{
	mHwnd = hwnd;
	AppWidth = width;
	AppHeight = height;

	RECT rt = { 0, 0, (LONG)AppWidth, (LONG)AppHeight};

	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);
	SetWindowPos(mHwnd, nullptr, 0, 0, rt.right - rt.left, rt.bottom - rt.top, 0);
	ShowWindow(mHwnd, true);
	UpdateWindow(mHwnd);
}
