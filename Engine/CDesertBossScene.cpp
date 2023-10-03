#include "CDesertBossScene.h"
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
#include "CParticleSystem.h"
#include "CPaintShader.h"
#include "CHPScript.h"

CDesertBossScene::CDesertBossScene()
{
}

CDesertBossScene::~CDesertBossScene()
{
}

void CDesertBossScene::Initialize()
{
	CCollisionMgr::GetInst()->SetCollideLayer(eLayerType::Player, eLayerType::Monster, true);
	CCollisionMgr::GetInst()->SetCollideLayer(eLayerType::Background, eLayerType::Projectile, true);
	CCollisionMgr::GetInst()->SetCollideLayer(eLayerType::Player, eLayerType::Projectile, true);
	CCollisionMgr::GetInst()->SetCollideLayer(eLayerType::Player, eLayerType::Background, true);
	CCollisionMgr::GetInst()->SetCollideLayer(eLayerType::Monster, eLayerType::Background, true);
	CCollisionMgr::GetInst()->SetCollideLayer(eLayerType::Monster, eLayerType::Monster, true);

	CGameObject* DesertBossBackground = new CGameObject();
	AddGameObject(eLayerType::Background, DesertBossBackground, L"DesertBossBackground",
		Vector3(0.f, 0.0f, 10.0009f), Vector3(25.f, 24.5f, 0.0f),true, L"Mesh", L"mt_DesertBossBackground", false);
	
	CGameObject* BackgroundUp = new CGameObject();
	AddGameObject(eLayerType::Background, BackgroundUp, L"BackgroundUp", Vector3(0.0f, 3.64f, 10.0008f),
		Vector3(1.0f, 1.0f, 0.0f),  false, L"Mesh", L"", false);
	CColliderMgr* CdList = BackgroundUp->AddComponent<CColliderMgr>(eComponentType::ColliderList);
	CCollider2D* CDforBackgroundUp = new CCollider2D;
	CDforBackgroundUp->SetSize(Vector2(13.5f, 0.3f));
	CdList->AddCollider(CDforBackgroundUp);
	

	CGameObject* BackgroundDown = new CGameObject();
	AddGameObject(eLayerType::Background, BackgroundDown, L"BackgroundDown", Vector3(0.0f, -4.3f, 10.0007f),
		Vector3(1.0f, 1.0f, 0.0f), false, L"Mesh", L"", false);
	CdList = BackgroundDown->AddComponent<CColliderMgr>(eComponentType::ColliderList);
	CCollider2D* CDforBackgroundDown = new CCollider2D;
	CDforBackgroundDown->SetSize(Vector2(13.5f, 0.3f));
	CdList->AddCollider(CDforBackgroundDown);

	CGameObject* BackgroundLeft = new CGameObject();
	AddGameObject(eLayerType::Background, BackgroundLeft, L"BackgroundLeft", Vector3(-6.625f, 0.0f, 10.0006f),
		Vector3(1.0f, 1.0f, 0.0f), false, L"Mesh", L"", false);
	CdList = BackgroundLeft->AddComponent<CColliderMgr>(eComponentType::ColliderList);
	CCollider2D* CDforBackgroundLeft = new CCollider2D;
	CDforBackgroundLeft->SetSize(Vector2(0.3f, 10.f));
	CdList->AddCollider(CDforBackgroundLeft);


	CGameObject* BackgroundRight = new CGameObject();
	AddGameObject(eLayerType::Background, BackgroundRight, L"BackgroundRight", Vector3(6.63f, 0.0f, 10.0005f),
		Vector3(1.0f, 1.0f, 0.0f), false, L"Mesh", L"", false);
	CdList = BackgroundRight->AddComponent<CColliderMgr>(eComponentType::ColliderList);
	CCollider2D* CDforBackgroundRight = new CCollider2D;
	CDforBackgroundRight->SetSize(Vector2(0.3f, 10.f));
	CdList->AddCollider(CDforBackgroundRight);

	// player
	CPlayer* Will = new CPlayer();
	AddGameObject(eLayerType::Player, Will, L"Will", Vector3(3.0f, 0.0f, 1.0002f)
		, Vector3(0.25f, 0.47f, 0.0f), true, L"Mesh", L"mt_atlas_Will_Idle_Down", true);
	CTransform* PlayerTr = Will->GetComponent<CTransform>(eComponentType::Transform);


	// Main Camera
	CGameObject* mainCamera = new CGameObject();
	AddGameObject(eLayerType::Camera, mainCamera, L"MainCamera", Vector3(0.0f, 0.0f, -10.0f),
		Vector3(1.0f, 1.0f, 1.0f), false, L"", L"",false);
	CCamera* mainCamComp = mainCamera->AddComponent<CCamera>(eComponentType::Camera);
	mainCamComp->SetCameraType(eCameraType::Main);
	mainCamComp->TurnLayerMask(eLayerType::UI, false);
	CCameraMoveScript* CameraMoveScript = mainCamera->GetComponent<CCameraMoveScript>(eComponentType::Script);
	CameraMoveScript->SetPlayerTr(PlayerTr);

	// UI Camera
	CGameObject* uiCamera = new CGameObject();
	AddGameObject(eLayerType::Camera, uiCamera, L"UICamera", Vector3(0.0f, 0.0f, -10.0f),
		Vector3(1.0f, 1.0f, 1.0f), false, L"", L"", false);
	CCamera* uiCamComp = uiCamera->AddComponent<CCamera>(eComponentType::Camera);
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
	DesertBossHead->SetHP(1000);
	CDesertBossScript* DesertBossScript = DesertBossHead->AddComponent<CDesertBossScript>(eComponentType::Script);

	CColliderMgr* BossHeadCdList = DesertBossHead->AddComponent<CColliderMgr>(eComponentType::ColliderList);
	CCollider2D* BossHeadCDforBackground = new CCollider2D;
	BossHeadCDforBackground->SetSize(Vector2(0.1f, 0.1f));
	BossHeadCdList->AddCollider(BossHeadCDforBackground);
	CCollider2D* BossHeadCDforHit = new CCollider2D;
	BossHeadCDforHit->SetSize(Vector2(0.5f, 0.5f));
	BossHeadCdList->AddCollider(BossHeadCDforHit);
	DesertBossHead->SetParentObject(Boss3_Born);

	CMonster* DesertBossCircle = new CMonster();
	AddGameObject(eLayerType::Monster, DesertBossCircle, L"DesertBossCircle", Vector3(0.4f, 0.2f, 1.0005f)
		, Vector3(1.6f, 1.6f, 0.0f), true, L"Mesh", L"mt_DesertBossCircle", true);
	DesertBossCircle->SetParentObject(DesertBossHead);
	CDesertBossCircleScript* DesertBossCircleScript = DesertBossCircle->AddComponent<CDesertBossCircleScript>(eComponentType::Script);
	DesertBossCircleScript->SetScene(this);
	CColliderMgr* BossCircleCdList = DesertBossCircle->AddComponent<CColliderMgr>(eComponentType::ColliderList);
	CCollider2D* CircleCDforBackground = new CCollider2D;
	CircleCDforBackground->SetSize(Vector2(0.5f, 0.5f));
	BossCircleCdList->AddCollider(CircleCDforBackground);
	CCollider2D* CircleCDforHit = new CCollider2D;
	CircleCDforHit->SetSize(Vector2(0.5f, 0.5f));
	BossCircleCdList->AddCollider(CircleCDforHit);


	CMonster* DesertBossRhombus = new CMonster();
	AddGameObject(eLayerType::Monster, DesertBossRhombus, L"DesertBossRhombus", Vector3(0.0f, 0.25f, 1.0006f)
		, Vector3(1.6f, 1.6f, 0.0f), true, L"Mesh", L"mt_DesertBossRhombus", true);
	DesertBossRhombus->SetParentObject(DesertBossCircle);
	CDesertBossRhombusScript* DesertBossRhombusScript = DesertBossRhombus -> AddComponent<CDesertBossRhombusScript>(eComponentType::Script);
	DesertBossRhombusScript->SetScene(this);

	CColliderMgr* BossRhombusCdList = DesertBossRhombus->AddComponent<CColliderMgr>(eComponentType::ColliderList);
	CCollider2D* RhombusCDforBackground = new CCollider2D;
	RhombusCDforBackground->SetSize(Vector2(0.5f, 0.5f));
	BossRhombusCdList->AddCollider(RhombusCDforBackground);
	CCollider2D* RhombusCDforHit = new CCollider2D;
	RhombusCDforHit->SetSize(Vector2(0.5f, 0.5f));
	BossRhombusCdList->AddCollider(RhombusCDforHit);

	CMonster* DesertBossSquare = new CMonster();
	AddGameObject(eLayerType::Monster, DesertBossSquare, L"DesertBossSquare", Vector3(-0.5f, 0.0f, 1.0007f)
		, Vector3(1.6f, 1.6f, 0.0f), true, L"Mesh", L"mt_DesertBossSquare", true);
	DesertBossSquare->SetParentObject(DesertBossRhombus);
	CDesertBossSquareScript* DesertBossSquareScript = DesertBossSquare->AddComponent<CDesertBossSquareScript>(eComponentType::Script);
	
	CColliderMgr* BossSquareCdList = DesertBossSquare->AddComponent<CColliderMgr>(eComponentType::ColliderList);
	CCollider2D* SquareCDforBackground = new CCollider2D;
	SquareCDforBackground->SetSize(Vector2(0.5f, 0.5f));
	BossSquareCdList->AddCollider(SquareCDforBackground);
	CCollider2D* SquareCDforHit = new CCollider2D;
	SquareCDforHit->SetSize(Vector2(0.5f, 0.5f));
	BossSquareCdList->AddCollider(SquareCDforHit);

	CMonster* DesertBossTriangle = new CMonster();
	AddGameObject(eLayerType::Monster, DesertBossTriangle, L"DesertBossTriangle", Vector3(-0.8f, -0.6f, 1.0008f)
		, Vector3(1.6f, 1.6f, 0.0f), true, L"Mesh", L"mt_DesertBossTriangle", true);
	DesertBossTriangle->SetParentObject(DesertBossSquare);
	CDesertBossTriangleScript* DesertBossTriangleScript = DesertBossTriangle->AddComponent<CDesertBossTriangleScript>(eComponentType::Script);
	DesertBossTriangleScript->SetScene(this);
	DesertBossTriangleScript->SetOtherPos(Will->GetComponent<CTransform>(eComponentType::Transform));
	
	CColliderMgr* BossTriangleCdList = DesertBossTriangle->AddComponent<CColliderMgr>(eComponentType::ColliderList);
	CCollider2D* TriangleCDforBackground = new CCollider2D;
	TriangleCDforBackground->SetSize(Vector2(0.5f, 0.5f));
	BossTriangleCdList->AddCollider(TriangleCDforBackground);
	CCollider2D* TriangleCDforHit = new CCollider2D;
	TriangleCDforHit->SetSize(Vector2(0.5f, 0.5f));
	BossTriangleCdList->AddCollider(TriangleCDforHit);
	 
	{ // boss HP
		CGameObject* DesertBossHP = new CGameObject();
		CHPScript* hpScript = DesertBossHP->AddComponent<CHPScript>(eComponentType::Script);
		DesertBossHP->SetParentObject(DesertBossHead);
		AddGameObject(eLayerType::UI, DesertBossHP, L"DesertBossHP", Vector3(0.0f, -2.0f, -0.1f),
			Vector3(3.f, 0.1f, 0.0f), true, L"Mesh", L"mt_DesertBoss_HealthBar", false);
		CMeshRender* mr = DesertBossHP->GetComponent<CMeshRender>(eComponentType::MeshRender);
	}


	{ // light
		CGameObject* light = new CGameObject();
		light->SetName(L"light");
		AddGameObject(eLayerType::Light, light, L"light", Vector3(0.0f, 0.0f,  0.0f), Vector3(0.0f, 0.0f, 0.0f), false, L"", L"", false);
		CLight* lightComp = light->AddComponent<CLight>(eComponentType::Light);
		lightComp->SetLightType(eLightType::Directional);
		lightComp->SetColor(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	}

	// background particle
	{
		CGameObject* particle = new CGameObject();

		particle->SetName(L"Particle");
		AddGameObject(eLayerType::Monster, particle, L"Particle", Vector3(0.0f, 0.0f, 1.0f), Vector3(0.2f, 0.2f, 0.2f), false, L"", L"", false);
		CParticleSystem* pts = particle->AddComponent<CParticleSystem>(eComponentType::Light);
	}
	
	CScene::Initialize(); 
}

void CDesertBossScene::Update()
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

void CDesertBossScene::LateUpdate()
{
	CScene::LateUpdate();
}

void CDesertBossScene::Render()
{
	//CScene::Render();
}
