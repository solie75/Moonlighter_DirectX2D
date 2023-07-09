#include "CApplication.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CRenderMgr.h"

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
	// device, context, swapchain, rendertarget buffer&view, depthstencil buffer&view
	CGraphicDevice::GetInst()->GraphicInit(mHwnd, AppWidth, AppHeight);

	// VS & PS Shader, InputLayout
	CGraphicShader::GetInst()->Init();

	CKeyMgr::GetInst()->Init(mHwnd);
	CRenderMgr::GetInst()->Init();

	CGraphicDevice::GetInst()->UpdateViewPort();
}

void CApplication::AppUpdate()
{
	CGraphicDevice::GetInst()->UpdateViewPort();
}

void CApplication::AppRender()
{
	// Print FPS
	CTimeMgr::GetInst()->Render(mHwnd);

	// Clear Target
	CGraphicDevice::GetInst()->ClearRenderTarget();

	// Binds Vertex & Pixel Buffer into IA
	CRenderMgr::GetInst()->BindBuffers();

	// Bind InputLayout into IA
	CGraphicShader::GetInst()->BindInputLayout();

	// Bind VS & PS
	CGraphicShader::GetInst()->BindsShader();

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
