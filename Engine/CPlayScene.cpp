#include "CPlayScene.h"
#include "CMeshRender.h"
#include "CResourceMgr.h"
#include "CCameraMoveScript.h"
#include "CPlayerMoveScript.h"
#include "CGridScript.h"
#include "CAnimator.h"
#include "CCollisionMgr.h"
#include "CPlayer.h"

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
		Vector3(1.0f, 1.0f, 1.0f), true, L"Mesh", L"mt_Link", false);
	CCollider2D* cd = player1->AddComponent<CCollider2D>();

	// Smile
	CGameObject* smile = new CGameObject();
	AddGameObject(eLayerType::UI, smile, L"Smile", Vector3(0.2f, 0.0f, 1.0f),
		Vector3(1.0f, 1.0f, 1.0f), true, L"Mesh", L"mt_Smile",false);


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

	CPlayer* Will = new CPlayer();
	AddGameObject(eLayerType::Player, Will, L"Will", Vector3(3.0f, 0.0f, 1.0002f)
		, Vector3(0.25f, 0.47f, 0.0f), true, L"Mesh", L"mt_atlas_Will_Idle_Down", true);

	{ // light
		CGameObject* light = new CGameObject();
		light->SetName(L"light");
		AddGameObject(eLayerType::Light, light, L"light", Vector3(0.0f, 0.0f,  0.0f), Vector3(0.0f, 0.0f, 0.0f), false, L"", L"", false);
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
