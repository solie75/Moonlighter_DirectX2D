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
#include "CDesertBossSquareScript.h"
#include "CDesertBossTriangleSCript.h"

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
	CCollisionMgr::GetInst()->SetCollideLayer(eLayerType::Monster, eLayerType::Background, true);

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

	// player
	CPlayer* Will = new CPlayer();
	AddGameObject(eLayerType::Player, Will, L"Will", Vector3(3.0f, 0.0f, 1.0002f)
		, Vector3(0.25f, 0.47f, 0.0f), true, L"Mesh", L"mt_atlas_Will_Idle_Down", true);
	CTransform* PlayerTr = Will->GetComponent<CTransform>(eComponentType::Transform);


	// Main Camera
	CGameObject* mainCamera = new CGameObject();
	AddGameObject(eLayerType::Camera, mainCamera, L"MainCamera", Vector3(0.0f, 0.0f, -10.0f),
		Vector3(1.0f, 1.0f, 1.0f), false, L"", L"",false);
	CCamera* mainCamComp = mainCamera->AddComponent<CCamera>();
	mainCamComp->SetCameraType(eCameraType::Main);
	mainCamComp->TurnLayerMask(eLayerType::UI, false);
	CCameraMoveScript* CameraMoveScript = mainCamera->AddComponent<CCameraMoveScript>();
	CameraMoveScript->SetPlayerTr(PlayerTr);

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



	// Boss Monster
	CMonster* Boss3_Born = new CMonster();
	AddGameObject(eLayerType::Monster, Boss3_Born, L"Boss3_Born", Vector3(-0.1f, 1.5f, 1.0003f)
		, Vector3(6.f, 6.f, 0.0f), true, L"Mesh", L"mt_atlas_Boss3_Born_1", true);
	BossBornAt = Boss3_Born->GetComponent<CAnimator>(eComponentType::Animator);
	BossBornAt->PlayAnimation(L"Boss3_Born_1", false);
	
	CMonster* DesertBossHead = new CMonster();
	AddGameObject(eLayerType::Monster, DesertBossHead, L"Boss3_Head", Vector3(0.3f, -0.6f, 1.0004f)
		, Vector3(2.5f, 2.5f, 0.0f), true, L"Mesh", L"mt_atlas_Boss3_Head_Down", true);
	CDesertBossScript* DesertBossScript = DesertBossHead->AddComponent<CDesertBossScript>();
	cd = DesertBossHead->AddComponent<CCollider2D>();
	cd->SetSize(Vector2(0.1f, 0.1f));
	DesertBossHead->SetParentObject(Boss3_Born);

	CMonster* DesertBossCircle = new CMonster();
	AddGameObject(eLayerType::Monster, DesertBossCircle, L"DesertBossCircle", Vector3(0.4f, 0.2f, 1.0005f)
		, Vector3(1.6f, 1.6f, 0.0f), true, L"Mesh", L"mt_DesertBossCircle", true);
	DesertBossCircle->SetParentObject(DesertBossHead);
	CDesertBossCircleScript* DesertBossCircleScript = DesertBossCircle->AddComponent<CDesertBossCircleScript>();
	DesertBossCircleScript->SetScene(this);
	cd = DesertBossCircle->AddComponent<CCollider2D>();
	cd->SetSize(Vector2(0.5f, 0.5f));

	CMonster* DesertBossRhombus = new CMonster();
	AddGameObject(eLayerType::Monster, DesertBossRhombus, L"DesertBossRhombus", Vector3(0.0f, 0.25f, 1.0006f)
		, Vector3(1.6f, 1.6f, 0.0f), true, L"Mesh", L"mt_DesertBossRhombus", true);
	DesertBossRhombus->SetParentObject(DesertBossCircle);
	CDesertBossRhombusScript* DesertBossRhombusScript = DesertBossRhombus -> AddComponent<CDesertBossRhombusScript>();
	DesertBossRhombusScript->SetScene(this);
	cd = DesertBossRhombus->AddComponent<CCollider2D>();
	cd->SetSize(Vector2(0.5f, 0.5f));

	CMonster* DesertBossSquare = new CMonster();
	AddGameObject(eLayerType::Monster, DesertBossSquare, L"DesertBossSquare", Vector3(-0.5f, 0.0f, 1.0007f)
		, Vector3(1.6f, 1.6f, 0.0f), true, L"Mesh", L"mt_DesertBossSquare", true);
	DesertBossSquare->SetParentObject(DesertBossRhombus);
	CDesertBossSquareScript* DesertBossSquareScript = DesertBossSquare->AddComponent<CDesertBossSquareScript>();
	cd = DesertBossSquare->AddComponent<CCollider2D>();
	cd->SetSize(Vector2(0.5f, 0.5f));

	CMonster* DesertBossTriangle = new CMonster();
	AddGameObject(eLayerType::Monster, DesertBossTriangle, L"DesertBossTriangle", Vector3(-0.8f, -0.6f, 1.0008f)
		, Vector3(1.6f, 1.6f, 0.0f), true, L"Mesh", L"mt_DesertBossTriangle", true);
	DesertBossTriangle->SetParentObject(DesertBossSquare);
	CDesertBossTriangleScript* DesertBossTriangleScript = DesertBossTriangle->AddComponent<CDesertBossTriangleScript>();
	DesertBossTriangleScript->SetScene(this);
	DesertBossTriangleScript->SetOtherPos(Will->GetComponent<CTransform>(eComponentType::Transform));
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
	if (BossBornAt->GetOwner()->GetState() == CGameObject::eObjectState::Paused)
	{
		BossBornAt->GetOwner()->SetState(CGameObject::eObjectState::Dead);
		//delete BossBornAt;
	}
	if (BossBornAt->GetCurAnimation()->GetKey() == L"Boss3_Born_1" && BossBornAt->GetCurAnimation()->IsComplete())
	{
		BossBornAt->PlayAnimation(L"Boss3_Born_2", false);
	}
	if (BossBornAt->GetCurAnimation()->GetKey() == L"Boss3_Born_2" && BossBornAt->GetCurAnimation()->IsComplete())
	{
		BossBornAt->GetOwner()->SetState(CGameObject::eObjectState::Paused);
	}
	
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
