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
	for (int i = 0; i < mLayers.size(); i++)
	{
		mLayers[i].Initialize();
	}
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
{}

void CScene::AddGameObject(eLayerType type, CGameObject* gameObj, const std::wstring& objName
	, Vector3 position, Vector3 scale, bool meshRenderBool, const std::wstring& meshName, const std::wstring& materialName, bool animationBool)
{
	gameObj->SetName(objName);
	mLayers[(int)type].AddGameObject(gameObj);
	gameObj->SetLayerType(type);
	gameObj->GetComponent<CTransform>(eComponentType::Transform)->SetPosition(position);
	gameObj->GetComponent<CTransform>(eComponentType::Transform)->SetScale(scale);
	if (meshRenderBool == true)
	{
		CMeshRender* mr = gameObj->AddComponent<CMeshRender>();
		mr->SetName(L"mr_" + objName);
		mr->SetMesh(CResourceMgr::Find<CMesh>(meshName));
		if (materialName == L"")
		{
			std::shared_ptr<CMaterial> mt = std::make_shared<CMaterial>();
			mt->SetShader(CResourceMgr::Find<CShader>(L"shader"));
			mr->SetMaterial(mt);
		}
		else
		{
			mr->SetMaterial(CResourceMgr::Find<CMaterial>(materialName));
		}
	}
	if (animationBool == true)
	{
		CAnimator* at = gameObj->AddComponent<CAnimator>();
		CResourceMgr::GetInst()->CreateAnimationTest(objName, at);
	}
	
}

void CScene::Destroy()
{
	for (CLayer& layer : mLayers)
	{
		layer.Destroy();
	}
}
