#include "CSceneMgr.h"
#include "CVillageScene.h"
#include "CStartMenuScene.h"
#include "CShopScene.h"
#include "CDesertBossScene.h"
#include "CDungeonsEntranceScene.h"
#include "CTestScene.h"

CSceneMgr::CSceneMgr()
	: mActiveScene(nullptr)
{
}

CSceneMgr::~CSceneMgr()
{
}

void CSceneMgr::Initialize()
{
	//AddScene<CStartMenuScene>(L"StartMenuScene");
	//AddScene<CShopScene>(L"CShopScene");
	//AddScene<CDungeonsEntranceScene>(L"CDungeonsEntranceScene");
	//AddScene<CVillageScene>(L"VillageScene");
	//AddScene<CDesertBossScene>(L"CDesertBossScene");
	AddScene<CTestScene>(L"CTestScene");
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

void CSceneMgr::Destroy()
{
	mActiveScene->Destroy();
}
