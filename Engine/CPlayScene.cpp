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
	
	// Atlas Test Object

	CGameObject* Will_Idle_Down = new CGameObject();
	AddGameObject(eLayerType::Player, Will_Idle_Down, L"atlas_Will_Idle_Down", Vector3(3.0f, 0.0f, 1.0002f)
		, Vector3(0.25f, 0.47f, 0.0f), true, L"Mesh", L"mt_atlas_Will_Idle_Down");

	std::shared_ptr<CTexture> atlas_Will_Idle_Down = CResourceMgr::GetInst()->Load<CTexture>(L"atlas_Will_Idle_Down", L"");

	CAnimator* at_Will_Idle_Down = Will_Idle_Down->AddComponent<CAnimator>();
	at_Will_Idle_Down->Create(L"Will_Idle_Down", atlas_Will_Idle_Down, Vector2(0.0f, 0.0f), Vector2(24.f, 41.f), 10);
	at_Will_Idle_Down->PlayAnimation(L"Will_Idle_Down", true);

	// 2
	CGameObject* Will_Idle_Left = new CGameObject();
	AddGameObject(eLayerType::Player, Will_Idle_Left, L"atlas_Will_Idle_Left", Vector3(3.0f, 2.0f, 1.0003f)
		, Vector3(0.25f, 0.47f, 0.0f), true, L"Mesh", L"mt_atlas_Will_Idle_Left");

	std::shared_ptr<CTexture> atlas_Will_Idle_Left = CResourceMgr::GetInst()->Load<CTexture>(L"atlas_Will_Idle_Left", L"");

	CAnimator* at_Will_Idle_Left = Will_Idle_Left->AddComponent<CAnimator>();
	at_Will_Idle_Left->Create(L"Will_Idle_Left", atlas_Will_Idle_Left, Vector2(0.0f, 0.0f), Vector2(32.f, 42.f), 10);
	at_Will_Idle_Left->PlayAnimation(L"Will_Idle_Left", true);


	
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
