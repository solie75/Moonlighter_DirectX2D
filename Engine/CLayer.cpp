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

void CLayer::Destroy()
{
	// Dead Object list
	std::set<CGameObject*> deadGameObjs = {};
	for (CGameObject* gameObj : mGameObjects)
	{
		if (gameObj->GetState() == CGameObject::eObjectState::Dead)
		{
			deadGameObjs.insert(gameObj);
		}
	}

	// layer ���� Dead ���� ������Ʈ ����
	typedef std::vector<CGameObject*>::iterator GameObjIter;
	for (GameObjIter iter = mGameObjects.begin(); iter != mGameObjects.end();)
	{
		std::set<CGameObject*>::iterator deleteIter = deadGameObjs.find(*(iter));
		if (deleteIter != deadGameObjs.end())
		{
			iter = mGameObjects.erase(iter);
			continue;
		}
		iter++;
	}

	// �޸� ����
	for (CGameObject* gameObj : deadGameObjs)
	{
		delete gameObj;
		gameObj = nullptr;
	}
}

void CLayer::AddGameObject(CGameObject* gameObj)
{
	mGameObjects.push_back(gameObj);
}

//CGameObject* CLayer::FindGameObject(std::wstring objName)
//{
//	for (int i = 0; i < mGameObjects.size(); i++)
//	{
//		if (mGameObjects[i]->GetName() == objName)
//		{
//			return mGameObjects[i];
//		}
//	}
//}
