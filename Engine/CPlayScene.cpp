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
	// Link
	CGameObject* player = new CGameObject();
	AddGameObject(eLayerType::Player, player, L"Link");
	CMeshRender* mr = player->AddComponent<CMeshRender>();
	mr->SetMesh(CResourceMgr::Find<CMesh>(L"Mesh"));
	mr->SetMaterial(CResourceMgr::Find<CMaterial>(L"mt_Link"));
	player->AddComponent<CPlayerMoveScript>();

	// Smile
	CGameObject* smile = new CGameObject();
	AddGameObject(eLayerType::UI, smile, L"Smile");
	CMeshRender* mr_smile = smile->AddComponent<CMeshRender>();
	mr_smile->SetMesh(CResourceMgr::Find<CMesh>(L"Mesh"));
	mr_smile->SetMaterial(CResourceMgr::Find<CMaterial>(L"mt_Smile"));
	smile->GetComponent<CTransform>(eComponentType::Transform)->SetPosition(Vector3(0.2f, 0.0f, 0.0f));

	// Main Camera
	CGameObject* mainCamera = new CGameObject();
	AddGameObject(eLayerType::Player, mainCamera, L"MainCamera");
	mainCamera->GetComponent<CTransform>(eComponentType::Transform)->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
	CCamera* mainCamComp = mainCamera->AddComponent<CCamera>();
	mainCamComp->TurnLayerMask(eLayerType::UI, false);
	mainCamera->AddComponent<CCameraMoveScript>();

	// UI Camera
	CGameObject* uiCamera = new CGameObject();
	AddGameObject(eLayerType::Player, uiCamera, L"UICamera");
	uiCamera->GetComponent<CTransform>(eComponentType::Transform)->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
	CCamera* uiCamComp = uiCamera->AddComponent<CCamera>();
	uiCamComp->TurnLayerMask(eLayerType::Player, false);
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
	//CScene::Render();
}
