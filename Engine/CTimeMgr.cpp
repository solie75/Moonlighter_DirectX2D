#include "CTimeMgr.h"

CTimeMgr::CTimeMgr()
	: mPrevCount{}
	, mCurCount{}
	, mFrequency{}
	, mFPS(0)
	//, mDeltaTime(0.f)
	//, mTime(0.f)
{
	QueryPerformanceFrequency(&mFrequency);
	QueryPerformanceCounter(&mCurCount);
	QueryPerformanceCounter(&mPrevCount);
}

CTimeMgr::~CTimeMgr()
{
}

void CTimeMgr::Update()
{
	QueryPerformanceCounter(&mCurCount);

	mDeltaTime = (double)(mCurCount.QuadPart - mPrevCount.QuadPart) / (double)(mFrequency.QuadPart);
	++mFPS;
	mTime += mDeltaTime;
	mPrevCount.QuadPart = mCurCount.QuadPart;
}

void CTimeMgr::Render(HWND _hWnd)
{
	if (1.f <= mTime)
	{
		wchar_t szfloat[256] = {};
		swprintf_s(szfloat, L"FPS : %d, DT : %f", mFPS, mDeltaTime);
		SetWindowText(_hWnd, szfloat);

		mFPS = 0;
		mTime = 0;
	}
}
