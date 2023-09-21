#include "CDesertDungeonScene.h"
#include "CDungeonMgr.h"
#include "CCollider2D.h"
#include "CCollisionMgr.h"
#include "CWeapon.h"
#include "CTimeMgr.h"


CDesertDungeonScene::CDesertDungeonScene()
{
	player = new CPlayer;
	mainCamera = new CGameObject;
	mbTranslateMapPos = false;
}

CDesertDungeonScene::~CDesertDungeonScene()
{
}

void CDesertDungeonScene::Initialize()
{
	CCollisionMgr::GetInst()->SetCollideLayer(eLayerType::Player, eLayerType::Portal, true);

	// player
	//CPlayer* player = new CPlayer;
	AddGameObject(eLayerType::Player, player, L"Will", Vector3(2.0f, 0.0f, 1.0002f)
		, Vector3(0.25f, 0.47f, 0.0f), true, L"Mesh", L"mt_atlas_Will_Idle_Down", true);
	CTransform* PlayerTr = player->GetComponent<CTransform>(eComponentType::Transform);

	// weapon
	CWeapon* Weapon = new CWeapon();
	AddGameObject(eLayerType::Player, Weapon, L"Weapon", Vector3(0.0f, 0.0f, 0.0f),
		Vector3(1.0f, 1.0f, 0.0f), true, L"Mesh", L"", true);
	//Weapon->SetPlayerToWeapon(Will);
	Weapon->SetParentObject(player);
	Weapon->SetScene(this);

	player->SetWeapon(Weapon);

	// Main Camera
	//CGameObject* mainCamera = new CGameObject;
	AddGameObject(eLayerType::Camera, mainCamera, L"MainCamera", Vector3(0.0f, 0.0f, -10.0f),
		Vector3(1.0f, 1.0f, 1.0f), false, L"", L"", false);
	CCamera* mainCamComp = mainCamera->AddComponent<CCamera>();
	mainCamComp->SetCameraType(eCameraType::Main);
	mainCamComp->TurnLayerMask(eLayerType::UI, false);
	CCameraMoveScript* CameraMoveScript = mainCamera->GetComponent<CCameraMoveScript>(eComponentType::Script);
	CameraMoveScript->ChangeCameraFocusing(CCameraMoveScript::eCameraFocusing::Map);
	CameraMoveScript->SetMapPos(Vector2(0.0f, 0.0f));
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
	uiCamComp->TurnLayerMask(eLayerType::Portal, false);

	// light
	CGameObject* light = new CGameObject();
	light->SetName(L"light");
	AddGameObject(eLayerType::Light, light, L"light", Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), false, L"", L"", false);
	CLight* lightComp = light->AddComponent<CLight>();
	lightComp->SetType(eLightType::Directional);
	lightComp->SetColor(Vector4(0.8f, 0.8f, 0.8f, 1.0f));

	// ���� �ʱ�ȭ
	CDungeonMgr::GetInst()->CreateMap();
	UINT BasicDoorNum = 0;

	for (int i = 0; i < CDungeonMgr::GetInst()->GetMapListSize(); i++)
	{
		CGameObject* Dungeon3_Map = new CGameObject;

		
		std::wstring mapName = L"Dungeon3_Map";
		Vector2 mapPosVec2 = CDungeonMgr::GetInst()->GetMapPos(i);

		// Dongeon Entrance
		if (mapPosVec2.x == 3 && mapPosVec2.y == 3)
		{
			AddGameObject(eLayerType::Background, Dungeon3_Map, L"Dungeon3_Map8", Vector3(0.0f, 0.0f, 10.0000f + (0.0001f * i)),
				Vector3(8.2f, 4.49f, 0.0f), true, L"Mesh", L"mt_Dungeon3_Map8", false);
			
			mapPosVec2.x = mapPosVec2.x - 3;
			mapPosVec2.y = (mapPosVec2.y * -1) + 3;

			// Basic Door Setting
			vector<CDungeonMgr::eGateDirection> gateList = CDungeonMgr::GetInst()->GetDoorList(i);
			for (int j = 0; j < gateList.size(); j++) // ���⿡�� 3�� �� map �� ������ �ִ� door �� ����
			{
				BasicDoorNum++;

				CGameObject* Dungeon3_BasicDoor = new CGameObject;
				CTransform* BasicDoorTr = Dungeon3_BasicDoor->GetComponent<CTransform>(eComponentType::Transform);
				double pi = 3.14159265358979323846;

				Vector2 inputVector = mapPosVec2;

				float yValue = 1.8f;
				float xValue = 3.2f;

				switch (gateList[j])
				{ // �߽��� �������� �� �ʿ��� Door �� ��濡 ��� ��ġ�� ���� ������ ��ġ ����
				case CDungeonMgr::eGateDirection::Down :
					inputVector.y -= yValue; // �뷫�� ����
					BasicDoorTr->SetRotation(Vector3(0.0f, 0.0f, pi));
					break;
				case CDungeonMgr::eGateDirection::Left:
					inputVector.x -= xValue; // �뷫�� ����
					BasicDoorTr->SetRotation(Vector3(0.0f, 0.0f, pi / 2));
					break;
				case CDungeonMgr::eGateDirection::Right:
					inputVector.x += xValue; // �뷫�� ����
					BasicDoorTr->SetRotation(Vector3(0.0f, 0.0f, -(pi / 2)));
					break;
				case CDungeonMgr::eGateDirection::Up:
					inputVector.y += yValue; // �뷫�� ����
					break;
				}

				AddGameObject(eLayerType::Portal, Dungeon3_BasicDoor, L"Dungeon3_BasicDoor", Vector3(inputVector.x, inputVector.y, 10.000f - (0.0001f * BasicDoorNum)),
					Vector3(1.0f, 1.0f, 0.0f), true, L"Mesh", L"", true);
				// Basic Door �ִϸ��̼�
				CAnimator* BasicDoorAt = Dungeon3_BasicDoor->GetComponent<CAnimator>(eComponentType::Animator);
				BasicDoorAt->PlayAnimation(L"Dungeon3_BasicDoor_Cycle", true);
				CCollider2D* BasicDoorCd = Dungeon3_BasicDoor->AddComponent<CCollider2D>();
				BasicDoorCd->SetSize(Vector2(0.3f, 0.3f));
			}
		}
		// Dongeon normal map
		else
		{
			mapPosVec2.x = mapPosVec2.x - 3;
			mapPosVec2.y = (mapPosVec2.y * -1) + 3;

			mapPosVec2.x *= mXPosStandard;
			mapPosVec2.y *= mYPosStandard;

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
			else if (i == CDungeonMgr::GetInst()->GetMapListSize() - 1)
			{
				AddGameObject(eLayerType::Background, Dungeon3_Map, L"Dungeon3_Map7", mapPosVec3,
					Vector3(8.2f, 4.49f, 0.0f), true, L"Mesh", L"mt_Dungeon3_Map7", false);
			}

			// BasicDoor Setting
			vector<CDungeonMgr::eGateDirection> gateList = CDungeonMgr::GetInst()->GetDoorList(i);
			for (int j = 0; j < gateList.size(); j++) // ���⿡�� 3�� �� map �� ������ �ִ� door �� ����
			{
				BasicDoorNum++;

				CGameObject* Dungeon3_BasicDoor = new CGameObject;
				CTransform* BasicDoorTr = Dungeon3_BasicDoor->GetComponent<CTransform>(eComponentType::Transform);
				double pi = 3.14159265358979323846;

				Vector2 inputVector = mapPosVec2;

				float yValue = 1.8f;
				float xValue = 3.2f;

				switch (gateList[j])
				{ // �߽��� �������� �� �ʿ��� Door �� ��濡 ��� ��ġ�� ���� ������ ��ġ ����
				case CDungeonMgr::eGateDirection::Down:
					inputVector.y -= yValue; // �뷫�� ����
					BasicDoorTr->SetRotation(Vector3(0.0f, 0.0f, pi));
					break;
				case CDungeonMgr::eGateDirection::Left:
					inputVector.x -= xValue; // �뷫�� ����
					BasicDoorTr->SetRotation(Vector3(0.0f, 0.0f, pi / 2));
					break;
				case CDungeonMgr::eGateDirection::Right:
					inputVector.x += xValue; // �뷫�� ����
					BasicDoorTr->SetRotation(Vector3(0.0f, 0.0f, -(pi / 2)));
					break;
				case CDungeonMgr::eGateDirection::Up:
					inputVector.y += yValue; // �뷫�� ����
					break;
				}

				AddGameObject(eLayerType::Portal, Dungeon3_BasicDoor, L"Dungeon3_BasicDoor", Vector3(inputVector.x, inputVector.y, 10.000f - (0.001f * BasicDoorNum)),
					Vector3(1.0f, 1.0f, 0.0f), true, L"Mesh", L"", true);
				// Basic Door �ִϸ��̼�
				CAnimator* BasicDoorAt = Dungeon3_BasicDoor->GetComponent<CAnimator>(eComponentType::Animator);
				BasicDoorAt->PlayAnimation(L"Dungeon3_BasicDoor_Cycle", true);
				CCollider2D* BasicDoorCd = Dungeon3_BasicDoor->AddComponent<CCollider2D>();
				BasicDoorCd->SetSize(Vector2(0.3f, 0.3f));
			}
		}
	}
	CScene::Initialize();
}

void CDesertDungeonScene::Update()
{
	// map �� �̵�

	// 1. map �� �̵��ϴ� ���� (player �� door �� �浹
	CCollider2D* playerCD = player->GetComponent<CCollider2D>(eComponentType::Collider2D);
	CTransform* playerTr = player->GetComponent<CTransform>(eComponentType::Transform);
	CCameraMoveScript* mainCameraScript = mainCamera->GetComponent<CCameraMoveScript>(eComponentType::Script);

	Vector2 doorPos = playerCD->GetColliderData(eLayerType::Portal).pos;
	CTransform* mainCamTr = mainCameraScript->GetOwner()->GetComponent<CTransform>(eComponentType::Transform);
	Vector3 mainCamPos = mainCamTr->GetPosition();

	if (mbTranslateMapPos == true)
	{
		

		float diff = Vector2::Distance(Vector2(mainCamPos.x, mainCamPos.y), NextMapPos);
		if (diff < 0.1f)
		{
			mainCamTr->SetPosition(Vector3(NextMapPos.x, NextMapPos.y, mainCamPos.z));
			mbTranslateMapPos = false;
		}
		else
		{
			if (mainCamPos.x > NextMapPos.x)
			{
				mainCamPos.x -= (float)(5.0 * CTimeMgr::GetInst()->GetDeltaTime());
				mainCamTr->SetPosition(mainCamPos);
			}
			else if (mainCamPos.x < NextMapPos.x)
			{
				mainCamPos.x += (float)(5.0 * CTimeMgr::GetInst()->GetDeltaTime());
				mainCamTr->SetPosition(mainCamPos);
			}
			else if (mainCamPos.y > NextMapPos.y)
			{
				mainCamPos.y -= (float)(5.0 * CTimeMgr::GetInst()->GetDeltaTime());
				mainCamTr->SetPosition(mainCamPos);
			}
			else if (mainCamPos.y < NextMapPos.y)
			{
				mainCamPos.y += (float)(5.0 * CTimeMgr::GetInst()->GetDeltaTime());
				mainCamTr->SetPosition(mainCamPos);
			}
		}
	}

	if (playerCD->GetColliderData(eLayerType::Portal).id != 0 && mbTranslateMapPos == false)
	{
		mbTranslateMapPos = true;
		
		if (doorPos.x > mainCamPos.x) // ����������
		{
			NextMapPos = Vector2(mainCamPos.x + mXPosStandard, mainCamPos.y);
		}
		else if (doorPos.x < mainCamPos.x) // ��������
		{
			NextMapPos = Vector2(mainCamPos.x - mXPosStandard, mainCamPos.y);
		}
		else if (doorPos.y < mainCamPos.y) // �Ʒ�������
		{
			NextMapPos = Vector2(mainCamPos.x, mainCamPos.y - mYPosStandard);
		}
		else if (doorPos.y > mainCamPos.y) // ��������
		{
			NextMapPos = Vector2(mainCamPos.x, mainCamPos.y + mYPosStandard);
		}
	}

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