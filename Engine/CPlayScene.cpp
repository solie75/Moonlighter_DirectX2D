#include "CPlayScene.h"
#include "CMeshRender.h"
#include "CResourceMgr.h"
#include "CCameraMoveScript.h"
#include "CPlayerMoveScript.h"

CPlayScene::CPlayScene()
{
}

CPlayScene::~CPlayScene()
{
}

void CPlayScene::Initialize()
{
	CGameObject* player = new CGameObject();
	AddGameObject(eLayerType::Player, player, L"Link");
	CMeshRender* mr = player->AddComponent<CMeshRender>();
	mr->SetMesh(CResourceMgr::Find<CMesh>(L"Mesh"));
	mr->SetMaterial(CResourceMgr::Find<CMaterial>(L"Material"));
	player->AddComponent<CPlayerMoveScript>();

	CGameObject* mainCamera = new CGameObject();
	AddGameObject(eLayerType::Player, mainCamera, L"MainCamera");
	mainCamera->GetComponent<CTransform>(eComponentType::Transform)->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
	CCamera* camComponent = mainCamera->AddComponent<CCamera>();
	mainCamera->AddComponent<CCameraMoveScript>();

}

void CPlayScene::Update()
{
	CScene::Update();
}

void CPlayScene::LateUpdate()
{
	CScene::LateUpdate();
}

void CPlayScene::Render()
{
	CScene::Render();
}
