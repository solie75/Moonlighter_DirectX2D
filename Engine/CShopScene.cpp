#include "CShopScene.h"
#include "CCameraMoveScript.h"
#include "CPlayerMoveScript.h"

CShopScene::CShopScene()
{
}

CShopScene::~CShopScene()
{
}

void CShopScene::Initialize()
{
	// Create GameObejct
	{ // will
		CGameObject* Will = new CGameObject();
		AddGameObject(eLayerType::Background, Will, L"Will", Vector3(0.0f, 0.0f, -0.1f),
			Vector3(0.25f, 0.47f, 0.0f), true, L"Mesh", L"mt_Will");
		Will->AddComponent<CPlayerMoveScript>();
	}
	{ // Background
		CGameObject* Shop_Background = new CGameObject();
		AddGameObject(eLayerType::Background, Shop_Background, L"Shop_Background", Vector3(0.f, 0.0f, 10.0f),
			Vector3(4.35f, 5.37f, 0.0f), true, L"Mesh", L"mt_Shop_Background");
	}
	{ // Object
		CGameObject* bed_carpet = new CGameObject();
		AddGameObject(eLayerType::Background, bed_carpet, L"bed_carpet", Vector3(0.621f, 1.45f, 8.0009f),
			Vector3(1.5f, 1.5f, 0.0f), true, L"Mesh", L"mt_bed_carpet");

		CGameObject* will_bed = new CGameObject();
		AddGameObject(eLayerType::Background, will_bed, L"will_bed", Vector3(0.637f, 1.5f, 8.0002f),
			Vector3(0.66f, 0.47f, 0.0f), true, L"Mesh", L"mt_will_bed");

		CGameObject* room_stove = new CGameObject();
		AddGameObject(eLayerType::Background, room_stove, L"room_stove", Vector3(0.9f, 0.95f, 8.0001f),
			Vector3(0.45f, 0.57f, 0.0f), true, L"Mesh", L"mt_room_stove");

		CGameObject* room_table = new CGameObject();
		AddGameObject(eLayerType::Background, room_table, L"room_table", Vector3(-0.83f, 1.411f, 8.0004f),
			Vector3(0.3f, 0.82f, 0.0f), true, L"Mesh", L"mt_room_table");

		CGameObject* room_stool = new CGameObject();
		AddGameObject(eLayerType::Background, room_stool, L"room_stool", Vector3(-0.65f, 1.411f, 8.0005f),
			Vector3(0.2f, 0.2f, 0.0f), true, L"Mesh", L"mt_room_stool");

		CGameObject* room_mirror_frame = new CGameObject();
		AddGameObject(eLayerType::Background, room_mirror_frame, L"room_mirror_frame", Vector3(-0.27f, 0.63f, 8.0007f),
			Vector3(0.2f, 0.25f, 0.0f), true, L"Mesh", L"mt_room_mirror_frame");

		CGameObject* room_mirror = new CGameObject(); // ���� �ſ� ��� �߰� �� ��
		AddGameObject(eLayerType::Background, room_mirror, L"room_mirror", Vector3(-0.27f, 0.63f, 8.0006f),
			Vector3(0.2f, 0.25f, 0.0f), true, L"Mesh", L"mt_room_mirror");

		CGameObject* bed_chest = new CGameObject();
		AddGameObject(eLayerType::Background, bed_chest, L"bed_chest", Vector3(0.2f, 1.45f, 8.0008f),
			Vector3(0.7f, 0.7f, 0.0f), true, L"Mesh", L"mt_bed_chest");

		CGameObject* shop_chest = new CGameObject();
		AddGameObject(eLayerType::Background, shop_chest, L"shop_chest", Vector3(0.35f, 2.02f, 8.0010f),
			Vector3(0.28f, 0.28f, 0.0f), true, L"Mesh", L"mt_shop_chest");

		CGameObject* shop_stove = new CGameObject();
		AddGameObject(eLayerType::Background, shop_stove, L"shop_stove", Vector3(-0.95f, 0.35f, 8.0011f),
			Vector3(0.85f, 0.85f, 0.0f), true, L"Mesh", L"mt_shop_stove");

		CGameObject* shop_cauldron = new CGameObject();
		AddGameObject(eLayerType::Background, shop_cauldron, L"shop_cauldron", Vector3(-0.98f, 0.05f, 8.0012f),
			Vector3(0.15f, 0.17f, 0.0f), true, L"Mesh", L"mt_shop_cauldron");

		CGameObject* shop_main_table = new CGameObject();
		AddGameObject(eLayerType::Background, shop_main_table, L"shop_main_table", Vector3(0.73f, -0.7f, 8.0021f),
			Vector3(1.6f, 0.48f, 0.0f), true, L"Mesh", L"mt_shop_main_table");

		CGameObject* entrance_carpet = new CGameObject();
		AddGameObject(eLayerType::Background, entrance_carpet, L"entrance_carpet", Vector3(0.02f, -1.915f, 8.0014f),
			Vector3(0.6f, 0.3f, 0.0f), true, L"Mesh", L"mt_entrance_carpet");

		CGameObject* shop_table_1 = new CGameObject();
		AddGameObject(eLayerType::Background, shop_table_1, L"shop_table_1", Vector3(-1.1f, -1.3f, 8.0015f),
			Vector3(0.322f, 0.37f, 0.0f), true, L"Mesh", L"mt_shop_table");

		CGameObject* shop_table_2 = new CGameObject();
		AddGameObject(eLayerType::Background, shop_table_2, L"shop_table_2", Vector3(-0.8f, -1.3f, 8.0016f),
			Vector3(0.322f, 0.37f, 0.0f), true, L"Mesh", L"mt_shop_table");

		CGameObject* shop_table_3 = new CGameObject();
		AddGameObject(eLayerType::Background, shop_table_3, L"shop_table_3", Vector3(-1.1f, -1.025f, 8.0017f),
			Vector3(0.322f, 0.37f, 0.0f), true, L"Mesh", L"mt_shop_table");

		CGameObject* shop_table_4 = new CGameObject();
		AddGameObject(eLayerType::Background, shop_table_4, L"shop_table_4", Vector3(-0.8f, -1.025f, 8.0018f),
			Vector3(0.322f, 0.37f, 0.0f), true, L"Mesh", L"mt_shop_table");

		CGameObject* shop_table_5 = new CGameObject();
		AddGameObject(eLayerType::Background, shop_table_5, L"shop_table_5", Vector3(-0.8f, -0.75f, 8.0019f),
			Vector3(0.322f, 0.37f, 0.0f), true, L"Mesh", L"mt_shop_table");

		CGameObject* shop_table_6 = new CGameObject();
		AddGameObject(eLayerType::Background, shop_table_6, L"shop_table_6", Vector3(-1.1f, -0.75f, 8.0020f),
			Vector3(0.322f, 0.37f, 0.0f), true, L"Mesh", L"mt_shop_table");

		CGameObject* cash_register = new CGameObject();
		AddGameObject(eLayerType::Background, cash_register, L"cash_register", Vector3(0.925f, -0.623f, 8.0013f),
			Vector3(0.37f, 0.3f, 0.0f), true, L"Mesh", L"mt_cash_register");

		CGameObject* shop_door = new CGameObject();
		AddGameObject(eLayerType::Background, shop_door, L"shop_door", Vector3(0.0155f, -2.167f, 8.0022f),
			Vector3(0.295f, 0.23f, 0.0f), true, L"Mesh", L"mt_shop_door");

		CGameObject* shop_shoes = new CGameObject();
		AddGameObject(eLayerType::Background, shop_shoes, L"shop_shoes", Vector3(0.61f, 0.95f, 8.0023f),
			Vector3(0.1f, 0.065f, 0.0f), true, L"Mesh", L"mt_shop_shoes");
	}


	{ // UI
		CGameObject* Health_UI_Circle = new CGameObject();
		AddGameObject(eLayerType::UI, Health_UI_Circle, L"Health_UI_Circle", Vector3(-3.175f, 1.9f, -0.12f),
			Vector3(0.3f, 0.3f, 0.0f), true, L"Mesh", L"mt_UI_Base_Circle");

		CGameObject* HealthBar_Base = new CGameObject();
		AddGameObject(eLayerType::UI, HealthBar_Base, L"HealthBar_Base", Vector3(-2.58f, 1.9f, -2.002f),
			Vector3(1.0f, 0.28f, 0.0f), true, L"Mesh", L"mt_HealthBar_Base");

		CGameObject* Cash_Base_Circle = new CGameObject();
		AddGameObject(eLayerType::UI, Cash_Base_Circle, L"Cash_Base_Circle", Vector3(-3.67f, 1.82f, -2.003f),
			Vector3(0.5f, 0.5f, 0.0f), true, L"Mesh", L"mt_UI_Base_Circle");

		CGameObject* Gold4 = new CGameObject();
		AddGameObject(eLayerType::UI, Gold4, L"Gold4", Vector3(-3.67f, 1.82f, -2.0031f),
			Vector3(0.3f, 0.3f, 0.0f), true, L"Mesh", L"mt_Gold4");

		CGameObject* Health_Icon = new CGameObject();
		AddGameObject(eLayerType::UI, Health_Icon, L"Health_Icon", Vector3(-3.18f, 1.9f, -2.004f),
			Vector3(0.21f, 0.21f, 0.0f), true, L"Mesh", L"mt_Health_Icon");

		CGameObject* Weapon_Base_Circle1 = new CGameObject();
		AddGameObject(eLayerType::UI, Weapon_Base_Circle1, L"Weapon_Base_Circle1", Vector3(3.5f, 1.56f, -2.008f),
			Vector3(0.485f, 0.485f, 0.0f), true, L"Mesh", L"mt_UI_Base_Circle");

		CGameObject* Weapon_Base_Circle2 = new CGameObject();
		AddGameObject(eLayerType::UI, Weapon_Base_Circle2, L"Weapon_Base_Circle2", Vector3(3.6f, 1.56f, -2.009f),
			Vector3(0.485f, 0.485f, 0.0f), true, L"Mesh", L"mt_UI_Base_Circle");

		CGameObject* Inventory_Base_Circle = new CGameObject();
		AddGameObject(eLayerType::UI, Inventory_Base_Circle, L"Inventory_Base_Circle", Vector3(3.6f, 0.93f, -2.010f),
			Vector3(0.485f, 0.485f, 0.0f), true, L"Mesh", L"mt_UI_Base_Circle");

		CGameObject* HUD_Set1 = new CGameObject();
		AddGameObject(eLayerType::UI, HUD_Set1, L"HUD_Set1", Vector3(3.23f, 1.6f, -2.005f),
			Vector3(0.18f, 0.18f, 0.0f), true, L"Mesh", L"mt_HUD_Set1");

		CGameObject* HUD_Set2 = new CGameObject();
		AddGameObject(eLayerType::UI, HUD_Set2, L"HUD_Set2", Vector3(3.13f, 1.6f, -2.006f),
			Vector3(0.18f, 0.18f, 0.0f), true, L"Mesh", L"mt_HUD_Set2");

		CGameObject* Bag = new CGameObject();
		AddGameObject(eLayerType::UI, Bag, L"Bag", Vector3(3.61f, 0.93f, -2.011f),
			Vector3(0.4f, 0.4f, 0.0f), true, L"Mesh", L"mt_Bag");

		CGameObject* Button_E = new CGameObject();
		AddGameObject(eLayerType::UI, Button_E, L"Button_E", Vector3(3.7f, 2.0f, -2.012f),
			Vector3(0.35f, 0.35f, 0.0f), true, L"Mesh", L"mt_Button_E");

		CGameObject* Button_Space = new CGameObject();
		AddGameObject(eLayerType::UI, Button_Space, L"Button_Space", Vector3(3.35f, 2.0f, -2.013f),
			Vector3(0.35f, 0.35f, 0.0f), true, L"Mesh", L"mt_Button_Space");

		CGameObject* Button_Z = new CGameObject();
		AddGameObject(eLayerType::UI, Button_Z, L"Button_Z", Vector3(2.85f, 1.6f, -2.014f),
			Vector3(0.35f, 0.35f, 0.0f), true, L"Mesh", L"mt_Button_Z");

		CGameObject* Button_K = new CGameObject();
		AddGameObject(eLayerType::UI, Button_K, L"Button_K", Vector3(3.36f, 1.39f, -2.015f),
			Vector3(0.35f, 0.35f, 0.0f), true, L"Mesh", L"mt_Button_K");

		CGameObject* Button_J = new CGameObject();
		AddGameObject(eLayerType::UI, Button_J, L"Button_J", Vector3(3.57f, 1.285f, -2.016f),
			Vector3(0.35f, 0.35f, 0.0f), true, L"Mesh", L"mt_Button_J");

		CGameObject* Button_I = new CGameObject();
		AddGameObject(eLayerType::UI, Button_I, L"Button_I", Vector3(3.4f, 0.73f, -2.017f),
			Vector3(0.35f, 0.35f, 0.0f), true, L"Mesh", L"mt_Button_I");

		CGameObject* HUD_MiniRoll = new CGameObject();
		AddGameObject(eLayerType::UI, HUD_MiniRoll, L"HUD_MiniRoll", Vector3(3.17f, 1.9f, -2.018f),
			Vector3(0.2f, 0.2f, 0.0f), true, L"Mesh", L"mt_HUD_MiniRoll");

		CGameObject* Item_Potion = new CGameObject();
		AddGameObject(eLayerType::UI, Item_Potion, L"Item_Potion", Vector3(3.8f, 1.94f, -2.019f),
			Vector3(0.4f, 0.4f, 0.0f), true, L"Mesh", L"mt_Item_Potion");

		CGameObject* Item_Coin = new CGameObject();
		AddGameObject(eLayerType::UI, Item_Coin, L"Item_Coin", Vector3(-3.84f, 1.48f, -2.020f),
			Vector3(0.12f, 0.12f, 0.0f), true, L"Mesh", L"mt_Item_Coin");
	}

	{ // camera
		// Main Camera
		CGameObject* mainCamera = new CGameObject();
		AddGameObject(eLayerType::Player, mainCamera, L"MainCamera", Vector3(0.0f, 0.0f, -10.0f),
			Vector3(1.0f, 1.0f, 1.0f), false, L"", L"");
		CCamera* mainCamComp = mainCamera->AddComponent<CCamera>();
		mainCamComp->TurnLayerMask(eLayerType::UI, false);
		mainCamera->AddComponent<CCameraMoveScript>();

		// UI Camera
		CGameObject* uiCamera = new CGameObject();
		AddGameObject(eLayerType::Player, uiCamera, L"UICamera", Vector3(0.0f, 0.0f, -10.0f),
			Vector3(1.0f, 1.0f, 1.0f), false, L"", L"");
		CCamera* uiCamComp = uiCamera->AddComponent<CCamera>();
		uiCamComp->TurnLayerMask(eLayerType::Player, false);
		uiCamComp->TurnLayerMask(eLayerType::Background, false);
	}
}

void CShopScene::Update()
{
	CScene::Update();
}

void CShopScene::LateUpdate()
{
	CScene::LateUpdate();
}

void CShopScene::Render()
{
	CScene::Render();
}
