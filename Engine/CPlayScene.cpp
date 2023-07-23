#include "CPlayScene.h"
#include "CMeshRender.h"
#include "CResourceMgr.h"
#include "CCameraMoveScript.h"
#include "CPlayerMoveScript.h"
#include "CGridScript.h"
#include "CAnimator.h"

CPlayScene::CPlayScene()
{
}

CPlayScene::~CPlayScene()
{
}

void CPlayScene::Initialize()
{
	// Link
	CGameObject* player1 = new CGameObject();
	AddGameObject(eLayerType::Player, player1, L"Link", Vector3(0.0f, 0.0f, 1.01f),
		Vector3(1.0f, 1.0f, 1.0f), true, L"Mesh", L"mt_Link");
	/*player1->AddComponent<CPlayerMoveScript>();*/

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
	//mainCamComp->TurnLayerMask(eLayerType::Grid, false);
	mainCamera->AddComponent<CCameraMoveScript>();

	// UI Camera
	CGameObject* uiCamera = new CGameObject();
	AddGameObject(eLayerType::Player, uiCamera, L"UICamera", Vector3(0.0f, 0.0f, -10.0f),
		Vector3(1.0f, 1.0f, 1.0f), false, L"", L"");
	CCamera* uiCamComp = uiCamera->AddComponent<CCamera>();
	uiCamComp->TurnLayerMask(eLayerType::Player, false);

	// Grid
	CGameObject* grid = new CGameObject();
	AddGameObject(eLayerType::Grid, grid, L"Grid", Vector3(0.0f, 0.0f, 0.0f),
		Vector3(1.0f, 1.0, 1.0f), true, L"Mesh", L"mt_Grid");
	CGridScript* gridScript = grid->AddComponent<CGridScript>();

	// Link Animation
	CGameObject* player = new CGameObject();
	AddGameObject(eLayerType::Player, player, L"linkSprites", Vector3(-2.0f, 0.0f, 1.0001f)
		, Vector3(1.0f, 1.0f, 1.0f), true, L"Mesh", L"mt_linkSprites");
	
	std::shared_ptr<CTexture> atlas
		= CResourceMgr::GetInst()->Load<CTexture>(L"linkSprites", L"..\\Resources\\Texture\\linkSprites.png");

	CAnimator* at = player->AddComponent<CAnimator>();
	at->Create(L"LinkIdle", atlas, Vector2(0.0f, 0.0f), Vector2(120.f, 130.f), 3);
	at->PlayAnimation(L"LinkIdle", true);
	player->AddComponent<CPlayerMoveScript>();
	
	
	
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
