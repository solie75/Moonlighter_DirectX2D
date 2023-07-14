#include "CScene.h"

CScene::CScene()
{
	mLayers.resize((int)eLayerType::End);
}

CScene::~CScene()
{
}

void CScene::Initialize()
{
}

void CScene::Update()
{
	for (int i = 0; i < mLayers.size(); i++)
	{
		mLayers[i].Update();
	}
}

void CScene::LateUpdate()
{
	for (CLayer& layer : mLayers)
	{
		layer.LateUpdate();
	}
}

void CScene::Render()
{
	for (int i = 0; i < mLayers.size(); i++)
	{
		mLayers[i].Render();
	}
}

void CScene::AddGameObject(eLayerType type, CGameObject* gameObj, const std::wstring& name)
{
	gameObj->SetName(name);
	mLayers[(int)type].AddGameObject(gameObj);
}
