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

	 // dongeon Map �� ��ǥ �̵� ������ x : 8.202f, y : 4.492f �̴�. 
	 // Doungeon Map
	float xPosStandard = 8.202f;
	float yPosStandard = 4.492f;

	for (int i = 0; i < CDungeonMgr::GetInst()->GetMapListSize(); i++)
	{
		CGameObject* Dungeon3_Map = new CGameObject;

		
		std::wstring mapName = L"Dungeon3_Map";
		Vector2 mapPosVec2 = CDungeonMgr::GetInst()->GetMapPos(i);

		// (3,2) �� ��� ���� ��ĭ �̴ϱ� (0, 4.492 �� �Ǿ�� �Ѵ�. -> 3,3 ���� 3.2 �� ����.
		// (3,4) �� ��� �Ʒ��� ��ĭ �̴ϱ� (0, -4���ñ�) -> 3,3 ���� 3,4 �� ����. �׷� 0 -1 dl ehlsek.
		mapPosVec2.x = 3 - mapPosVec2.x;
		mapPosVec2.y = 3 - mapPosVec2.y;

		mapPosVec2.x *= xPosStandard;
		mapPosVec2.y *= yPosStandard;

		Vector3 mapPosVec3 = Vector3(mapPosVec2.x, mapPosVec2.y, 10.0000f + (0.00001f * i)); 

		if (i < CDungeonMgr::GetInst()->GetMapListSize() - 2)
		{
			// map �� �ؽ��� �� ���͸��� �̸� �߰�
			std::wstring MapNumberToString = std::to_wstring(i % 5 + 1);
			mapName += MapNumberToString;

			std::wstring materialString = L"mt_" + mapName;

			// map �� ��ġ ����
			AddGameObject(eLayerType::Background, Dungeon3_Map, mapName, mapPosVec3,
				Vector3(8.2f, 4.49f, 0.0f), true, L"Mesh", materialString, false);
		}
		else if (i == CDungeonMgr::GetInst()->GetMapListSize() - 2)
		{
			AddGameObject(eLayerType::Background, Dungeon3_Map, L"Dungeon3_Map6", mapPosVec3,
				Vector3(8.2f, 4.49f, 0.0f), true, L"Mesh", L"mt_Dungeon3_Map6", false);
		}
		else if (i == CDungeonMgr::GetInst()->GetMapListSize()-1)
		{
			AddGameObject(eLayerType::Background, Dungeon3_Map, L"Dungeon3_Map7", mapPosVec3,
				Vector3(8.2f, 4.49f, 0.0f), true, L"Mesh", L"mt_Dungeon3_Map7", false);
		}

		
	}

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
