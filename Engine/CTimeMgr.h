#pragma once
#include "Header.h"
#include "CSingleton.h"

class CTimeMgr
	: public CSingleton<CTimeMgr>
{
private:
	static LARGE_INTEGER	mPrevCount;
	static LARGE_INTEGER	mCurCount;
	static LARGE_INTEGER	mFrequency;

	//UINT			mFPS;
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
LARGE_INTEGER CTimeMgr::mFrequency = {};
LARGE_INTEGER CTimeMgr::mPrevCount = {};
LARGE_INTEGER CTimeMgr::mCurCount = {};