#include "CSceneMgr.h"

CSceneMgr::CSceneMgr()
	: mActiveScene(nullptr)
{
}

CSceneMgr::~CSceneMgr()
{
}

void CSceneMgr::Initialize()
{
}

void CSceneMgr::Update()
{
	CSceneMgr::GetInst()->mActiveScene->Update();
}

void CSceneMgr::LateUpdate()
{
	CSceneMgr::GetInst()->mActiveScene->LateUpdate();
}

void CSceneMgr::Render()
{
	CSceneMgr::GetInst()->mActiveScene->Render();
}

void CSceneMgr::Release()
{
	for (auto& iter : CSceneMgr::GetInst()->mScenes)
	{
		delete iter.second;
		iter.second = nullptr;
	}
}
