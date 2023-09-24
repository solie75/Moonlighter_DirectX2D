#include "CDesertDungeonScene.h"
#include "CDungeonMgr.h"
#include "CCollider2D.h"
#include "CCollisionMgr.h"
#include "CWeapon.h"
#include "CTimeMgr.h"
#include "CPlayerMoveScript.h"


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

	CGameObject* BackgroundCollider = new CGameObject();
	AddGameObject(eLayerType::Background, BackgroundCollider, L"BackgroundCollider"
		// 여기
		, Vector3(2.75f, -1.46f, 2.000f)
		, Vector3(0.6f, 0.3f, 0.0f), false, L"Mesh", L"", false);
	CCollider2D* cd = BackgroundCollider->AddComponent<CCollider2D>();
	//cd->SetSize(Vector2(13.5f, 0.3f));

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

	// 맴의 초기화
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
			/*AddGameObject(eLayerType::Background, Dungeon3_Map, L"Dungeon3_Map8", Vector3(0.0f, 0.0f, 10.0000f + (0.0001f * i)),
				Vector3(8.2f, 4.49f, 0.0f), true, L"Mesh", L"mt_Dungeon3_Map8", false);
			*/
			AddGameObject(eLayerType::Background, Dungeon3_Map, L"Dungeon3_Map8", Vector3(0.0f, 0.0f, 10.0000f + (0.0001f * i)),
				Vector3(8.2f, 4.49f, 0.0f), true, L"Mesh", L"mt_Dungeon3_Map8", false);


			mapPosVec2.x = mapPosVec2.x - 3;
			mapPosVec2.y = (mapPosVec2.y * -1) + 3;

			// Basic Door Setting
			vector<CDungeonMgr::eGateDirection> gateList = CDungeonMgr::GetInst()->GetDoorList(i);
			for (int j = 0; j < gateList.size(); j++) // 여기에서 3은 한 map 이 가지고 있는 door 의 숫자
			{
				BasicDoorNum++;

				CGameObject* Dungeon3_BasicDoor = new CGameObject;
				CTransform* BasicDoorTr = Dungeon3_BasicDoor->GetComponent<CTransform>(eComponentType::Transform);
				double pi = 3.14159265358979323846;

				Vector2 inputVector = mapPosVec2;

				float yValue = 1.8f;
				float xValue = 3.2f;

				switch (gateList[j])
				{ // 중심을 기준으로 한 맵에서 Door 가 사방에 어느 위치에 존재 할지의 수치 추정
				case CDungeonMgr::eGateDirection::Down :
					inputVector.y -= yValue; // 대략의 숫자
					BasicDoorTr->SetRotation(Vector3(0.0f, 0.0f, pi));
					break;
				case CDungeonMgr::eGateDirection::Left:
					inputVector.x -= xValue; // 대략의 숫자
					BasicDoorTr->SetRotation(Vector3(0.0f, 0.0f, pi / 2));
					break;
				case CDungeonMgr::eGateDirection::Right:
					inputVector.x += xValue; // 대략의 숫자
					BasicDoorTr->SetRotation(Vector3(0.0f, 0.0f, -(pi / 2)));
					break;
				case CDungeonMgr::eGateDirection::Up:
					inputVector.y += yValue; // 대략의 숫자
					break;
				}

				AddGameObject(eLayerType::Portal, Dungeon3_BasicDoor, L"Dungeon3_BasicDoor", Vector3(inputVector.x, inputVector.y, 10.000f - (0.0001f * BasicDoorNum)),
					Vector3(1.0f, 1.0f, 0.0f), true, L"Mesh", L"", true);
				// Basic Door 애니메이션
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
			 .y *= mYPosStandard;

			Vector3 mapPosVec3 = Vector3(mapPosVec2.x, mapPosVec2.y, 10.0000f + (0.00001f * i));

			if (i < CDungeonMgr::GetInst()->GetMapListSize() - 2)
			{
				// map 의 텍스쳐 및 머터리얼 이름 추가
				std::wstring MapNumberToString = std::to_wstring(i % 5 + 1);
				mapName += MapNumberToString;

				std::wstring materialString = L"mt_" + mapName;

				// map 의 위치 지정
				AddGameObject(eLayerType::Background, Dungeon3_Map, mapName, mapPosVec3,
					Vector3(8.2f, 4.49f, 0.0f), true, L"Mesh", materialString, false);

				// 여기에서 각 map 에 맞는 Collider와 Monster 추가.
				// 이렇게 미리 추가하면 한번에 계산해야할 연산량이 너무 많다.
			}
			else if (i == CDungeonMgr::GetInst()->GetMapListSize() - 2)
			{
				AddGameObject(eLayerType::Background, Dungeon3_Map, L"Dungeon3_Map6", mapPosVec3,
					Vector3(8.2f, 4.49f, 0.0f), true, L"Mesh", L"mt_Dungeon3_Map6", false);
				// 여기에서 heal pool 추가
			}
			else if (i == CDungeonMgr::GetInst()->GetMapListSize() - 1)
			{
				AddGameObject(eLayerType::Background, Dungeon3_Map, L"Dungeon3_Map7", mapPosVec3,
					Vector3(8.2f, 4.49f, 0.0f), true, L"Mesh", L"mt_Dungeon3_Map7", false);
			}

			// BasicDoor Setting
			vector<CDungeonMgr::eGateDirection> gateList = CDungeonMgr::GetInst()->GetDoorList(i);
			for (int j = 0; j < gateList.size(); j++) // 여기에서 3은 한 map 이 가지고 있는 door 의 숫자
			{
				BasicDoorNum++;

				CGameObject* Dungeon3_BasicDoor = new CGameObject;
				CTransform* BasicDoorTr = Dungeon3_BasicDoor->GetComponent<CTransform>(eComponentType::Transform);
				double pi = 3.14159265358979323846;

				Vector2 inputVector = mapPosVec2;

				float yValue = 1.8f;
				float xValue = 3.2f;

				switch (gateList[j])
				{ // 중심을 기준으로 한 맵에서 Door 가 사방에 어느 위치에 존재 할지의 수치 추정
				case CDungeonMgr::eGateDirection::Down:
					inputVector.y -= yValue; // 대략의 숫자
					BasicDoorTr->SetRotation(Vector3(0.0f, 0.0f, pi));
					break;
				case CDungeonMgr::eGateDirection::Left:
					inputVector.x -= xValue; // 대략의 숫자
					BasicDoorTr->SetRotation(Vector3(0.0f, 0.0f, pi / 2));
					break;
				case CDungeonMgr::eGateDirection::Right:
					inputVector.x += xValue; // 대략의 숫자
					BasicDoorTr->SetRotation(Vector3(0.0f, 0.0f, -(pi / 2)));
					break;
				case CDungeonMgr::eGateDirection::Up:
					inputVector.y += yValue; // 대략의 숫자
					break;
				}

				AddGameObject(eLayerType::Portal, Dungeon3_BasicDoor, L"Dungeon3_BasicDoor", Vector3(inputVector.x, inputVector.y, 10.000f - (0.001f * BasicDoorNum)),
					Vector3(1.0f, 1.0f, 0.0f), true, L"Mesh", L"", true);
				// Basic Door 애니메이션
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
	// map 의 이동

	// 1. map 이 이동하는 조건 (player 와 door 의 충돌
	CCollider2D* playerCD = player->GetComponent<CCollider2D>(eComponentType::Collider2D);
	CPlayerMoveScript* playerST = player->GetComponent<CPlayerMoveScript>(eComponentType::Script);
	CTransform* playerTr = player->GetComponent<CTransform>(eComponentType::Transform);
	CCameraMoveScript* mainCameraScript = mainCamera->GetComponent<CCameraMoveScript>(eComponentType::Script);

	Vector2 doorPos = playerCD->GetColliderData(eLayerType::Portal).pos;
	CTransform* mainCamTr = mainCameraScript->GetOwner()->GetComponent<CTransform>(eComponentType::Transform);
	Vector3 mainCamPos = mainCamTr->GetPosition();
	CState* playerState = player->GetState();


	// map 의 이동
	if (mbTranslateMapPos == true)
	{
		float diff = Vector2::Distance(Vector2(mainCamPos.x, mainCamPos.y), NextMapPos);
		if (diff < 0.1f)
		{
			mainCamTr->SetPosition(Vector3(NextMapPos.x, NextMapPos.y, mainCamPos.z));
			mbTranslateMapPos = false;
			playerState->SetBoolStateChange(true);
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

	// 맵 이동 시에 플레이어의 이동
	if (playerCD->GetColliderData(eLayerType::Portal).id != 0 && mbTranslateMapPos == false)
	{
		mbTranslateMapPos = true;
		playerState->SetBoolStateChange(false);
		
		Vector3 playerPos = playerTr->GetPosition();

		if (doorPos.x > mainCamPos.x) // 오른쪽으로
		{
			NextMapPos = Vector2(mainCamPos.x + mXPosStandard, mainCamPos.y);
			playerPos.x += 2.5f;
			playerTr->SetPosition(playerPos);
		}
		else if (doorPos.x < mainCamPos.x) // 왼쪽으로
		{
			NextMapPos = Vector2(mainCamPos.x - mXPosStandard, mainCamPos.y);
			playerPos.x -= 2.5f;
			playerTr->SetPosition(playerPos);
		}
		else if (doorPos.y < mainCamPos.y) // 아래쪽으로
		{
			NextMapPos = Vector2(mainCamPos.x, mainCamPos.y - mYPosStandard);
			playerPos.y -= 1.6f;
			playerTr->SetPosition(playerPos);
		}
		else if (doorPos.y > mainCamPos.y) // 위쪽으로
		{
			NextMapPos = Vector2(mainCamPos.x, mainCamPos.y + mYPosStandard);
			playerPos.y += 1.6f;
			playerTr->SetPosition(playerPos);
		}

		// NextMapPos 를 근거로 해당 Map의 번호를 가져올 수 있나?
		Vector2 mapNum = Vector2(NextMapPos.x / mXPosStandard, NextMapPos.y / mYPosStandard);
		mapNum.x += 3;
		mapNum.y *= -1;
		mapNum.y += 3;
		mapNum;
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