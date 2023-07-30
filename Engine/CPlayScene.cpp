#include "CPlayScene.h"
#include "CMeshRender.h"
#include "CResourceMgr.h"
#include "CCameraMoveScript.h"
#include "CPlayerMoveScript.h"
#include "CGridScript.h"
#include "CAnimator.h"
#include "CCollisionMgr.h"
#include "CCreatureObject.h"

CPlayScene::CPlayScene()
{
}

CPlayScene::~CPlayScene()
{
}

void CPlayScene::Initialize()
{
	CCollisionMgr::GetInst()->SetCollideLayer(eLayerType::Player, eLayerType::Monster, true);

	// Link
	CGameObject* player1 = new CGameObject();
	AddGameObject(eLayerType::Monster, player1, L"Link", Vector3(0.0f, 0.0f, 1.01f),
		Vector3(1.0f, 1.0f, 1.0f), true, L"Mesh", L"mt_Link");
	CCollider2D* cd = player1->AddComponent<CCollider2D>();

	// Smile
	CGameObject* smile = new CGameObject();
	AddGameObject(eLayerType::UI, smile, L"Smile", Vector3(0.2f, 0.0f, 1.0f),
		Vector3(1.0f, 1.0f, 1.0f), true, L"Mesh", L"mt_Smile");


	// Main Camera
	CGameObject* mainCamera = new CGameObject();
	AddGameObject(eLayerType::Camera, mainCamera, L"MainCamera", Vector3(0.0f, 0.0f, -10.0f),
		Vector3(1.0f, 1.0f, 1.0f), false, L"", L"");
	CCamera* mainCamComp = mainCamera->AddComponent<CCamera>();
	mainCamComp->SetCameraType(eCameraType::Main);
	mainCamComp->TurnLayerMask(eLayerType::UI, false);
	//mainCamComp->TurnLayerMask(eLayerType::Grid, false);
	mainCamera->AddComponent<CCameraMoveScript>();

	// UI Camera
	CGameObject* uiCamera = new CGameObject();
	AddGameObject(eLayerType::Camera, uiCamera, L"UICamera", Vector3(0.0f, 0.0f, -10.0f),
		Vector3(1.0f, 1.0f, 1.0f), false, L"", L"");
	CCamera* uiCamComp = uiCamera->AddComponent<CCamera>();
	uiCamComp->SetCameraType(eCameraType::UI);
	uiCamComp->TurnLayerMask(eLayerType::Player, false);
	uiCamComp->TurnLayerMask(eLayerType::Monster, false);

	// Grid
	/*CGameObject* grid = new CGameObject();
	AddGameObject(eLayerType::Grid, grid, L"Grid", Vector3(0.0f, 0.0f, 0.0f),
		Vector3(1.0f, 1.0, 1.0f), true, L"Mesh", L"mt_Grid");
	CGridScript* gridScript = grid->AddComponent<CGridScript>();*/

	// Link Animation
	CGameObject* player = new CGameObject();
	AddGameObject(eLayerType::Player, player, L"linkSprites", Vector3(-2.0f, 0.0f, 1.0001f)
		, Vector3(1.0f, 1.0f, 1.0f), true, L"Mesh", L"mt_linkSprites");

	std::shared_ptr<CTexture> atlas
		= CResourceMgr::GetInst()->Load<CTexture>(L"linkSprites", L"..\\Resources\\Texture\\linkSprites.png");

	CAnimator* at = player->AddComponent<CAnimator>();
	at->Create(L"LinkIdle", atlas, Vector2(0.0f, 0.0f), Vector2(120.f, 130.f), 3);
	at->PlayAnimation(L"LinkIdle", true);
	
	
	// Atlas Test Object

	/*CGameObject* Will = new CGameObject();
	AddGameObject(eLayerType::Player, Will, L"Will", Vector3(3.0f, 0.0f, 1.0002f)
		, Vector3(0.25f, 0.47f, 0.0f), true, L"Mesh", L"mt_atlas_Will_Idle_Down");
	CAnimator* Will_Animator = Will->AddComponent<CAnimator>();
	CMeshRender* mr = Will->GetComponent<CMeshRender>(eComponentType::MeshRender);
	CPlayerMoveScript* pmScript = Will->AddComponent<CPlayerMoveScript>();
	CCollider2D* col2D = Will->AddComponent<CCollider2D>();
	col2D->SetSize(Vector2(0.7f, 0.7f));*/

	CCreatureObject* Will = new CCreatureObject();
	AddGameObject(eLayerType::Player, Will, L"Will", Vector3(3.0f, 0.0f, 1.0002f)
		, Vector3(0.25f, 0.47f, 0.0f), true, L"Mesh", L"mt_atlas_Will_Idle_Down");
	Will->SetCreatureType(CCreatureObject::eCreatureType::Player);
	Will->SetAimSight(CCreatureObject::eAimSight::Down);
	Will->SetState(CCreatureObject::eState::Idle);

	CAnimator* Will_Animator = Will->AddComponent<CAnimator>();
	CMeshRender* mr = Will->GetComponent<CMeshRender>(eComponentType::MeshRender);
	CPlayerMoveScript* pmScript = Will->AddComponent<CPlayerMoveScript>();
	CCollider2D* col2D = Will->AddComponent<CCollider2D>();
	col2D->SetSize(Vector2(0.7f, 0.7f));
	{
		// Idle Atlas
		std::shared_ptr<CTexture> atlas_Will_Idle_Down = CResourceMgr::GetInst()->Load<CTexture>(L"atlas_Will_Idle_Down", L"");
		Will_Animator->Create(L"Will_Idle_Down", atlas_Will_Idle_Down, Vector2(0.0f, 0.0f), Vector2(24.f, 41.f), 10);

		std::shared_ptr<CTexture> atlas_Will_Idle_Left = CResourceMgr::GetInst()->Load<CTexture>(L"atlas_Will_Idle_Left", L"");
		Will_Animator->Create(L"Will_Idle_Left", atlas_Will_Idle_Left, Vector2(0.0f, 0.0f), Vector2(32.f, 42.f), 10);

		std::shared_ptr<CTexture> atlas_Will_Idle_Right = CResourceMgr::GetInst()->Load<CTexture>(L"atlas_Will_Idle_Right", L"");
		Will_Animator->Create(L"Will_Idle_Right", atlas_Will_Idle_Right, Vector2(0.0f, 0.0f), Vector2(32.f, 42.f), 10);

		std::shared_ptr<CTexture> atlas_Will_Idle_Up = CResourceMgr::GetInst()->Load<CTexture>(L"atlas_Will_Idle_Up", L"");
		Will_Animator->Create(L"Will_Idle_Up", atlas_Will_Idle_Up, Vector2(0.0f, 0.0f), Vector2(25.f, 42.f), 10);

		// Walk Atlas
		std::shared_ptr<CTexture> atlas_Will_Walk_Down = CResourceMgr::GetInst()->Load<CTexture>(L"atlas_Will_Walk_Down", L"");
		Will_Animator->Create(L"Will_Walk_Down", atlas_Will_Walk_Down, Vector2(0.0f, 0.0f), Vector2(24.f, 39.f), 8);

		std::shared_ptr<CTexture> atlas_Will_Walk_Left = CResourceMgr::GetInst()->Load<CTexture>(L"atlas_Will_Walk_Left", L"");
		Will_Animator->Create(L"Will_Walk_Left", atlas_Will_Walk_Left, Vector2(0.0f, 0.0f), Vector2(35.f, 40.f), 8);

		std::shared_ptr<CTexture> atlas_Will_Walk_Right = CResourceMgr::GetInst()->Load<CTexture>(L"atlas_Will_Walk_Right", L"");
		Will_Animator->Create(L"Will_Walk_Right", atlas_Will_Walk_Right, Vector2(0.0f, 0.0f), Vector2(35.f, 40.f), 8);

		std::shared_ptr<CTexture> atlas_Will_Walk_Up = CResourceMgr::GetInst()->Load<CTexture>(L"atlas_Will_Walk_Up", L"");
		Will_Animator->Create(L"Will_Walk_Up", atlas_Will_Walk_Up, Vector2(0.0f, 0.0f), Vector2(25.f, 43.f), 8);

		// Roll Atlas
		std::shared_ptr<CTexture> atlas_Will_Roll_Down = CResourceMgr::GetInst()->Load<CTexture>(L"atlas_Will_Roll_Down", L"");
		Will_Animator->Create(L"Will_Roll_Down", atlas_Will_Roll_Down, Vector2(0.0f, 0.0f), Vector2(29.f, 42.f), 8);

		std::shared_ptr<CTexture> atlas_Will_Roll_Left = CResourceMgr::GetInst()->Load<CTexture>(L"atlas_Will_Roll_Left", L"");
		Will_Animator->Create(L"Will_Roll_Left", atlas_Will_Roll_Left, Vector2(0.0f, 0.0f), Vector2(35.f, 40.f), 8);

		std::shared_ptr<CTexture> atlas_Will_Roll_Right = CResourceMgr::GetInst()->Load<CTexture>(L"atlas_Will_Roll_Right", L"");
		Will_Animator->Create(L"Will_Roll_Right", atlas_Will_Roll_Right, Vector2(0.0f, 0.0f), Vector2(35.f, 42.f), 8);

		std::shared_ptr<CTexture> atlas_Will_Roll_Up = CResourceMgr::GetInst()->Load<CTexture>(L"atlas_Will_Roll_Up", L"");
		Will_Animator->Create(L"Will_Roll_Up", atlas_Will_Roll_Up, Vector2(0.0f, 0.0f), Vector2(26.f, 41.f), 8);
	}
	
	Will_Animator->PlayAnimation(L"Will_Idle_Down", true); //맨 처음 화면에 나오는 애니메이션

	{ // light
		CGameObject* light = new CGameObject();
		light->SetName(L"light");
		AddGameObject(eLayerType::Light, light, L"light", Vector3(0.0f, 0.0f,  0.0f), Vector3(0.0f, 0.0f, 0.0f), false, L"", L"");
		CLight* lightComp = light->AddComponent<CLight>();
		lightComp->SetType(eLightType::Directional);
		lightComp->SetColor(Vector4(1.0f, 0.0f, 1.0f, 1.0f));
	}
	
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
