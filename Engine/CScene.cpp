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
		mr->SetMesh(CResourceMgr::Find<CMesh>(meshName));
		mr->SetMaterial(CResourceMgr::Find<CMaterial>(materialName));

		/*CMeshRender* mr = gameObj->AddComponent<CMeshRender>();
		mr->SetMesh(CResourceMgr::Find<CMesh>(meshName));
		if (materialName == L"")
		{
			std::shared_ptr<CMaterial> mt = std::make_shared<CMaterial>();
			std::shared_ptr<CShader> shader = CResourceMgr::Find<CShader>(L"Shader");
			mt->SetShader(shader);
			mt->SetTexture(nullptr);
			mt->SetRenderMode(eRenderingMode::CutOut);
			mr->SetMaterial(mt);
		}
		else
		{
			mr->SetMaterial(CResourceMgr::Find<CMaterial>(materialName));
		}*/
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
