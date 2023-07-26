#include "CCameraMgr.h"

CCameraMgr::CCameraMgr()
{
}

CCameraMgr::~CCameraMgr()
{
}

void CCameraMgr::Initialize()
{
}

void CCameraMgr::Update()
{
}

void CCameraMgr::LateUpdate()
{
}

void CCameraMgr::Render()
{
	typedef std::map<CCamera*, eCameraType>::iterator CamIter;

	for (CamIter iter = mCameras.begin(); iter != mCameras.end();)
	{
		if (nullptr == iter->first)
		{
			continue;
		}
		iter->first->Render();
		iter++;
	}
}

void CCameraMgr::Release()
{
}
