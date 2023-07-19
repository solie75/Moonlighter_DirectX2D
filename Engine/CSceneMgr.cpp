#include "CSceneMgr.h"
#include "CVillageScene.h"
#include "CStartMenuScene.h"
#include "CShopScene.h"
#include "CPlayScene.h"

CSceneMgr::CSceneMgr()
	: mActiveScene(nullptr)
{
}

CSceneMgr::~CSceneMgr()
{
}

void CSceneMgr::Initialize()
{
	AddScene<CPlayScene>(L"TestScene");
	AddScene<CStartMenuScene>(L"StartMenuScene");
	AddScene<CVillageScene>(L"VillageScene");
	AddScene<CShopScene>(L"CShopScene");
}

void CSceneMgr::Update()
{
	mActiveScene->Update();
}

void CSceneMgr::LateUpdate()
{
	mActiveScene->LateUpdate();
}

void CSceneMgr::Render()
{
//	mActiveScene->Render();
}

void CSceneMgr::Release()
{
	for (auto& iter : CSceneMgr::GetInst()->mScenes)
	{
		delete iter.second;
		iter.second = nullptr;
	}
}
