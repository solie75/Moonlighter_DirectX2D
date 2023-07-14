#include "CPlayScene.h"
#include "CMeshRender.h"
#include "CResourceMgr.h"

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
