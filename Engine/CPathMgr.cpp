#include "CPathMgr.h"

CPathMgr::CPathMgr()
	: mContentPath{}
{
}

CPathMgr::~CPathMgr()
{
}

void CPathMgr::init()
{
	GetCurrentDirectory(256, mContentPath);

	int ilen = (int)wcslen(mContentPath);

	for (int i = ilen - 1; i >= 0; --i)
	{
		if (L'\\' == mContentPath[i])
		{
			mContentPath[i] = 0;
			break;
		}
	}

	wcscat_s(mContentPath, L"\\bin\\content");
}
