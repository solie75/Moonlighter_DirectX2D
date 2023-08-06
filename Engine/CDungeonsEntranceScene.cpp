#include "CDungeonsEntranceScene.h"
#include "CPlayer.h"

CDungeonsEntranceScene::CDungeonsEntranceScene()
{
}

CDungeonsEntranceScene::~CDungeonsEntranceScene()
{
}

void CDungeonsEntranceScene::Initialize()
{ // Create GameObejct
	{ // player
		CPlayer* Will = new CPlayer();
		AddGameObject(eLayerType::Player, Will, L"Will", Vector3(3.0f, 0.0f, 1.0002f)
			, Vector3(0.25f, 0.47f, 0.0f), true, L"Mesh", L"mt_atlas_Will_Idle_Down", true);
	}
	{ // camera
		// Main Camera
		CGameObject* mainCamera = new CGameObject();
		AddGameObject(eLayerType::Player, mainCamera, L"MainCamera", Vector3(0.0f, 0.0f, -10.0f),
			Vector3(1.0f, 1.0f, 1.0f), false, L"", L"", false);
		CCamera* mainCamComp = mainCamera->AddComponent<CCamera>();
		mainCamComp->SetCameraType(eCameraType::Main);
		mainCamComp->TurnLayerMask(eLayerType::UI, false);
		//mainCamera->AddComponent<CCameraMoveScript>();

		// UI Camera
		CGameObject* uiCamera = new CGameObject();
		AddGameObject(eLayerType::Player, uiCamera, L"UICamera", Vector3(0.0f, 0.0f, -10.0f),
			Vector3(1.0f, 1.0f, 1.0f), false, L"", L"", false);
		CCamera* uiCamComp = uiCamera->AddComponent<CCamera>();
		uiCamComp->SetCameraType(eCameraType::UI);
		uiCamComp->TurnLayerMask(eLayerType::Player, false);
		uiCamComp->TurnLayerMask(eLayerType::Background, false);
	}
	{ // Background
		CGameObject* DungeonsEntrance_Background = new CGameObject();
		AddGameObject(eLayerType::Background, DungeonsEntrance_Background, L"DungeonsEntrance_Background", Vector3(0.f, 0.0f, 10.0f),
			Vector3(15.56f, 12.80f, 0.0f), true, L"Mesh", L"mt_DungeonsEntrance_Background",false);

		CGameObject* DungeonsEntrance_Background_Cover = new CGameObject(); // 중앙 초록깃발 지우고 애니메이션
		AddGameObject(eLayerType::Background, DungeonsEntrance_Background_Cover, L"DungeonsEntrance_Background_Cover", Vector3(0.09f, -0.435f, 7.0f),
			Vector3(8.68f, 11.5f, 0.0f), true, L"Mesh", L"mt_DungeonsEntrance_Background_Cover",false);
	}
	
	{ // sign
		CGameObject* Village_Sign_Golem = new CGameObject();
		AddGameObject(eLayerType::Background, Village_Sign_Golem, L"Village_Sign_Golem", Vector3(-2.6f, 0.45f, 8.0001f),
			Vector3(0.4f, 0.28f, 0.0f), true, L"Mesh", L"mt_Village_Sign_Golem",false);

		CGameObject* Village_Sign_Desert = new CGameObject();
		AddGameObject(eLayerType::Background, Village_Sign_Desert, L"Village_Sign_Desert", Vector3(-1.68f, 2.17f, 8.0002f),
			Vector3(0.4f, 0.28f, 0.0f), true, L"Mesh", L"mt_Village_Sign_Desert",false);

		CGameObject* Village_Sign_Tesla = new CGameObject();
		AddGameObject(eLayerType::Background, Village_Sign_Tesla, L"Village_Sign_Tesla", Vector3(1.8f, 2.17f, 8.0003f),
			Vector3(0.4f, 0.28f, 0.0f), true, L"Mesh", L"mt_Village_Sign_Tesla",false);

		CGameObject* Village_Sign_Forest = new CGameObject();
		AddGameObject(eLayerType::Background, Village_Sign_Forest, L"Village_Sign_Forest", Vector3(3.28f, 0.45f, 8.0004f),
			Vector3(0.4f, 0.28f, 0.0f), true, L"Mesh", L"mt_Village_Sign_Forest",false);
	}
	{ // LockedPotal
		CGameObject* LockedPortal_1 = new CGameObject();
		AddGameObject(eLayerType::Background, LockedPortal_1, L"LockedPortal_1", Vector3(3.26f, 0.75f, 8.0005f),
			Vector3(0.9f, 0.4f, 0.0f), true, L"Mesh", L"mt_LockedPortal_1",false);

		CGameObject* LockedPortal_2 = new CGameObject();
		AddGameObject(eLayerType::Background, LockedPortal_2, L"LockedPortal_2", Vector3(-1.7f, 2.48f, 8.0006f),
			Vector3(0.9f, 0.4f, 0.0f), true, L"Mesh", L"mt_LockedPortal_2",false);

		CGameObject* LockedPortal_3 = new CGameObject();
		AddGameObject(eLayerType::Background, LockedPortal_3, L"LockedPortal_3", Vector3(1.8f, 2.48f, 8.0007f),
			Vector3(0.9f, 0.4f, 0.0f), true, L"Mesh", L"mt_LockedPortal_3",false);
	}
	{ // door
		CGameObject* DungeonEntrance_5thDoor = new CGameObject();
		AddGameObject(eLayerType::Background, DungeonEntrance_5thDoor, L"DungeonEntrance_5thDoor", Vector3(0.0f, 4.85f, 8.0009f),
			Vector3(1.85f, 1.1f, 0.0f), true, L"Mesh", L"mt_DungeonEntrance_5thDoor",false);

		CGameObject* DungeonEntrance_Fabric = new CGameObject(); // 애니메이션
		AddGameObject(eLayerType::Background, DungeonEntrance_Fabric, L"DungeonEntrance_Fabric", Vector3(0.33f, 4.75f, 8.0008f),
			Vector3(1.4f, 1.3f, 0.0f), true, L"Mesh", L"mt_DungeonEntrance_Fabric",false);

		CGameObject* DungeonEntrance_Wall = new CGameObject();
		AddGameObject(eLayerType::Background, DungeonEntrance_Wall, L"DungeonEntrance_Wall", Vector3(-2.248f, 1.47f, 8.0010f),
			Vector3(0.5f, 0.5f, 0.0f), true, L"Mesh", L"mt_DungeonEntrance_Wall",false);

		CGameObject* DungeonEntrance_Pillar1 = new CGameObject();
		AddGameObject(eLayerType::Background, DungeonEntrance_Pillar1, L"DungeonEntrance_Pillar1", Vector3(-1.165f, 1.47f, 8.0011f),
			Vector3(0.15f, 0.5f, 0.0f), true, L"Mesh", L"mt_DungeonEntrance_Pillar",false);

		CGameObject* DungeonEntrance_Pillar2 = new CGameObject();
		AddGameObject(eLayerType::Background, DungeonEntrance_Pillar2, L"DungeonEntrance_Pillar2", Vector3(1.51f, 1.6f, 8.0012f),
			Vector3(0.15f, 0.4f, 0.0f), true, L"Mesh", L"mt_DungeonEntrance_Pillar",false);
	}
	{ // oilLamp, barrel, box
		CGameObject* DungeonsEntrance_Barrel1 = new CGameObject();
		AddGameObject(eLayerType::Background, DungeonsEntrance_Barrel1, L"DungeonsEntrance_Barrel1", Vector3(-0.85f, -5.1f, 8.0013f),
			Vector3(0.42f, 0.46f, 0.0f), true, L"Mesh", L"mt_Village_Barrel_Right",false);

		CGameObject* DungeonsEntrance_OilLamps_1_1 = new CGameObject(); // 측면
		AddGameObject(eLayerType::Background, DungeonsEntrance_OilLamps_1_1, L"DungeonsEntrance_OilLamps_1_1", Vector3(1.2f, -4.4f, 8.0014f),
			Vector3(0.35f, 0.7f, 0.0f), true, L"Mesh", L"mt_Village_OilLamps_1",false);

		CGameObject* DungeonsEntrance_OilLamps_1_2 = new CGameObject(); // 측면
		AddGameObject(eLayerType::Background, DungeonsEntrance_OilLamps_1_2, L"DungeonsEntrance_OilLamps_1_2", Vector3(1.2f, -2.9f, 8.0015f),
			Vector3(0.35f, 0.7f, 0.0f), true, L"Mesh", L"mt_Village_OilLamps_1",false);

		CGameObject* DungeonsEntrance_OilLamps_2_1 = new CGameObject(); // 정면
		AddGameObject(eLayerType::Background, DungeonsEntrance_OilLamps_2_1, L"DungeonsEntrance_OilLamps_2_1", Vector3(-0.6f, -2.9f, 8.0016f),
			Vector3(0.26f, 0.65f, 0.0f), true, L"Mesh", L"mt_Village_OilLamps_2",false);

		CGameObject* Village_Box1 = new CGameObject(); // will house
		AddGameObject(eLayerType::Background, Village_Box1, L"Village_Box1", Vector3(1.75f, -2.8f, 8.0017f),
			Vector3(0.46f, 0.46f, 0.0f), true, L"Mesh", L"mt_Village_Box_Left",false);

		CGameObject* DungeonsEntrance_Barrel2 = new CGameObject();
		AddGameObject(eLayerType::Background, DungeonsEntrance_Barrel2, L"DungeonsEntrance_Barrel2", Vector3(-2.2f, -3.1f, 8.0018f),
			Vector3(0.42f, 0.46f, 0.0f), true, L"Mesh", L"mt_Village_Barrel_Right",false);

		CGameObject* Village_Box2 = new CGameObject(); // will house
		AddGameObject(eLayerType::Background, Village_Box2, L"Village_Box2", Vector3(-2.5f, -2.6f, 8.0019f),
			Vector3(0.46f, 0.46f, 0.0f), true, L"Mesh", L"mt_Village_Box_Left",false);

		CGameObject* Village_Sign_DungeonUp = new CGameObject();
		AddGameObject(eLayerType::Background, Village_Sign_DungeonUp, L"Village_Sign_DungeonUp", Vector3(-0.93f, -4.2f, 8.0020f),
			Vector3(0.4f, 0.28f, 0.0f), true, L"Mesh", L"mt_Village_Sign_DungeonUp",false);
	}
	{ // UI
		CGameObject* Health_UI_Circle = new CGameObject();
		AddGameObject(eLayerType::UI, Health_UI_Circle, L"Health_UI_Circle", Vector3(-3.175f, 1.9f, -0.12f),
			Vector3(0.3f, 0.3f, 0.0f), true, L"Mesh", L"mt_UI_Base_Circle",false);

		CGameObject* HealthBar_Base = new CGameObject();
		AddGameObject(eLayerType::UI, HealthBar_Base, L"HealthBar_Base", Vector3(-2.58f, 1.9f, -2.002f),
			Vector3(1.0f, 0.28f, 0.0f), true, L"Mesh", L"mt_HealthBar_Base",false);

		CGameObject* Cash_Base_Circle = new CGameObject();
		AddGameObject(eLayerType::UI, Cash_Base_Circle, L"Cash_Base_Circle", Vector3(-3.67f, 1.82f, -2.003f),
			Vector3(0.5f, 0.5f, 0.0f), true, L"Mesh", L"mt_UI_Base_Circle",false);

		CGameObject* Gold4 = new CGameObject();
		AddGameObject(eLayerType::UI, Gold4, L"Gold4", Vector3(-3.67f, 1.82f, -2.0031f),
			Vector3(0.3f, 0.3f, 0.0f), true, L"Mesh", L"mt_Gold4",false);

		CGameObject* Health_Icon = new CGameObject();
		AddGameObject(eLayerType::UI, Health_Icon, L"Health_Icon", Vector3(-3.18f, 1.9f, -2.004f),
			Vector3(0.21f, 0.21f, 0.0f), true, L"Mesh", L"mt_Health_Icon",false);

		CGameObject* Weapon_Base_Circle1 = new CGameObject();
		AddGameObject(eLayerType::UI, Weapon_Base_Circle1, L"Weapon_Base_Circle1", Vector3(3.5f, 1.56f, -2.008f),
			Vector3(0.485f, 0.485f, 0.0f), true, L"Mesh", L"mt_UI_Base_Circle",false);

		CGameObject* Weapon_Base_Circle2 = new CGameObject();
		AddGameObject(eLayerType::UI, Weapon_Base_Circle2, L"Weapon_Base_Circle2", Vector3(3.6f, 1.56f, -2.009f),
			Vector3(0.485f, 0.485f, 0.0f), true, L"Mesh", L"mt_UI_Base_Circle",false);

		CGameObject* Inventory_Base_Circle = new CGameObject();
		AddGameObject(eLayerType::UI, Inventory_Base_Circle, L"Inventory_Base_Circle", Vector3(3.6f, 0.96f, -2.010f),
			Vector3(0.485f, 0.485f, 0.0f), true, L"Mesh", L"mt_UI_Base_Circle",false);

		CGameObject* HUD_Set1 = new CGameObject();
		AddGameObject(eLayerType::UI, HUD_Set1, L"HUD_Set1", Vector3(3.23f, 1.6f, -2.005f),
			Vector3(0.18f, 0.18f, 0.0f), true, L"Mesh", L"mt_HUD_Set1",false);

		CGameObject* HUD_Set2 = new CGameObject();
		AddGameObject(eLayerType::UI, HUD_Set2, L"HUD_Set2", Vector3(3.13f, 1.6f, -2.006f),
			Vector3(0.18f, 0.18f, 0.0f), true, L"Mesh", L"mt_HUD_Set2",false);

		CGameObject* Bag = new CGameObject();
		AddGameObject(eLayerType::UI, Bag, L"Bag", Vector3(3.61f, 0.96f, -2.011f),
			Vector3(0.4f, 0.4f, 0.0f), true, L"Mesh", L"mt_Bag",false);

		CGameObject* Button_E = new CGameObject();
		AddGameObject(eLayerType::UI, Button_E, L"Button_E", Vector3(3.7f, 2.0f, -2.012f),
			Vector3(0.35f, 0.35f, 0.0f), true, L"Mesh", L"mt_Button_E",false);

		CGameObject* Button_Space = new CGameObject();
		AddGameObject(eLayerType::UI, Button_Space, L"Button_Space", Vector3(3.35f, 2.0f, -2.013f),
			Vector3(0.35f, 0.35f, 0.0f), true, L"Mesh", L"mt_Button_Space",false);

		CGameObject* Button_Z = new CGameObject();
		AddGameObject(eLayerType::UI, Button_Z, L"Button_Z", Vector3(2.85f, 1.6f, -2.014f),
			Vector3(0.35f, 0.35f, 0.0f), true, L"Mesh", L"mt_Button_Z",false);

		CGameObject* Button_K = new CGameObject();
		AddGameObject(eLayerType::UI, Button_K, L"Button_K", Vector3(3.36f, 1.39f, -2.015f),
			Vector3(0.35f, 0.35f, 0.0f), true, L"Mesh", L"mt_Button_K",false);

		CGameObject* Button_J = new CGameObject();
		AddGameObject(eLayerType::UI, Button_J, L"Button_J", Vector3(3.57f, 1.285f, -2.016f),
			Vector3(0.35f, 0.35f, 0.0f), true, L"Mesh", L"mt_Button_J",false);

		CGameObject* Button_I = new CGameObject();
		AddGameObject(eLayerType::UI, Button_I, L"Button_I", Vector3(3.4f, 0.73f, -2.017f),
			Vector3(0.35f, 0.35f, 0.0f), true, L"Mesh", L"mt_Button_I",false);

		CGameObject* HUD_MiniRoll = new CGameObject();
		AddGameObject(eLayerType::UI, HUD_MiniRoll, L"HUD_MiniRoll", Vector3(3.17f, 1.9f, -2.018f),
			Vector3(0.2f, 0.2f, 0.0f), true, L"Mesh", L"mt_HUD_MiniRoll",false);

		CGameObject* Item_Potion = new CGameObject();
		AddGameObject(eLayerType::UI, Item_Potion, L"Item_Potion", Vector3(3.8f, 1.94f, -2.019f),
			Vector3(0.4f, 0.4f, 0.0f), true, L"Mesh", L"mt_Item_Potion",false);

		CGameObject* Item_Coin = new CGameObject();
		AddGameObject(eLayerType::UI, Item_Coin, L"Item_Coin", Vector3(-3.84f, 1.48f, -2.020f),
			Vector3(0.12f, 0.12f, 0.0f), true, L"Mesh", L"mt_Item_Coin",false);
	}
}

void CDungeonsEntranceScene::Update()
{
	CScene::Update();
}

void CDungeonsEntranceScene::LateUpdate()
{
	CScene::LateUpdate();
}

void CDungeonsEntranceScene::Render()
{
	CScene::Render();
}
