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
	for (CCamera* cam : mCameras)
	{
		if (cam == nullptr)
		{
			continue;
		}
		cam->Render();
	}
	mCameras.clear();
}

void CCameraMgr::Release()
{
}
