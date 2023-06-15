#pragma once
#include "CSingleton.h"
#include "Header.h"

class CPathMgr
	: public CSingleton<CPathMgr>
{
private:
	wchar_t mContentPath[256];

public:
	CPathMgr();
	~CPathMgr();
	void init();

public:
	const wchar_t* GetContextPath() { return mContentPath; }
};

