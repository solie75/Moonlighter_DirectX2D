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
	double			mDeltaTime;
	double			mTime;

public:
	CTimeMgr();
	~CTimeMgr();

	void Update();
	void Render(HWND _hWnd);

	float GetDeltaTime() { return mDeltaTime; }
};

