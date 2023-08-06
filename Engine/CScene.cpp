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
{
//	for (int i = 0; i < mLayers.size(); i++)
//	{
//		mLayers[i].Render();
//	}
}

//void CScene::AddGameObject(eLayerType type, CGameObject* gameObj, const std::wstring& objName
//	, Vector3 position, Vector3 scale, bool meshRenderBool, const std::wstring& meshName, const std::wstring& materialName)
//{
//	gameObj->SetName(objName);
//	mLayers[(int)type].AddGameObject(gameObj);
//	gameObj->GetComponent<CTransform>(eComponentType::Transform)->SetPosition(position);
//	gameObj->GetComponent<CTransform>(eComponentType::Transform)->SetScale(scale);
//	if (meshRenderBool == true)
//	{
//		CMeshRender* mr = gameObj->AddComponent<CMeshRender>();
//		mr->SetMesh(CResourceMgr::Find<CMesh>(meshName));
//		mr->SetMaterial(CResourceMgr::Find<CMaterial>(materialName));
//		int a = 0;
//	}
//	
//}

void CScene::AddGameObject(eLayerType type, CGameObject* gameObj, const std::wstring& objName
	, Vector3 position, Vector3 scale, bool meshRenderBool, const std::wstring& meshName, const std::wstring& materialName, bool animationBool)
{
	gameObj->SetName(objName);
	mLayers[(int)type].AddGameObject(gameObj);
	gameObj->GetComponent<CTransform>(eComponentType::Transform)->SetPosition(position);
	gameObj->GetComponent<CTransform>(eComponentType::Transform)->SetScale(scale);
	if (meshRenderBool == true)
	{
		CMeshRender* mr = gameObj->AddComponent<CMeshRender>();
		mr->SetMesh(CResourceMgr::Find<CMesh>(meshName));
		mr->SetMaterial(CResourceMgr::Find<CMaterial>(materialName));
		// Animation 의 경우 PlayAnimation 으로 애니메이션이 실행될 때마다 그에 맞는 material 을 설정한다.
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
