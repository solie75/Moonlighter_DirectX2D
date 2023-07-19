#include "CVillageScene.h"
#include "CCameraMoveScript.h"
#include "CPlayerMoveScript.h"

CVillageScene::CVillageScene()
{
}

CVillageScene::~CVillageScene()
{
}

void CVillageScene::Initialize()
{
	// Create GameObejct
	{
		CGameObject* Will = new CGameObject();
		AddGameObject(eLayerType::Background, Will, L"Will", Vector3(0.0f, 0.0f, -0.1f),
			Vector3(0.25f, 0.47f, 0.0f), true, L"Mesh", L"mt_Will");
		Will->AddComponent<CPlayerMoveScript>();
	}
	{ // Background
		CGameObject* Village_Background = new CGameObject();
		AddGameObject(eLayerType::Background, Village_Background, L"Village_Background", Vector3(0.f, 0.0f, 10.0f),
			Vector3(15.56f, 12.80f, 0.0f), true, L"Mesh", L"mt_Village_Background");
	}
	{	// House
		CGameObject* WillsHome = new CGameObject();
		AddGameObject(eLayerType::Background, WillsHome, L"WillsHome", Vector3(1.9f, 4.6f, 9.001f),
			Vector3(3.0f, 3.0f, 0.0f), true, L"Mesh", L"mt_WillsHome");

		CGameObject* Village_House_01 = new CGameObject();
		AddGameObject(eLayerType::Background, Village_House_01, L"Village_House_01", Vector3(5.9f, -2.3f, 9.002f),
			Vector3(2.8f, 2.8f, 0.0f), true, L"Mesh", L"mt_Village_House_01");

		CGameObject* Village_House_02 = new CGameObject();
		AddGameObject(eLayerType::Background, Village_House_02, L"Village_House_02", Vector3(-1.15f, 4.15f, 9.003f),
			Vector3(2.0f, 2.2f, 0.0f), true, L"Mesh", L"mt_Village_House_02");



		CGameObject* Village_House_06 = new CGameObject();
		AddGameObject(eLayerType::Background, Village_House_06, L"Village_House_06", Vector3(2.1f, -2.7f, 9.004f),
			Vector3(2.0f, 2.0f, 0.0f), true, L"Mesh", L"mt_Village_House_06");

		CGameObject* Village_House_05 = new CGameObject();
		AddGameObject(eLayerType::Background, Village_House_05, L"Village_House_05", Vector3(-2.45f, -3.15f, 9.005f),
			Vector3(2.55f, 2.0f, 0.0f), true, L"Mesh", L"mt_Village_House_05");

		CGameObject* Village_Awning = new CGameObject();
		AddGameObject(eLayerType::Background, Village_Awning, L"Village_Awning", Vector3(-2.42f, 3.9f, 9.006f),
			Vector3(0.635f, 1.3f, 0.0f), true, L"Mesh", L"mt_Village_Awning");

		CGameObject* Village_Board = new CGameObject();
		AddGameObject(eLayerType::Background, Village_Board, L"Village_Board", Vector3(0.97f, 0.435f, 9.007f),
			Vector3(1.15f, 0.7f, 0.0f), true, L"Mesh", L"mt_Village_Board");
	}
	{ // blacksmith


		CGameObject* Village_Blacksmith_House_old = new CGameObject();
		AddGameObject(eLayerType::Background, Village_Blacksmith_House_old, L"Village_Blacksmith_House_old", Vector3(6.68f, 0.245f, 9.0084f),
			Vector3(1.85f, 1.0f, 0.0f), true, L"Mesh", L"mt_Village_Blacksmith_House_old");

		CGameObject* Village_Blacksmith_Roof_old = new CGameObject();
		AddGameObject(eLayerType::Background, Village_Blacksmith_Roof_old, L"Village_Blacksmith_Roof_old", Vector3(6.53f, 1.223f, 9.0081f),
			Vector3(1.61f, 1.95f, 0.0f), true, L"Mesh", L"mt_Village_Blacksmith_Roof_old");

		CGameObject* Village_Blacksmith_Stand1_old = new CGameObject();
		AddGameObject(eLayerType::Background, Village_Blacksmith_Stand1_old, L"Village_Blacksmith_Stand1_old", Vector3(5.09f, 0.53f, 9.0082f),
			Vector3(1.42f, 0.5f, 0.0f), true, L"Mesh", L"mt_Village_Blacksmith_Stand1_old");

		CGameObject* Village_Blacksmith_Stand2_old = new CGameObject();
		AddGameObject(eLayerType::Background, Village_Blacksmith_Stand2_old, L"Village_Blacksmith_Stand2_old", Vector3(4.55f, 1.0735f, 9.008f),
			Vector3(0.35f, 0.7f, 0.0f), true, L"Mesh", L"mt_Village_Blacksmith_Stand2_old");

		CGameObject* Village_Blacksmith_Fence = new CGameObject();
		AddGameObject(eLayerType::Background, Village_Blacksmith_Fence, L"Village_Blacksmith_Fence", Vector3(5.045f, 1.515f, 9.0083f),
			Vector3(1.5f, 0.75f, 0.0f), true, L"Mesh", L"mt_Village_Blacksmith_Fence");

	}
	{ // witch

		CGameObject* Village_Witch_House_old = new CGameObject();
		AddGameObject(eLayerType::Background, Village_Witch_House_old, L"Village_Witch_House_old", Vector3(-5.53f, -2.6f, 9.0093f),
			Vector3(1.25f, 1.77f, 0.0f), true, L"Mesh", L"mt_Village_Witch_House_old");

		CGameObject* Village_Witch_Roof_old = new CGameObject();
		AddGameObject(eLayerType::Background, Village_Witch_Roof_old, L"Village_Witch_Roof_old", Vector3(-5.53f, -1.7f, 9.009f),
			Vector3(1.6f, 3.0f, 0.0f), true, L"Mesh", L"mt_Village_Witch_Roof_old");

		CGameObject* Village_Witch_Table_old = new CGameObject();
		AddGameObject(eLayerType::Background, Village_Witch_Table_old, L"Village_Witch_Table_old", Vector3(-5.5f, -3.7f, 9.0092f),
			Vector3(1.8f, 1.23f, 0.0f), true, L"Mesh", L"mt_Village_Witch_Table_old");

		CGameObject* Village_Witch_Storage_old = new CGameObject();
		AddGameObject(eLayerType::Background, Village_Witch_Storage_old, L"Village_Witch_Storage_old", Vector3(-6.85f, -3.8f, 9.0091f),
			Vector3(1.0f, 1.15f, 0.0f), true, L"Mesh", L"mt_Village_Witch_Storage_old");

	}
	{ // rival
		CGameObject* Village_Rival_House_old = new CGameObject();
		AddGameObject(eLayerType::Background, Village_Rival_House_old, L"Village_Rival_House_old", Vector3(-6.05f, 3.75f, 9.0102f),
			Vector3(3.3f, 2.0f, 0.0f), true, L"Mesh", L"mt_Village_Rival_House_old");

		CGameObject* Village_Rival_Roof_old = new CGameObject();
		AddGameObject(eLayerType::Background, Village_Rival_Roof_old, L"Village_Rival_Roof_old", Vector3(-5.215f, 4.167f, 9.010f),
			Vector3(2.05f, 1.7f, 0.0f), true, L"Mesh", L"mt_Village_Rival_Roof_old");

		CGameObject* Village_Rival_Fountain_old = new CGameObject();
		AddGameObject(eLayerType::Background, Village_Rival_Fountain_old, L"Village_Rival_Fountain_old", Vector3(-5.32f, 1.62f, 9.0101f),
			Vector3(0.5f, 0.58f, 0.0f), true, L"Mesh", L"mt_Village_Rival_Fountain_old");

		CGameObject* Village_Rival_Desk_old = new CGameObject();
		AddGameObject(eLayerType::Background, Village_Rival_Desk_old, L"Village_Rival_Desk_old", Vector3(-5.32f, 2.3f, 9.0103f),
			Vector3(1.6f, 0.50f, 0.0f), true, L"Mesh", L"mt_Village_Rival_Desk_old");
	}
	{ // Object
		{ // Oil Lamp
			CGameObject* Village_OilLamps_1_1 = new CGameObject(); // black smith
			AddGameObject(eLayerType::Background, Village_OilLamps_1_1, L"Village_OilLamps_1_1", Vector3(4.2f, 1.57f, 8.0011f),
				Vector3(0.3f, 0.7f, 0.0f), true, L"Mesh", L"mt_Village_OilLamps_1");

			CGameObject* Village_OilLamps_1_2 = new CGameObject(); // Rival right
			AddGameObject(eLayerType::Background, Village_OilLamps_1_2, L"Village_OilLamps_1_2", Vector3(-1.9f, 1.86f, 8.0012f),
				Vector3(0.3f, 0.7f, 0.0f), true, L"Mesh", L"mt_Village_OilLamps_1");

			CGameObject* Village_OilLamps_1_3 = new CGameObject();
			AddGameObject(eLayerType::Background, Village_OilLamps_1_3, L"Village_OilLamps_1_3", Vector3(-1.8f, -0.8f, 8.0013f),
				Vector3(0.3f, 0.7f, 0.0f), true, L"Mesh", L"mt_Village_OilLamps_1");

			CGameObject* Village_OilLamps_2_1 = new CGameObject(); // will home
			AddGameObject(eLayerType::Background, Village_OilLamps_2_1, L"Village_OilLamps_2_1", Vector3(1.75f, 3.25f, 8.0018f), // Á¤¸é
				Vector3(0.22f, 0.65f, 0.0f), true, L"Mesh", L"mt_Village_OilLamps_2");

			CGameObject* Village_OilLamps_2_2 = new CGameObject(); // right pass
			AddGameObject(eLayerType::Background, Village_OilLamps_2_2, L"Village_OilLamps_2_2", Vector3(6.75f, 3.05f, 8.0019f),
				Vector3(0.22f, 0.65f, 0.0f), true, L"Mesh", L"mt_Village_OilLamps_2");

			CGameObject* Village_OilLamps_2_3 = new CGameObject(); // rival desk
			AddGameObject(eLayerType::Background, Village_OilLamps_2_3, L"Village_OilLamps_2_3", Vector3(-4.26f, 2.2f, 8.0020f),
				Vector3(0.22f, 0.65f, 0.0f), true, L"Mesh", L"mt_Village_OilLamps_2");

			CGameObject* Village_OilLamps_2_4 = new CGameObject(); // house 6
			AddGameObject(eLayerType::Background, Village_OilLamps_2_4, L"Village_OilLamps_2_4", Vector3(3.8f, -3.2f, 8.0021f),
				Vector3(0.22f, 0.65f, 0.0f), true, L"Mesh", L"mt_Village_OilLamps_2");

			CGameObject* Village_OilLamps_2_5 = new CGameObject(); // witch
			AddGameObject(eLayerType::Background, Village_OilLamps_2_5, L"Village_OilLamps_2_5", Vector3(-6.1f, -4.4f, 8.0022f),
				Vector3(0.22f, 0.65f, 0.0f), true, L"Mesh", L"mt_Village_OilLamps_2");
		}
		{ // Sign

			CGameObject* Village_Sign_DungeonRight = new CGameObject();
			AddGameObject(eLayerType::Background, Village_Sign_DungeonRight, L"Village_Sign_DungeonRight", Vector3(5.7f, 2.9f, 8.0023f),
				Vector3(0.4f, 0.28f, 0.0f), true, L"Mesh", L"mt_Village_Sign_DungeonRight");

			CGameObject* Village_Sign_BlacksmithRight = new CGameObject();
			AddGameObject(eLayerType::Background, Village_Sign_BlacksmithRight, L"Village_Sign_BlacksmithRight", Vector3(4.5f, 1.95f, 8.0024f),
				Vector3(0.4f, 0.28f, 0.0f), true, L"Mesh", L"mt_Village_Sign_BlacksmithRight");

			CGameObject* Will_Shop_Sign = new CGameObject();
			AddGameObject(eLayerType::Background, Will_Shop_Sign, L"Will_Shop_Sign", Vector3(2.93f, 2.9f, 8.0025f),
				Vector3(0.43f, 0.28f, 0.0f), true, L"Mesh", L"mt_Will_Shop_Sign");

			CGameObject* Village_Sign_WitchLeft = new CGameObject();
			AddGameObject(eLayerType::Background, Village_Sign_WitchLeft, L"Village_Sign_WitchLeft", Vector3(-1.15f, -4.13f, 8.0026f),
				Vector3(0.4f, 0.28f, 0.0f), true, L"Mesh", L"mt_Village_Sign_WitchLeft");

			CGameObject* Village_Sign_WitchDown = new CGameObject();
			AddGameObject(eLayerType::Background, Village_Sign_WitchDown, L"Village_Sign_WitchDown", Vector3(-2.93f, 5.0f, 8.0027f),
				Vector3(0.4f, 0.28f, 0.0f), true, L"Mesh", L"mt_Village_Sign_WitchDown");

			CGameObject* Village_Sign_DungeonUp = new CGameObject();
			AddGameObject(eLayerType::Background, Village_Sign_DungeonUp, L"Village_Sign_DungeonUp", Vector3(-2.93f, 3.0f, 8.0028f),
				Vector3(0.4f, 0.28f, 0.0f), true, L"Mesh", L"mt_Village_Sign_DungeonUp");
		}
		{ // Box, Barrel
			CGameObject* Village_Box1 = new CGameObject(); // will house
			AddGameObject(eLayerType::Background, Village_Box1, L"Village_Box1", Vector3(0.57f, 3.15f, 8.0029f),
				Vector3(0.46f, 0.46f, 0.0f), true, L"Mesh", L"mt_Village_Box_Left");

			CGameObject* Village_Barrel1 = new CGameObject(); // will house
			AddGameObject(eLayerType::Background, Village_Barrel1, L"Village_Barrel1", Vector3(0.85f, 3.2f, 8.0032f),
				Vector3(0.46f, 0.46f, 0.0f), true, L"Mesh", L"mt_Village_Barrel_Left");

			CGameObject* Village_Barrel2 = new CGameObject();
			AddGameObject(eLayerType::Background, Village_Barrel2, L"Village_Barrel2", Vector3(1.1f, 3.13f, 8.0031f),
				Vector3(0.4f, 0.4f, 0.0f), true, L"Mesh", L"mt_Village_Barrel_Right");

			CGameObject* Village_Barrel3 = new CGameObject();
			AddGameObject(eLayerType::Background, Village_Barrel3, L"Village_Barrel3", Vector3(0.98f, 3.0f, 8.0030f),
				Vector3(0.46f, 0.46f, 0.0f), true, L"Mesh", L"mt_Village_Barrel_Left");

			CGameObject* Village_Box2 = new CGameObject(); // witch
			AddGameObject(eLayerType::Background, Village_Box2, L"Village_Box2", Vector3(-7.5f, -4.6f, 8.0033f),
				Vector3(0.46f, 0.46f, 0.0f), true, L"Mesh", L"mt_Village_Box_Left");

			CGameObject* Village_Box3 = new CGameObject(); // witch
			AddGameObject(eLayerType::Background, Village_Box3, L"Village_Box3", Vector3(-7.05f, -5.0f, 8.0035f),
				Vector3(0.46f, 0.46f, 0.0f), true, L"Mesh", L"mt_Village_Box_Left");

			CGameObject* Village_Box4 = new CGameObject();
			AddGameObject(eLayerType::Background, Village_Box4, L"Village_Box4", Vector3(-7.05f, -5.36f, 8.0034f),
				Vector3(0.46f, 0.46f, 0.0f), true, L"Mesh", L"mt_Village_Box_Left");

			CGameObject* Village_Box5 = new CGameObject();
			AddGameObject(eLayerType::Background, Village_Box5, L"Village_Box5", Vector3(-7.45f, -5.28f, 8.0036f),
				Vector3(0.4f, 0.4f, 0.0f), true, L"Mesh", L"mt_Village_Box_Right");

			CGameObject* Village_Box6 = new CGameObject();
			AddGameObject(eLayerType::Background, Village_Box6, L"Village_Box6", Vector3(-5.5f, 0.2f, 8.0037f),
				Vector3(0.37f, 0.4f, 0.0f), true, L"Mesh", L"mt_Village_Box_Right");

			CGameObject* Village_Box7 = new CGameObject();
			AddGameObject(eLayerType::Background, Village_Box7, L"Village_Box7", Vector3(-6.0f, -0.1f, 8.0038f),
				Vector3(0.4f, 0.4f, 0.0f), true, L"Mesh", L"mt_Village_Box_Left");

			CGameObject* Village_Box8 = new CGameObject();
			AddGameObject(eLayerType::Background, Village_Box8, L"Village_Box8", Vector3(-4.9f, -0.2f, 8.0039f),
				Vector3(0.4f, 0.4f, 0.0f), true, L"Mesh", L"mt_Village_Box_Left");

			CGameObject* Village_Barrel4 = new CGameObject();
			AddGameObject(eLayerType::Background, Village_Barrel4, L"Village_Barrel4", Vector3(-2.85f, 1.67f, 8.0040f),
				Vector3(0.46f, 0.46f, 0.0f), true, L"Mesh", L"mt_Village_Barrel_Left");

			CGameObject* Village_Box9 = new CGameObject();
			AddGameObject(eLayerType::Background, Village_Box9, L"Village_Box9", Vector3(5.97f, -2.73f, 8.0041f),
				Vector3(0.4f, 0.4f, 0.0f), true, L"Mesh", L"mt_Village_Box_Left");

			CGameObject* Village_Box10 = new CGameObject();
			AddGameObject(eLayerType::Background, Village_Box10, L"Village_Box10", Vector3(3.11f, -2.9f, 9.0041f),
				Vector3(0.4f, 0.4f, 0.0f), true, L"Mesh", L"mt_Village_Box_Left");

			CGameObject* Village_Box11 = new CGameObject();
			AddGameObject(eLayerType::Background, Village_Box11, L"Village_Box11", Vector3(1.115f, -2.9f, 9.0042f),
				Vector3(0.4f, 0.4f, 0.0f), true, L"Mesh", L"mt_Village_Box_Left");

			CGameObject* Village_Box12 = new CGameObject();
			AddGameObject(eLayerType::Background, Village_Box12, L"Village_Box12", Vector3(1.1f, -3.6f, 8.0044f),
				Vector3(0.4f, 0.4f, 0.0f), true, L"Mesh", L"mt_Village_Box_Left");
		}
		{ // Bench
			CGameObject* Village_Bench1 = new CGameObject();
			AddGameObject(eLayerType::Background, Village_Bench1, L"Village_Bench1", Vector3(-2.4f, 1.25f, 8.0045f),
				Vector3(0.7f, 0.7f, 0.0f), true, L"Mesh", L"mt_Village_Bench_1");

			CGameObject* Village_Bench2 = new CGameObject();
			AddGameObject(eLayerType::Background, Village_Bench2, L"Village_Bench2", Vector3(-1.25f, 1.65f, 8.0046f),
				Vector3(0.7f, 0.35f, 0.0f), true, L"Mesh", L"mt_Village_Bench_3");

			CGameObject* Village_Bench3 = new CGameObject();
			AddGameObject(eLayerType::Background, Village_Bench3, L"Village_Bench3", Vector3(-1.25f, -1.2f, 8.0047f),
				Vector3(0.7f, 0.35f, 0.0f), true, L"Mesh", L"mt_Village_Bench_3");

			CGameObject* Village_Bench4 = new CGameObject();
			AddGameObject(eLayerType::Background, Village_Bench4, L"Village_Bench4", Vector3(-2.4f, -0.7f, 8.0048f),
				Vector3(0.7f, 0.7f, 0.0f), true, L"Mesh", L"mt_Village_Bench_2");

		}
		{ // Stone, Flowerpot, Bush, Cutted Tree
			CGameObject* Village_BigStone = new CGameObject();
			AddGameObject(eLayerType::Background, Village_BigStone, L"Village_BigStone", Vector3(-7.1f, 0.5f, 8.0049f),
				Vector3(0.7f, 0.7f, 0.0f), true, L"Mesh", L"mt_Village_BigStone");


			CGameObject* Village_Flowerpots_1 = new CGameObject(); // rival house
			AddGameObject(eLayerType::Background, Village_Flowerpots_1, L"Village_Flowerpots_1", Vector3(-4.245f, 1.7f, 8.0050f),
				Vector3(0.3f, 0.3f, 0.0f), true, L"Mesh", L"mt_Village_Flowerpots_1");

			CGameObject* Village_Flowerpots_2 = new CGameObject();
			AddGameObject(eLayerType::Background, Village_Flowerpots_2, L"Village_Flowerpots_2", Vector3(-4.245f, 1.05f, 8.0051f),
				Vector3(0.3f, 0.3f, 0.0f), true, L"Mesh", L"mt_Village_Flowerpots_2");

			CGameObject* Village_Flowerpots_3 = new CGameObject();
			AddGameObject(eLayerType::Background, Village_Flowerpots_3, L"Village_Flowerpots_3", Vector3(-4.55f, 3.05f, 8.0052f),
				Vector3(0.3f, 0.3f, 0.0f), true, L"Mesh", L"mt_Village_Flowerpots_3");

			CGameObject* Village_CuttedTree_1 = new CGameObject(); // left bottom
			AddGameObject(eLayerType::Background, Village_CuttedTree_1, L"Village_CuttedTree_1", Vector3(7.45f, -4.15f, 8.0053f),
				Vector3(0.4f, 0.4f, 0.0f), true, L"Mesh", L"mt_Village_CuttedTree_01");

			CGameObject* Village_CuttedTree_2 = new CGameObject();
			AddGameObject(eLayerType::Background, Village_CuttedTree_2, L"Village_CuttedTree_2", Vector3(6.1f, -5.05f, 8.0054f),
				Vector3(0.4f, 0.4f, 0.0f), true, L"Mesh", L"mt_Village_CuttedTree_01");

			CGameObject* Village_CuttedTree_3 = new CGameObject();
			AddGameObject(eLayerType::Background, Village_CuttedTree_3, L"Village_CuttedTree_3", Vector3(6.7f, -5.4f, 8.0055f),
				Vector3(0.4f, 0.4f, 0.0f), true, L"Mesh", L"mt_Village_CuttedTree_02");

				CGameObject* Village_CuttedTree_4 = new CGameObject();
			AddGameObject(eLayerType::Background, Village_CuttedTree_4, L"Village_CuttedTree_4", Vector3(-2.93f, 5.5f, 8.0060f),
				Vector3(0.4f, 0.4f, 0.0f), true, L"Mesh", L"mt_Village_CuttedTree_02");

			CGameObject* Village_Bush_1 = new CGameObject();
			AddGameObject(eLayerType::Background, Village_Bush_1, L"Village_Bush_1", Vector3(4.8f, -5.15f, 8.0056f),
				Vector3(0.4f, 0.4f, 0.0f), true, L"Mesh", L"mt_Village_Bush");

			CGameObject* Village_Bush_2 = new CGameObject();
			AddGameObject(eLayerType::Background, Village_Bush_2, L"Village_Bush_2", Vector3(5.9f, -6.0f, 8.0057f),
				Vector3(0.4f, 0.4f, 0.0f), true, L"Mesh", L"mt_Village_Bush");

			CGameObject* Village_Bush_3 = new CGameObject();
			AddGameObject(eLayerType::Background, Village_Bush_3, L"Village_Bush_3", Vector3(3.1f, -5.5f, 8.0058f),
				Vector3(0.4f, 0.4f, 0.0f), true, L"Mesh", L"mt_Village_Bush");

			CGameObject* Village_Bush_4 = new CGameObject();
			AddGameObject(eLayerType::Background, Village_Bush_4, L"Village_Bush_4", Vector3(-6.5f, 0.7f, 8.0059f),
				Vector3(0.4f, 0.4f, 0.0f), true, L"Mesh", L"mt_Village_Bush");
		}
		{ // orange Tree Animation

		}
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
		AddGameObject(eLayerType::UI, Inventory_Base_Circle, L"Inventory_Base_Circle", Vector3(3.6f, 0.96f, -2.010f),
			Vector3(0.485f, 0.485f, 0.0f), true, L"Mesh", L"mt_UI_Base_Circle");

		CGameObject* HUD_Set1 = new CGameObject();
		AddGameObject(eLayerType::UI, HUD_Set1, L"HUD_Set1", Vector3(3.23f, 1.6f, -2.005f),
			Vector3(0.18f, 0.18f, 0.0f), true, L"Mesh", L"mt_HUD_Set1");

		CGameObject* HUD_Set2 = new CGameObject();
		AddGameObject(eLayerType::UI, HUD_Set2, L"HUD_Set2", Vector3(3.13f, 1.6f, -2.006f),
			Vector3(0.18f, 0.18f, 0.0f), true, L"Mesh", L"mt_HUD_Set2");

		CGameObject* Bag = new CGameObject();
		AddGameObject(eLayerType::UI, Bag, L"Bag", Vector3(3.61f, 0.96f, -2.011f),
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
		/*CGameObject* YesNo_Circle = new CGameObject();
		AddGameObject(eLayerType::UI, YesNo_Circle, L"YesNo_Circle", Vector3(3.6f, 1.56f, -2.007f),
			Vector3(0.18f, 0.18f, 0.0f), true, L"Mesh", L"mt_YesNo_Circle");*/
	}

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

void CVillageScene::Update()
{
	CScene::Update();
}

void CVillageScene::LateUpdate()
{
	CScene::LateUpdate();
}

void CVillageScene::Render()
{
	CScene::Render();
}
