#include "CDesertDungeonScene.h"
#include "CDungeonMgr.h"
#include "CPlayer.h"

CDesertDungeonScene::CDesertDungeonScene()
{
}

CDesertDungeonScene::~CDesertDungeonScene()
{
}

void CDesertDungeonScene::Initialize()
{
	CDungeonMgr::GetInst()->CreateMap();

	// Doungeon Map
	//for (int i = 0; i < CDungeonMgr::GetInst()->GetMapListSize(); i++)
	//{
	//	CGameObject* Dungeon3_Map = new CGameObject;

	//	// map 의 텍스쳐 및 머터리얼 이름 추가
	//	std::wstring mapName = L"Dungeon3_Map";
	//	if (i < CDungeonMgr::GetInst()->GetMapListSize() - 1)
	//	{
	//		std::wstring MapNumberToString = std::to_wstring(i / 5 + 1);
	//		mapName += MapNumberToString;
	//	}
	//	std::wstring materialString = L"mt_" + mapName;

	//	// map 의 위치 지정

	//	AddGameObject(eLayerType::Background, Dungeon3_Map, mapName, Vector3(0.0f, 0.0f, 10.0000f),
	//		Vector3(14.0f, 13.0f, 0.0f), true, L"Mesh", materialString , false);
	//}
	CGameObject* Dungeon3_Map1 = new CGameObject;
	AddGameObject(eLayerType::Background, Dungeon3_Map1, L"Dungeon3_Map1", Vector3(0.0f, 0.0f, 10.000f),
		Vector3(14.0f, 13.0f, 0.0f), true, L"Mesh", L"mt_Dungeon3_Map1", false);
	CGameObject* Dungeon3_Map2 = new CGameObject;
	AddGameObject(eLayerType::Background, Dungeon3_Map2, L"Dungeon3_Map2", Vector3(-10.0f, 0.0f, 10.0001f),
		Vector3(14.0f, 13.0f, 0.0f), true, L"Mesh", L"mt_Dungeon3_Map2", false);
	CGameObject* Dungeon3_Map3 = new CGameObject;
	AddGameObject(eLayerType::Background, Dungeon3_Map3, L"Dungeon3_Map3", Vector3(0.0f, 5.0f, 10.0002f),
		Vector3(14.0f, 13.0f, 0.0f), true, L"Mesh", L"mt_Dungeon3_Map3", false);

	// Player
	// player
	CPlayer* Will = new CPlayer();
	AddGameObject(eLayerType::Player, Will, L"Will", Vector3(3.0f, 0.0f, 1.0002f)
		, Vector3(0.25f, 0.47f, 0.0f), true, L"Mesh", L"mt_atlas_Will_Idle_Down", true);
	CTransform* PlayerTr = Will->GetComponent<CTransform>(eComponentType::Transform);


	// Main Camera
	CGameObject* mainCamera = new CGameObject();
	AddGameObject(eLayerType::Camera, mainCamera, L"MainCamera", Vector3(0.0f, 0.0f, -10.0f),
		Vector3(1.0f, 1.0f, 1.0f), false, L"", L"", false);
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

	CGameObject* light = new CGameObject();
	light->SetName(L"light");
	AddGameObject(eLayerType::Light, light, L"light", Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), false, L"", L"", false);
	CLight* lightComp = light->AddComponent<CLight>();
	lightComp->SetType(eLightType::Directional);
	lightComp->SetColor(Vector4(0.8f, 0.8f, 0.8f, 1.0f));

	CScene::Initialize();
}

void CDesertDungeonScene::Update()
{
	

	CScene::Update();
}

void CDesertDungeonScene::LateUpdate()
{
	CScene::LateUpdate();
}

void CDesertDungeonScene::Render()
{
	CScene::Render();
}
