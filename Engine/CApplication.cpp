#include "CApplication.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CPathMgr.h"
#include "CRenderMgr.h"
#include "CTexture.h"
#include "CCollisionMgr.h"
#include "CEditor.h"

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
	AppLateUpdate();
	AppRender();
	AppDestroy();
}

void CApplication::AppInit()
{
	// Init Key Setting
	CKeyMgr::GetInst()->Init(mHwnd);

	// Init Path
	CPathMgr::GetInst()->Init();

	// device, context, swapchain, rendertarget buffer&view, depthstencil buffer&view
	CDevice::GetInst()->GraphicInit(mHwnd, AppWidth, AppHeight);

	// Create & Bind triangle vertexses, vertex buffer, index buffer, Constant Buffer, Bind InputLayout into IA, Bind VS & PS
	CRenderMgr::GetInst()->Init();

	CEditor::GetInst()->Initialize();
}

void CApplication::AppUpdate()
{
	CTimeMgr::GetInst()->Update();
	CKeyMgr::GetInst()->Update();
	CRenderMgr::GetInst()->Update();
	CCollisionMgr::GetInst()->Update();
}

void CApplication::AppLateUpdate()
{
	CRenderMgr::GetInst()->LateUpdate();
}

void CApplication::AppRender()
{
	// Print FPS
	CTimeMgr::GetInst()->Render(mHwnd);

	// Clear Target
	CDevice::GetInst()->ClearRenderTarget();
	CDevice::GetInst()->UpdateViewPort();

	// DrawIndexed, Present
	CRenderMgr::GetInst()->Render();

	CDevice::GetInst()->GetSwapChain()->Present(0, 0);
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

void CApplication::AppDestroy()
{
	CSceneMgr::GetInst()->Destroy();
}

void CApplication::AppRelease()
{
	CRenderMgr::GetInst()->Release();
	CEditor::GetInst()->Release();
	CSceneMgr::GetInst()->Release();
}
