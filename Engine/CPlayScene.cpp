#include "CPlayScene.h"
#include "CMeshRender.h"
#include "CResourceMgr.h"
#include "CCameraMoveScript.h"
#include "CPlayerMoveScript.h"
#include "CGridScript.h"
#include "CAnimator.h"
#include "CCollisionMgr.h"
#include "CPlayer.h"
#include "CMonster.h"
#include "CDesertBossScript.h"
#include "CDesertBossCircleScript.h"
#include "CDesertBossRhombusScript.h"

CPlayScene::CPlayScene()
{
}

CPlayScene::~CPlayScene()
{
}

void CPlayScene::Initialize()
{
	CCollisionMgr::GetInst()->SetCollideLayer(eLayerType::Player, eLayerType::Monster, true);
	CCollisionMgr::GetInst()->SetCollideLayer(eLayerType::Background, eLayerType::Projectile, true);
	CCollisionMgr::GetInst()->SetCollideLayer(eLayerType::Player, eLayerType::Projectile, true);
	CCollisionMgr::GetInst()->SetCollideLayer(eLayerType::Player, eLayerType::Background, true);

	CGameObject* DesertBossBackground = new CGameObject();
	AddGameObject(eLayerType::Background, DesertBossBackground, L"DesertBossBackground",
		Vector3(0.f, 0.0f, 10.0009f), Vector3(25.f, 24.5f, 0.0f),true, L"Mesh", L"mt_DesertBossBackground", false);
	
	CGameObject* BackgroundUp = new CGameObject();
	AddGameObject(eLayerType::Background, BackgroundUp, L"BackgroundUp", Vector3(0.0f, 3.64f, 10.0008f),
		Vector3(1.0f, 1.0f, 0.0f),  false, L"Mesh", L"", false);
	CCollider2D* cd = BackgroundUp->AddComponent<CCollider2D>();
	cd->SetSize(Vector2(13.5f, 0.3f));

	CGameObject* BackgroundDown = new CGameObject();
	AddGameObject(eLayerType::Background, BackgroundDown, L"BackgroundDown", Vector3(0.0f, -4.3f, 10.0007f),
		Vector3(1.0f, 1.0f, 0.0f), false, L"Mesh", L"", false);
	cd = BackgroundDown->AddComponent<CCollider2D>();
	cd->SetSize(Vector2(13.5f, 0.3f));

	CGameObject* BackgroundLeft = new CGameObject();
	AddGameObject(eLayerType::Background, BackgroundLeft, L"BackgroundLeft", Vector3(-6.625f, 0.0f, 10.0006f),
		Vector3(1.0f, 1.0f, 0.0f), false, L"Mesh", L"", false);
	cd = BackgroundLeft->AddComponent<CCollider2D>();
	cd->SetSize(Vector2(0.3f, 10.f));

	CGameObject* BackgroundRight = new CGameObject();
	AddGameObject(eLayerType::Background, BackgroundRight, L"BackgroundRight", Vector3(6.63f, 0.0f, 10.0005f),
		Vector3(1.0f, 1.0f, 0.0f), false, L"Mesh", L"", false);
	cd = BackgroundRight->AddComponent<CCollider2D>();
	cd->SetSize(Vector2(0.3f, 10.f));


	// Main Camera
	CGameObject* mainCamera = new CGameObject();
	AddGameObject(eLayerType::Camera, mainCamera, L"MainCamera", Vector3(0.0f, 0.0f, -10.0f),
		Vector3(1.0f, 1.0f, 1.0f), false, L"", L"",false);
	CCamera* mainCamComp = mainCamera->AddComponent<CCamera>();
	mainCamComp->SetCameraType(eCameraType::Main);
	mainCamComp->TurnLayerMask(eLayerType::UI, false);
	//mainCamComp->TurnLayerMask(eLayerType::Grid, false);
	mainCamera->AddComponent<CCameraMoveScript>();

	// UI Camera
	CGameObject* uiCamera = new CGameObject();
	AddGameObject(eLayerType::Camera, uiCamera, L"UICamera", Vector3(0.0f, 0.0f, -10.0f),
		Vector3(1.0f, 1.0f, 1.0f), false, L"", L"", false);
	CCamera* uiCamComp = uiCamera->AddComponent<CCamera>();
	uiCamComp->SetCameraType(eCameraType::UI);
	uiCamComp->TurnLayerMask(eLayerType::Player, false);
	uiCamComp->TurnLayerMask(eLayerType::Monster, false);
	uiCamComp->TurnLayerMask(eLayerType::Background, false);
	uiCamComp->TurnLayerMask(eLayerType::Projectile, false);

	// player
	CPlayer* Will = new CPlayer();
	AddGameObject(eLayerType::Player, Will, L"Will", Vector3(3.0f, 0.0f, 1.0002f)
		, Vector3(0.25f, 0.47f, 0.0f), true, L"Mesh", L"mt_atlas_Will_Idle_Down", true);

	// Boss Monster
	CMonster* DesertBossHead = new CMonster();
	AddGameObject(eLayerType::Monster, DesertBossHead, L"Boss3_Head", Vector3(0.0f, 0.0f, 1.0004f)
		, Vector3(1.0f, 1.0f, 0.0f), true, L"Mesh", L"mt_Boss3_Head_Down", false);
	CDesertBossScript* DesertBossScript = DesertBossHead->AddComponent<CDesertBossScript>();
	cd = DesertBossHead->AddComponent<CCollider2D>();

	CMonster* DesertBossCircle = new CMonster();
	AddGameObject(eLayerType::Monster, DesertBossCircle, L"DesertBossCircle", Vector3(-0.7f, 0.0f, 1.0005f)
		, Vector3(1.6f, 1.6f, 0.0f), true, L"Mesh", L"mt_DesertBossCircle", false);
	DesertBossCircle->SetParentObject(DesertBossHead);
	CDesertBossCircleScript* DesertBossCircleScript = DesertBossCircle->AddComponent<CDesertBossCircleScript>();
	DesertBossCircleScript->SetScene(this);
	cd = DesertBossCircle->AddComponent<CCollider2D>();
	cd->SetSize(Vector2(0.5f, 0.5f));

	CMonster* DesertBossRhombus = new CMonster();
	AddGameObject(eLayerType::Monster, DesertBossRhombus, L"DesertBossRhombus", Vector3(-1.4f, 0.0f, 1.0006f)
		, Vector3(1.6f, 1.6f, 0.0f), true, L"Mesh", L"mt_DesertBossRhombus", false);
	DesertBossRhombus->SetParentObject(DesertBossCircle);
	CDesertBossRhombusScript* DesertBossRhombusScript = DesertBossRhombus -> AddComponent<CDesertBossRhombusScript>();
	DesertBossRhombusScript->SetScene(this);
	cd = DesertBossRhombus->AddComponent<CCollider2D>();
	cd->SetSize(Vector2(0.5f, 0.5f));

	CMonster* DesertBossSquare = new CMonster();
	AddGameObject(eLayerType::Monster, DesertBossSquare, L"DesertBossSquare", Vector3(-2.1f, 0.0f, 1.0007f)
		, Vector3(1.6f, 1.6f, 0.0f), true, L"Mesh", L"mt_DesertBossSquare", false);
	DesertBossSquare->SetParentObject(DesertBossRhombus);
	cd = DesertBossSquare->AddComponent<CCollider2D>();
	cd->SetSize(Vector2(0.5f, 0.5f));

	CMonster* DesertBossTriangle = new CMonster();
	AddGameObject(eLayerType::Monster, DesertBossTriangle, L"DesertBossTriangle", Vector3(-2.8f, 0.0f, 1.0008f)
		, Vector3(1.6f, 1.6f, 0.0f), true, L"Mesh", L"mt_DesertBossTriangle", false);
	DesertBossTriangle->SetParentObject(DesertBossSquare);
	cd = DesertBossTriangle->AddComponent<CCollider2D>();
	cd->SetSize(Vector2(0.5f, 0.5f));
	
	{ // light
		CGameObject* light = new CGameObject();
		light->SetName(L"light");
		AddGameObject(eLayerType::Light, light, L"light", Vector3(0.0f, 0.0f,  0.0f), Vector3(0.0f, 0.0f, 0.0f), false, L"", L"", false);
		CLight* lightComp = light->AddComponent<CLight>();
		lightComp->SetType(eLightType::Directional);
		lightComp->SetColor(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
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
