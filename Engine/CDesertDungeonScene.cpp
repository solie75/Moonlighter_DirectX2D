#include "CDesertDungeonScene.h"
#include "CDungeonMgr.h"
#include "CCollider2D.h"
#include "CColliderMgr.h"
#include "CCollisionMgr.h"
#include "CWeapon.h"
#include "CTimeMgr.h"
#include "CPlayerMoveScript.h"
#include "CKatamariScript.h"
#include "CGolemSoldierScript.h"
#include "CHPScript.h"
#include "CNaviScript.h"


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
	CCollisionMgr::GetInst()->SetCollideLayer(eLayerType::Player, eLayerType::Background, true);
	CCollisionMgr::GetInst()->SetCollideLayer(eLayerType::Player, eLayerType::Monster, true);
	CCollisionMgr::GetInst()->SetCollideLayer(eLayerType::Background, eLayerType::Monster, true);
	CCollisionMgr::GetInst()->SetCollideLayer(eLayerType::PlayerProjectile, eLayerType::Monster, true);
	CCollisionMgr::GetInst()->SetCollideLayer(eLayerType::Node, eLayerType::Background, true);

	// player
	//CPlayer* player = new CPlayer;
	AddGameObject(eLayerType::Player, player, L"Will", Vector3(2.0, 0.0f, 1.0002f)
		, Vector3(0.25f, 0.47f, 0.0f), true, L"Mesh", L"mt_atlas_Will_Idle_Down", true);
	CTransform* PlayerTr = player->GetComponent<CTransform>(eComponentType::Transform);

	// Monster (Katamari)
	//CGameObject* Katamari = new CGameObject;
	//AddGameObject(eLayerType::Monster, Katamari, L"Katamari", Vector3(-2.0f, 0.0f, 4.0003f)
	//	, Vector3(0.6f, 0.8f, 0.0f), true, L"Mesh", L"", true);
	//CKatamariScript* KatamariScript = Katamari->AddComponent<CKatamariScript>(eComponentType::Script);

	//// Monster HP
	//CGameObject* KatamariHP_Background = new CGameObject;
	//KatamariHP_Background->SetParentObject(Katamari);
	//AddGameObject(eLayerType::HP, KatamariHP_Background, L"KatamariHP_Background", Vector3(0.0f, 0.0f, 0.0f)
	//	, Vector3(0.2f, 0.03f, 0.0f), true, L"Mesh", L"mt_HealthBar_Monster_Background", false);
	//CHPScript* HpBackground = KatamariHP_Background->AddComponent<CHPScript>(eComponentType::Script);
	//HpBackground->AddHpObject(this);
	//HpBackground->SetHpOffSet(Vector2(-0.12f, 0.15f));

	//KatamariScript->ChangeState(eState::Idle);

	//CColliderMgr* KatamariCdList = Katamari->AddComponent<CColliderMgr>(eComponentType::ColliderList);
	//
	//CCollider2D* KatamariCDforBackground = new CCollider2D;
	//KatamariCDforBackground->SetName(L"KatamariCDforBackground");
	//KatamariCDforBackground->SetCollideType(eCollideType::Background);
	//
	//KatamariCDforBackground->SetOffset(Vector2(0.0f, -0.24f));
	//KatamariCdList->AddCollider(KatamariCDforBackground);
	//KatamariCDforBackground->SetSize(Vector2(0.71f, 0.3f));

	//CCollider2D* KatamariCDforHit = new CCollider2D;
	//KatamariCDforHit->SetName(L"KatamariCDforHit");
	//KatamariCDforHit->SetCollideType(eCollideType::Hit);
	//
	//KatamariCDforHit->SetOffset(Vector2(0.0f, -0.12f));
	//KatamariCdList->AddCollider(KatamariCDforHit);
	//KatamariCDforHit->SetSize(Vector2(0.71f, 0.6f));

	// Monster (Soldier)
	//CGameObject* golemSoldier = new CGameObject;
	//AddGameObject(eLayerType::Monster, golemSoldier, L"GolemSoldier", Vector3(0.0f, 0.0f, 4.0004f)
	//	, Vector3(0.5f, 0.7f, 0.0f), true, L"Mesh", L"", true);
	//CNaviScript* NaviForGolemSoldier = golemSoldier->AddComponent<CNaviScript>(eComponentType::Script);
	//NaviForGolemSoldier->SetScene(this);
	////CGolemSoldierScript* golemSoldierScript = golemSoldier->AddComponent<CGolemSoldierScript>(eComponentType::Script);
	////NaviForGolemSoldier->SetObjScaleforDongeonMap(golemSoldierScript->GetScaleforDongeonMap());

	//CColliderMgr* golemSoldierCdList = golemSoldier->AddComponent<CColliderMgr>(eComponentType::ColliderList);

	//CCollider2D* golemSoldierCDforBackground = new CCollider2D;
	//golemSoldierCDforBackground->SetName(L"golemSoldierCDforBackground");
	//golemSoldierCDforBackground->SetCollideType(eCollideType::Background);

	//golemSoldierCDforBackground->SetOffset(Vector2(0.0f, 0.0f));
	//golemSoldierCdList->AddCollider(golemSoldierCDforBackground);
	//golemSoldierCDforBackground->SetSize(Vector2(0.5f, 0.5f));

	//CCollider2D* golemSoldierCDforHit = new CCollider2D;
	//golemSoldierCDforHit->SetName(L"KatamariCDforHit");
	//golemSoldierCDforHit->SetCollideType(eCollideType::Hit);

	//golemSoldierCDforHit->SetOffset(Vector2(0.0f, 0.0f));
	//golemSoldierCdList->AddCollider(golemSoldierCDforHit);
	//golemSoldierCDforHit->SetSize(Vector2(12.4f, 4.85f));


	// Background
	/*CGameObject* BackgroundTest = new CGameObject();
	AddGameObject(eLayerType::Background, BackgroundTest, L"BackgroundTest", Vector3(-3.1f, -1.7f, 4.0005f),
		Vector3(0.1, 0.1f, 0.0f), false, L"Mesh", L"", false);
	CColliderMgr* BackgroundTestCDList = BackgroundTest->AddComponent<CColliderMgr>(eComponentType::ColliderList);
	BackgroundTestCDList->AddCollider(new CCollider2D);*/

	CGameObject* BackgroundUp = new CGameObject();
	AddGameObject(eLayerType::Background, BackgroundUp, L"BackgroundBorderUp", Vector3(0.0f, 1.8f, 4.0001f),
		Vector3(8.0f, 0.2f, 0.0f), false, L"Mesh", L"", false);
	CColliderMgr* BackgroundUpCDList = BackgroundUp->AddComponent<CColliderMgr>(eComponentType::ColliderList);
	BackgroundUpCDList->AddCollider(new CCollider2D);

	CGameObject* BackgroundDown = new CGameObject();
	AddGameObject(eLayerType::Background, BackgroundDown, L"BackgroundBorderDown", Vector3(0.0f, -1.8f, 4.0002f),
		Vector3(8.0f, 0.2f, 0.0f), false, L"Mesh", L"", false);
	CColliderMgr* BackgroundDownCDList = BackgroundDown->AddComponent<CColliderMgr>(eComponentType::ColliderList);
	BackgroundDownCDList->AddCollider(new CCollider2D);

	CGameObject* BackgroundLeft = new CGameObject();
	AddGameObject(eLayerType::Background, BackgroundLeft, L"BackgroundBorderLeft", Vector3(-3.2f, 0.0f, 4.0003f),
		Vector3(0.2f, 4.0f, 0.0f), false, L"Mesh", L"", false);
	CColliderMgr* BackgroundLeftCDList = BackgroundLeft->AddComponent<CColliderMgr>(eComponentType::ColliderList);
	BackgroundLeftCDList->AddCollider(new CCollider2D);

	CGameObject* BackgroundRight = new CGameObject();
	AddGameObject(eLayerType::Background, BackgroundRight, L"BackgroundBorderRight", Vector3(3.2f, 0.0f, 4.0004f),
		Vector3(0.2f, 4.0f, 0.0f), false, L"Mesh", L"", false);
	CColliderMgr* BackgroundRightCDList = BackgroundRight->AddComponent<CColliderMgr>(eComponentType::ColliderList);
	BackgroundRightCDList->AddCollider(new CCollider2D);

	// weapon
	CWeapon* Weapon = new CWeapon();
	AddGameObject(eLayerType::Player, Weapon, L"Weapon", Vector3(0.0f, 0.0f, 0.0f),
		Vector3(1.0f, 1.0f, 0.0f), true, L"Mesh", L"", true);
	Weapon->SetParentObject(player);
	Weapon->SetScene(this);

	player->SetWeapon(Weapon);


	// Main Camera
	//CGameObject* mainCamera = new CGameObject;
	AddGameObject(eLayerType::Camera, mainCamera, L"MainCamera", Vector3(0.0f, 0.0f, -10.0f),
		Vector3(1.0f, 1.0f, 1.0f), false, L"", L"", false);
	CCamera* mainCamComp = mainCamera->AddComponent<CCamera>(eComponentType::Camera);
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
	CCamera* uiCamComp = uiCamera->AddComponent<CCamera>(eComponentType::Camera);
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
	CLight* lightComp = light->AddComponent<CLight>(eComponentType::Light);
	lightComp->SetLightType(eLightType::Directional);
	lightComp->SetColor(Vector4(0.8f, 0.8f, 0.8f, 1.0f));

	// ���� �ʱ�ȭ
	CDungeonMgr::GetInst()->CreateMap();
	UINT BasicDoorNum = 0;

	for (int i = 0; i < CDungeonMgr::GetInst()->GetMapListSize(); i++)
	{
		CGameObject* Dungeon3_Map = new CGameObject;

		std::wstring mapName = L"Dungeon3_Map";
		Vector2 mapPosVec2 = CDungeonMgr::GetInst()->GetMapPos(i);
		UINT MapNum = 0;

		// Dongeon Entrance
		if (mapPosVec2.x == 3 && mapPosVec2.y == 3)
		{
			AddGameObject(eLayerType::Background, Dungeon3_Map, L"Dungeon3_Map8", Vector3(0.0f, 0.0f, 10.0000f + (0.0001f * i)),
				Vector3(8.2f, 4.49f, 0.0f), true, L"Mesh", L"mt_Dungeon3_Map8", false);

			MapNum = mapPosVec2.x * 10 + mapPosVec2.y;

			mapPosVec2.x = mapPosVec2.x - 3;
			mapPosVec2.y = (mapPosVec2.y * -1) + 3;

			CDungeonMgr::GetInst()->SetMapNumList(MapNum, 8);

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
				CColliderMgr* BasicDoorCdList = Dungeon3_BasicDoor->AddComponent<CColliderMgr>(eComponentType::ColliderList);
				//CCollider2D* BasicDoorCd = Dungeon3_BasicDoor->AddComponent<CCollider2D>();
				
				CCollider2D* BasicDoorCd = new CCollider2D;
				BasicDoorCd->SetSize(Vector2(0.3f, 0.3f));
				BasicDoorCdList->AddCollider(BasicDoorCd);
			}
		}
		// Dongeon normal map
		else
		{
			MapNum = mapPosVec2.x * 10 + mapPosVec2.y;

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
				CDungeonMgr::GetInst()->SetMapNumList(MapNum, i % 5 + 1);

				// ���⿡�� �� map �� �´� Collider�� Monster �߰�.
				// �̷��� �̸� �߰��ϸ� �ѹ��� ����ؾ��� ���귮�� �ʹ� ����.
			}
			else if (i == CDungeonMgr::GetInst()->GetMapListSize() - 2)
			{
				AddGameObject(eLayerType::Background, Dungeon3_Map, L"Dungeon3_Map6", mapPosVec3,
					Vector3(8.2f, 4.49f, 0.0f), true, L"Mesh", L"mt_Dungeon3_Map6", false);
				CDungeonMgr::GetInst()->SetMapNumList(MapNum, 6);
				// ���⿡�� heal pool �߰�
			}
			else if (i == CDungeonMgr::GetInst()->GetMapListSize() - 1)
			{
				AddGameObject(eLayerType::Background, Dungeon3_Map, L"Dungeon3_Map7", mapPosVec3,
					Vector3(8.2f, 4.49f, 0.0f), true, L"Mesh", L"mt_Dungeon3_Map7", false);
				CDungeonMgr::GetInst()->SetMapNumList(MapNum, 7);
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
				CColliderMgr* BasicDoorCdList = Dungeon3_BasicDoor->AddComponent<CColliderMgr>(eComponentType::ColliderList);
				//CCollider2D* BasicDoorCd = Dungeon3_BasicDoor->AddComponent<CCollider2D>();

				CCollider2D* BasicDoorCd = new CCollider2D;
				BasicDoorCd->SetSize(Vector2(0.3f, 0.3f));
				BasicDoorCdList->AddCollider(BasicDoorCd);
			}
		}
	}
	CScene::Initialize();
}

void CDesertDungeonScene::Update()
{
	// map �� �̵�

	// 1. map �� �̵��ϴ� ���� (player �� door �� �浹
	//CCollider2D* playerCD = player->GetComponent<CCollider2D>(eComponentType::Collider2D);
	CCollider2D* playerCDforBackground = player->GetComponent<CColliderMgr>(eComponentType::ColliderList)->GetCollider(eCollideType::Background);
	CPlayerMoveScript* playerST = player->GetComponent<CPlayerMoveScript>(eComponentType::Script);
	CTransform* playerTr = player->GetComponent<CTransform>(eComponentType::Transform);
	CCameraMoveScript* mainCameraScript = mainCamera->GetComponent<CCameraMoveScript>(eComponentType::Script);

	Vector2 doorPos = playerCDforBackground->GetColliderData(eLayerType::Portal).pos;
	CTransform* mainCamTr = mainCameraScript->GetOwner()->GetComponent<CTransform>(eComponentType::Transform);
	Vector3 mainCamPos = mainCamTr->GetPosition();
	CState* playerState = player->GetState();


	// map �� �̵�
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

	// �� �̵� �ÿ� �÷��̾��� �̵�
	if (playerCDforBackground->GetColliderData(eLayerType::Portal).id != 0 && mbTranslateMapPos == false)
	{
		mbTranslateMapPos = true;
		playerState->SetBoolStateChange(false);
		
		Vector3 playerPos = playerTr->GetPosition();

		if (doorPos.x > mainCamPos.x) // ����������
		{
			NextMapPos = Vector2(mainCamPos.x + mXPosStandard, mainCamPos.y);
			playerPos.x += 2.5f;
			playerTr->SetPosition(playerPos);
		}
		else if (doorPos.x < mainCamPos.x) // ��������
		{
			NextMapPos = Vector2(mainCamPos.x - mXPosStandard, mainCamPos.y);
			playerPos.x -= 2.5f;
			playerTr->SetPosition(playerPos);
		}
		else if (doorPos.y < mainCamPos.y) // �Ʒ�������
		{
			NextMapPos = Vector2(mainCamPos.x, mainCamPos.y - mYPosStandard);
			playerPos.y -= 1.6f;
			playerTr->SetPosition(playerPos);
		}
		else if (doorPos.y > mainCamPos.y) // ��������
		{
			NextMapPos = Vector2(mainCamPos.x, mainCamPos.y + mYPosStandard);
			playerPos.y += 1.6f;
			playerTr->SetPosition(playerPos);
		}

		// NextMapPos �� �̿��Ͽ� �ش� Map�� ��ȣ�� ������ �� �ֳ�?
		Vector2 mapNum = Vector2(NextMapPos.x / mXPosStandard, NextMapPos.y / mYPosStandard);
		mapNum.x += 3;
		mapNum.y *= -1;
		mapNum.y += 3;
		mapNum;

		UINT CurMapNum = CDungeonMgr::GetInst()->GetMapTexNum(mapNum.x * 10 + mapNum.y);

		vector<CDungeonMgr::sColliderOnMap> ColliderList = CDungeonMgr::GetInst()->GetColliderData(CurMapNum);

		for (int i = 0; i < mTempGameObjects.size(); i++)
		{
			mTempGameObjects[i]->SetState(CGameObject::eObjectState::Dead);
		}
		mTempGameObjects.clear();

		for (int i = 0; i < ColliderList.size(); i++)
		{
			CGameObject* backColliderObj = new CGameObject;
			AddGameObject(eLayerType::Background, backColliderObj, L"BackgroundCollider", Vector3(NextMapPos.x + ColliderList[i].vColliderPos.x, NextMapPos.y + ColliderList[i].vColliderPos.y, 3.000f + 0.0001f * i),
				Vector3(ColliderList[i].vColliderScale.x, ColliderList[i].vColliderScale.y, 0.0f), false, L"Mesh", L"", false);
			CColliderMgr* BackColliderList = backColliderObj->AddComponent<CColliderMgr>(eComponentType::ColliderList);
			BackColliderList->AddCollider(new CCollider2D);
			//backColliderObj->AddComponent<CCollider2D>();

			mTempGameObjects.push_back(backColliderObj);
		}


		// MapColliderBorder �� �̵�
		CLayer& layer = CScene::GetLayer(eLayerType::Background);
		const std::vector<CGameObject*>& backgroundObjects = layer.GetGameObjects();
		for (int i = 0; i < backgroundObjects.size(); i++)
		{
			if (backgroundObjects[i]->GetName() == L"BackgroundBorderUp")
			{
				CTransform* Tr = backgroundObjects[i]->GetComponent<CTransform>(eComponentType::Transform);
				{
					Tr->SetPosition(Vector3(NextMapPos.x, NextMapPos.y + 1.8f, 4.0001f));
				}
			}
			else if (backgroundObjects[i]->GetName() == L"BackgroundBorderDown")
			{
				CTransform* Tr = backgroundObjects[i]->GetComponent<CTransform>(eComponentType::Transform);
				{
					Tr->SetPosition(Vector3(NextMapPos.x, NextMapPos.y - 1.8f, 4.0001f));
				}
			}
			else if (backgroundObjects[i]->GetName() == L"BackgroundBorderRight")
			{
				CTransform* Tr = backgroundObjects[i]->GetComponent<CTransform>(eComponentType::Transform);
				{
					Tr->SetPosition(Vector3(NextMapPos.x + 3.2f, NextMapPos.y, 4.0001f));
				}
			}
			else if (backgroundObjects[i]->GetName() == L"BackgroundBorderLeft")
			{
				CTransform* Tr = backgroundObjects[i]->GetComponent<CTransform>(eComponentType::Transform);
				{
					Tr->SetPosition(Vector3(NextMapPos.x - 3.2f, NextMapPos.y, 4.0001f));
				}
			}
		}

		// Monster ����
		CGameObject* golemSoldier = new CGameObject;
		AddGameObject(eLayerType::Monster, golemSoldier, L"GolemSoldier", Vector3(NextMapPos.x, NextMapPos.y, 4.0004f)
			, Vector3(0.5f, 0.7f, 0.0f), true, L"Mesh", L"", true);
		CGolemSoldierScript* golemSoldierScript = golemSoldier->AddComponent<CGolemSoldierScript>(eComponentType::Script);
		golemSoldierScript->Initialize();
		//golemSoldierScript->SetOwnerOnMonsterScript(golemSoldier);
		//CNaviScript* NaviForGolemSoldier = golemSoldier->AddComponent<CNaviScript>(eComponentType::Script);
		golemSoldierScript->SetNaviData(NextMapPos, CurMapNum, Vector2(0.4f, 0.1f)); // ���⿡�� objScale �� CDforBackground->SetSize() �� ���� ����.
		golemSoldierScript->GetNaviScript()->Initialize();
		golemSoldierScript->GetNaviScript()->SetScene(this);
		golemSoldierScript->GetNaviScript()->SetOwnerScript(golemSoldierScript);
		CColliderMgr* golemSoldierCdList = golemSoldier->AddComponent<CColliderMgr>(eComponentType::ColliderList);

		CCollider2D* golemSoldierCDforBackground = new CCollider2D;
		golemSoldierCDforBackground->SetName(L"golemSoldierCDforBackground");
		golemSoldierCDforBackground->SetCollideType(eCollideType::Background);

		golemSoldierCDforBackground->SetOffset(Vector2(0.0f, -0.2f));
		golemSoldierCdList->AddCollider(golemSoldierCDforBackground);
		golemSoldierCDforBackground->SetSize(Vector2(0.4f, 0.1f));

		CCollider2D* golemSoldierCDforHit = new CCollider2D;
		golemSoldierCDforHit->SetName(L"KatamariCDforHit");
		golemSoldierCDforHit->SetCollideType(eCollideType::Hit);

		golemSoldierCDforHit->SetOffset(Vector2(0.0f, 0.0f));
		golemSoldierCdList->AddCollider(golemSoldierCDforHit);
		golemSoldierCDforHit->SetSize(Vector2(1.0f, 1.0f));

		
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