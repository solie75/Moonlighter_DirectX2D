#include "CPlayScene.h"
#include "CMeshRender.h"
#include "CResourceMgr.h"
#include "CCameraMoveScript.h"
#include "CPlayerMoveScript.h"
#include "CGridScript.h"

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
	AddGameObject(eLayerType::Player, player, L"Link", Vector3(0.0f, 0.0f, 1.01f),
		Vector3(1.0f, 1.0f, 1.0f), true, L"Mesh", L"mt_Link");
	player->AddComponent<CPlayerMoveScript>();

	// Smile
	CGameObject* smile = new CGameObject();
	AddGameObject(eLayerType::UI, smile, L"Smile", Vector3(0.2f, 0.0f, 1.0f),
		Vector3(1.0f, 1.0f, 1.0f), true, L"Mesh", L"mt_Smile");

	// Main Camera
	CGameObject* mainCamera = new CGameObject();
	AddGameObject(eLayerType::Player, mainCamera, L"MainCamera", Vector3(0.0f, 0.0f, -10.0f),
		Vector3(1.0f, 1.0f, 1.0f), false, L"", L"");
	CCamera* mainCamComp = mainCamera->AddComponent<CCamera>();
	mainCamComp->TurnLayerMask(eLayerType::UI, false);
	mainCamComp->TurnLayerMask(eLayerType::Grid, false);
	mainCamera->AddComponent<CCameraMoveScript>();

	// UI Camera
	CGameObject* uiCamera = new CGameObject();
	AddGameObject(eLayerType::Player, uiCamera, L"UICamera", Vector3(0.0f, 0.0f, -10.0f),
		Vector3(1.0f, 1.0f, 1.0f), false, L"", L"");
	CCamera* uiCamComp = uiCamera->AddComponent<CCamera>();
	uiCamComp->TurnLayerMask(eLayerType::Player, false);
	uiCamComp->TurnLayerMask(eLayerType::Grid, false);

	// Grid Camera
	CGameObject* grid = new CGameObject();
	AddGameObject(eLayerType::Grid, grid, L"Grid", Vector3(0.0f, 0.0f, 0.0f),
		Vector3(1.0f, 1.0, 1.0f), true, L"RectMesh", L"mt_Grid");
	CGridScript* gridScript = grid->AddComponent<CGridScript>();

	CScene::Initialize();
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
