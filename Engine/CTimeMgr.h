#pragma once
#include "Header.h"
#include "CSingleton.h"

class CTimeMgr
	: public CSingleton<CTimeMgr>
{
private:
	LARGE_INTEGER	mPrevCount;
	LARGE_INTEGER	mCurCount;
	LARGE_INTEGER	mFrequency;

	UINT			mFPS;
	static double	mDeltaTime;
	static double	mTime;

public:
	CTimeMgr();
	~CTimeMgr();

	void Update();
	void Render(HWND _hWnd);

	__forceinline static double GetDeltaTime() { return mDeltaTime; }
};

double CTimeMgr::mDeltaTime = 0.0l;
double CTimeMgr::mTime = 0.0f;