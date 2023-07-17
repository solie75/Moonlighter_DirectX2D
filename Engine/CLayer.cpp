#include "CLayer.h"

CLayer::CLayer()
{
}

CLayer::~CLayer()
{
	for (CGameObject* gameObj : mGameObjects)
	{
		if (gameObj == nullptr)
		{
			continue;
		}
		delete gameObj;
		gameObj = nullptr;
	}
}

void CLayer::Initialize()
{
	for (int i = 0; i < mGameObjects.size(); i++)
	{
		mGameObjects[i]->Initialize();
	}
}

void CLayer::Update()
{
	for (int i = 0; i < mGameObjects.size(); i++)
	{
		mGameObjects[i]->Update();
	}
}

void CLayer::LateUpdate()
{
	for (int i = 0; i < mGameObjects.size(); i++)
	{
		mGameObjects[i]->LateUpdate();
	}
}

//void CLayer::Render()
//{
//	for (int i = 0; i < mGameObjects.size(); i++)
//	{
//		mGameObjects[i]->Render();
//	}
//}

void CLayer::AddGameObject(CGameObject* gameObj)
{
	mGameObjects.push_back(gameObj);
}
