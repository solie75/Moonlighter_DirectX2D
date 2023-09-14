#include "CTestScene.h"
#include "CPlayer.h"
#include "CMonster.h"
#include "CComputeShader.h"
#include "CPaintShader.h"
#include "CParticleSystem.h"
#include "CWeapon.h"
#include "CCollisionMgr.h"

CTestScene::CTestScene()
{
}

CTestScene::~CTestScene()
{
}

void CTestScene::Initialize()
{
	CCollisionMgr::GetInst()->SetCollideLayer(eLayerType::PlayerProjectile, eLayerType::Monster, true);
	CCollisionMgr::GetInst()->SetCollideLayer(eLayerType::PlayerProjectile, eLayerType::Background, true);

	std::shared_ptr<CPaintShader> paintShader = CResourceMgr::GetInst()->Find<CPaintShader>(L"PaintShader"); // paintShader ∞° empty ¿Ã¥Ÿ.
	std::shared_ptr<CTexture> paintTexture = CResourceMgr::GetInst()->Find<CTexture>(L"PaintTexture");
	paintShader->SetTarget(paintTexture);
	paintShader->OnExcute();

	CGameObject* BackgroundLeft = new CGameObject();
	AddGameObject(eLayerType::Background, BackgroundLeft, L"BackgroundLeft", Vector3(-6.625f, 0.0f, 10.0006f),
		Vector3(1.0f, 1.0f, 0.0f), false, L"Mesh", L"", false);
	CCollider2D* backgroundCd = BackgroundLeft->AddComponent<CCollider2D>();
	backgroundCd->SetSize(Vector2(0.3f, 10.f));

	// Will
	CPlayer* Will = new CPlayer();
	AddGameObject(eLayerType::Player, Will, L"Will", Vector3(3.0f, 0.0f, 1.0002f)
		, Vector3(0.25f, 0.47f, 0.0f), true, L"Mesh", L"mt_atlas_Will_Idle_Down", true);
	CTransform* PlayerTr = Will->GetComponent<CTransform>(eComponentType::Transform);

	// Weapon
	CWeapon* Weapon = new CWeapon();
	AddGameObject(eLayerType::Player, Weapon, L"Weapon", Vector3(0.0f, 0.0f, 0.0f),
		Vector3(1.0f, 1.0f, 0.0f), true, L"Mesh", L"", true);
	//Weapon->SetPlayerToWeapon(Will);
	Weapon->SetParentObject(Will);
	Weapon->SetScene(this);

	Will->SetWeapon(Weapon);

	// Smile
	CMonster* Smile = new CMonster();
	AddGameObject(eLayerType::Monster, Smile, L"Smile", Vector3(-2.0f, 0.0f, 1.0003f)
		, Vector3(1.0f, 1.0f, 0.0f), true, L"Mesh", L"mt_Smile", false);
	CMeshRender* mr = Smile->GetComponent<CMeshRender>(eComponentType::MeshRender);
	std::shared_ptr<CMaterial> mt = mr->GetMaterial();
	Smile->AddComponent<CCollider2D>();
	//mt->SetTexture(paintTexture);

	// Particle
	CGameObject* particle = new CGameObject();
	particle->SetName(L"Particle");
	AddGameObject(eLayerType::Monster, particle, L"Particle", Vector3(0.0f, 0.0f, 1.0f), Vector3(0.2f, 0.2f, 0.2f), false, L"", L"", false);
	CParticleSystem* pts = particle->AddComponent<CParticleSystem>();


	// Camera
	CGameObject* mainCamera = new CGameObject();
	AddGameObject(eLayerType::Camera, mainCamera, L"MainCamera", Vector3(0.0f, 0.0f, -10.0f),
		Vector3(1.0f, 1.0f, 1.0f), false, L"", L"", false);
	CCamera* mainCamComp = mainCamera->AddComponent<CCamera>();
	mainCamComp->SetCameraType(eCameraType::Main);
	mainCamComp->TurnLayerMask(eLayerType::UI, false);
	CCameraMoveScript* CameraMoveScript = mainCamera->AddComponent<CCameraMoveScript>();
	CameraMoveScript->SetPlayerTr(PlayerTr);

	// Light
	CGameObject* light = new CGameObject();
	light->SetName(L"light");
	AddGameObject(eLayerType::Light, light, L"light", Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), false, L"", L"", false);
	CLight* lightComp = light->AddComponent<CLight>();
	lightComp->SetType(eLightType::Directional);
	lightComp->SetColor(Vector4(1.0f, 1.0f, 1.0f, 1.0f));

	{
		CGameObject* light = new CGameObject();
		light->SetName(L"Smile");
		AddGameObject(eLayerType::Light, light, L"light", Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), false, L"", L"", false);
		CLight* lightComp = light->AddComponent<CLight>();
		lightComp->SetType(eLightType::Point);
		lightComp->SetColor(Vector4(0.0f, 0.0f, 1.0f, 1.0f));
		lightComp->SetRadius(3.0f);
	}

	CScene::Initialize();
}

void CTestScene::Update()
{
	CScene::Update();
}

void CTestScene::LateUpdate()
{
	CScene::LateUpdate();
}

void CTestScene::Render()
{
	CScene::Render();
}
