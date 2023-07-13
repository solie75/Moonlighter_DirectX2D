#include "CApplication.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CRenderMgr.h"
#include "CTexture.h"

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
	// Init Key Setting
	CKeyMgr::GetInst()->Init(mHwnd);

	// device, context, swapchain, rendertarget buffer&view, depthstencil buffer&view
	CDevice::GetInst()->GraphicInit(mHwnd, AppWidth, AppHeight);

	// Create & Bind triangle vertexses, vertex buffer, index buffer, Constant Buffer, Bind InputLayout into IA, Bind VS & PS
	CRenderMgr::GetInst()->Init();
}

void CApplication::AppUpdate()
{
	CDevice::GetInst()->UpdateViewPort();
}

void CApplication::AppRender()
{
	// Print FPS
	CTimeMgr::GetInst()->Render(mHwnd);

	// Clear Target
	CDevice::GetInst()->ClearRenderTarget();

	// DrawIndexed, Present
	CRenderMgr::GetInst()->Render();

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
