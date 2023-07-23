#include "CRenderMgr.h"
#include "CTexture.h"
#include "CPlayScene.h"

CRenderMgr::CRenderMgr()
	: mCB{}
	, cameras{}
{
	mGraphicContext = CDevice::GetInst()->GetContext();
}

CRenderMgr::~CRenderMgr()
{
}

void CRenderMgr::Init()
{
	// Set Sampler
	SetUpState();

	// Create Mesh
	std::shared_ptr<CMesh> mesh = std::make_shared<CMesh>();
	mesh->BindBuffer();
	CResourceMgr::GetInst()->Insert(L"Mesh", mesh);

	// Create Shader
	std::shared_ptr<CShader> shader = std::make_shared<CShader>();
	shader->CreateShader(eShaderStage::VS, L"VS.hlsl", "main");
	shader->CreateShader(eShaderStage::PS, L"PS.hlsl", "main");
	shader->CreateInputLayout();

	CResourceMgr::GetInst()->Insert(L"Shader", shader);

	std::shared_ptr<CShader> gridShader = std::make_shared<CShader>();
	gridShader->CreateShader(eShaderStage::VS, L"GridVS.hlsl", "main");
	gridShader->CreateShader(eShaderStage::PS, L"GridPS.hlsl", "main");
	gridShader->CreateInputLayout();
	CResourceMgr::GetInst()->Insert(L"GridShader", gridShader);

	std::shared_ptr<CShader> aniShader = std::make_shared<CShader>();
	aniShader->CreateShader(eShaderStage::VS, L"AnimationVS.hlsl", "main");
	aniShader->CreateShader(eShaderStage::PS, L"AnimationPS.hlsl", "main");
	aniShader->CreateInputLayout();
	CResourceMgr::GetInst()->Insert(L"AnimationShader", aniShader);

	// Create Grid Material
	std::shared_ptr<CMaterial> mt_Grid = std::make_shared<CMaterial>();
	mt_Grid->SetShader(gridShader);
	mt_Grid->SetTexture(nullptr);
	mt_Grid->SetRenderMode(eRenderingMode::Opaque);
	mt_Grid->SetName(L"mt_Grid");
	CResourceMgr::Insert(L"mt_Grid", mt_Grid);

	// Load Texture and Mateiral
	{ // Test
		LoadTexture(L"Link", L"..\\Resource\\Texture\\Link.png");
		LoadMaterial(shader, L"Link", eRenderingMode::Opaque);

		LoadTexture(L"Smile", L"..\\Resource\\Texture\\Smile.png");
		LoadMaterial(shader, L"Smile", eRenderingMode::CutOut);
	}
	{ // will
		LoadTexture(L"Will", L"..\\Resource\\Texture\\Will.png");
		LoadMaterial(shader, L"Will", eRenderingMode::Transparent);
	}
	{ // UI
		LoadTexture(L"UI_Base_Circle", L"..\\Resource\\Texture\\UI\\UI_Base_Circle.png");
		LoadMaterial(shader, L"UI_Base_Circle", eRenderingMode::CutOut);

		LoadTexture(L"HealthBar_Circle", L"..\\Resource\\Texture\\UI\\HealthBar_Circle.png");
		LoadMaterial(shader, L"HealthBar_Circle", eRenderingMode::CutOut);

		LoadTexture(L"HealthBar_Base", L"..\\Resource\\Texture\\UI\\HealthBar_Base.png");
		LoadMaterial(shader, L"HealthBar_Base", eRenderingMode::CutOut);

		LoadTexture(L"Gold4", L"..\\Resource\\Texture\\UI\\Gold4.png");
		LoadMaterial(shader, L"Gold4", eRenderingMode::CutOut);

		LoadTexture(L"Health_Icon", L"..\\Resource\\Texture\\UI\\Health_Icon.png");
		LoadMaterial(shader, L"Health_Icon", eRenderingMode::CutOut);

		LoadTexture(L"HUD_Set1", L"..\\Resource\\Texture\\UI\\HUD_Set1.png");
		LoadMaterial(shader, L"HUD_Set1", eRenderingMode::CutOut);

		LoadTexture(L"HUD_Set2", L"..\\Resource\\Texture\\UI\\HUD_Set2.png");
		LoadMaterial(shader, L"HUD_Set2", eRenderingMode::CutOut);

		LoadTexture(L"YesNo_Circle", L"..\\Resource\\Texture\\UI\\YesNo_Circle.png");
		LoadMaterial(shader, L"YesNo_Circle", eRenderingMode::CutOut);

		LoadTexture(L"Bag", L"..\\Resource\\Texture\\UI\\Bag.png");
		LoadMaterial(shader, L"Bag", eRenderingMode::CutOut);

		LoadTexture(L"Button_E", L"..\\Resource\\Texture\\UI\\Button_E.png");
		LoadMaterial(shader, L"Button_E", eRenderingMode::CutOut);

		LoadTexture(L"Button_I", L"..\\Resource\\Texture\\UI\\Button_I.png");
		LoadMaterial(shader, L"Button_I", eRenderingMode::CutOut);

		LoadTexture(L"Button_J", L"..\\Resource\\Texture\\UI\\Button_J.png");
		LoadMaterial(shader, L"Button_J", eRenderingMode::CutOut);

		LoadTexture(L"Button_K", L"..\\Resource\\Texture\\UI\\Button_K.png");
		LoadMaterial(shader, L"Button_K", eRenderingMode::CutOut);

		LoadTexture(L"Button_Space", L"..\\Resource\\Texture\\UI\\Button_Space.png");
		LoadMaterial(shader, L"Button_Space", eRenderingMode::CutOut);

		LoadTexture(L"Button_Z", L"..\\Resource\\Texture\\UI\\Button_Z.png");
		LoadMaterial(shader, L"Button_Z", eRenderingMode::CutOut);

		LoadTexture(L"HUD_MiniRoll", L"..\\Resource\\Texture\\UI\\HUD_MiniRoll.png");
		LoadMaterial(shader, L"HUD_MiniRoll", eRenderingMode::CutOut);

	}
	{ // Start Menu
		LoadTexture(L"Start_Intro_Door_Left", L"..\\Resource\\Texture\\Start_Menu\\Start_Intro_Door_Left.png");
		LoadMaterial(shader, L"Start_Intro_Door_Left", eRenderingMode::CutOut);

		LoadTexture(L"Start_Intro_Door_Right", L"..\\Resource\\Texture\\Start_Menu\\Start_Intro_Door_Right.png");
		LoadMaterial(shader, L"Start_Intro_Door_Right", eRenderingMode::CutOut);

		LoadTexture(L"GameLogo", L"..\\Resource\\Texture\\Start_Menu\\GameLogo.png");
		LoadMaterial(shader, L"GameLogo", eRenderingMode::CutOut);

		{ // Animation sample
			LoadTexture(L"Main_menu_1_1", L"..\\Resource\\Texture\\Start_Menu\\Main_menu_1_1.png");
			LoadMaterial(shader, L"Main_menu_1_1", eRenderingMode::CutOut);

			LoadTexture(L"Main_menu_2_1", L"..\\Resource\\Texture\\Start_Menu\\Main_menu_2_1.png");
			LoadMaterial(shader, L"Main_menu_2_1", eRenderingMode::CutOut);
		}
	}
	{ // Village
		LoadTexture(L"Village_Background", L"..\\Resource\\Texture\\Village_Background.png");
		LoadMaterial(shader, L"Village_Background", eRenderingMode::Opaque);

		LoadTexture(L"WillsHome", L"..\\Resource\\Texture\\Village_house\\WillsHome.png");
		LoadMaterial(shader, L"WillsHome", eRenderingMode::CutOut);

		LoadTexture(L"Village_House_01", L"..\\Resource\\Texture\\Village_house\\Village_House_01.png");
		LoadMaterial(shader, L"Village_House_01", eRenderingMode::CutOut);

		LoadTexture(L"Village_Blacksmith_House_old", L"..\\Resource\\Texture\\Village_house\\Village_Blacksmith_House_old.png");
		LoadMaterial(shader, L"Village_Blacksmith_House_old", eRenderingMode::CutOut);

		LoadTexture(L"Village_Blacksmith_Roof_old", L"..\\Resource\\Texture\\Village_house\\Village_Blacksmith_Roof_old.png");
		LoadMaterial(shader, L"Village_Blacksmith_Roof_old", eRenderingMode::CutOut);

		LoadTexture(L"Village_Blacksmith_Stand1_old", L"..\\Resource\\Texture\\Village_house\\Village_Blacksmith_Stand1_old.png");
		LoadMaterial(shader, L"Village_Blacksmith_Stand1_old", eRenderingMode::CutOut);

		LoadTexture(L"Village_Blacksmith_Stand2_old", L"..\\Resource\\Texture\\Village_house\\Village_Blacksmith_Stand2_old.png");
		LoadMaterial(shader, L"Village_Blacksmith_Stand2_old", eRenderingMode::CutOut);

		LoadTexture(L"Village_Blacksmith_Fence", L"..\\Resource\\Texture\\Village_house\\Village_Blacksmith_Fence.png");
		LoadMaterial(shader, L"Village_Blacksmith_Fence", eRenderingMode::CutOut);

		LoadTexture(L"Village_House_06", L"..\\Resource\\Texture\\Village_house\\Village_House_06.png");
		LoadMaterial(shader, L"Village_House_06", eRenderingMode::CutOut);

		LoadTexture(L"Village_House_05", L"..\\Resource\\Texture\\Village_house\\Village_House_05.png");
		LoadMaterial(shader, L"Village_House_05", eRenderingMode::CutOut);

		LoadTexture(L"Village_House_02", L"..\\Resource\\Texture\\Village_house\\Village_House_02.png");
		LoadMaterial(shader, L"Village_House_02", eRenderingMode::CutOut);

		LoadTexture(L"Village_Awning", L"..\\Resource\\Texture\\Village_house\\Village_Awning.png");
		LoadMaterial(shader, L"Village_Awning", eRenderingMode::CutOut);

		LoadTexture(L"Village_Board", L"..\\Resource\\Texture\\Village_house\\Village_Board.png");
		LoadMaterial(shader, L"Village_Board", eRenderingMode::CutOut);

		LoadTexture(L"Village_Fence_Column", L"..\\Resource\\Texture\\Village_house\\Village_Fence_Column.png");
		LoadMaterial(shader, L"Village_Fence_Column", eRenderingMode::CutOut);

		LoadTexture(L"Village_Fence_Row", L"..\\Resource\\Texture\\Village_house\\Village_Fence_Row.png");
		LoadMaterial(shader, L"Village_Fence_Row", eRenderingMode::CutOut);

		LoadTexture(L"Village_Witch_House_old", L"..\\Resource\\Texture\\Village_house\\Village_Witch_House_old.png");
		LoadMaterial(shader, L"Village_Witch_House_old", eRenderingMode::CutOut);

		LoadTexture(L"Village_Witch_Roof_old", L"..\\Resource\\Texture\\Village_house\\Village_Witch_Roof_old.png");
		LoadMaterial(shader, L"Village_Witch_Roof_old", eRenderingMode::CutOut);

		LoadTexture(L"Village_Witch_Table_old", L"..\\Resource\\Texture\\Village_house\\Village_Witch_Table_old.png");
		LoadMaterial(shader, L"Village_Witch_Table_old", eRenderingMode::CutOut);

		LoadTexture(L"Village_Witch_Storage_old", L"..\\Resource\\Texture\\Village_house\\Village_Witch_Storage_old.png");
		LoadMaterial(shader, L"Village_Witch_Storage_old", eRenderingMode::CutOut);

		LoadTexture(L"Village_Rival_House_old", L"..\\Resource\\Texture\\Village_house\\Village_Rival_House_old.png");
		LoadMaterial(shader, L"Village_Rival_House_old", eRenderingMode::CutOut);

		LoadTexture(L"Village_Rival_Roof_old", L"..\\Resource\\Texture\\Village_house\\Village_Rival_Roof_old.png");
		LoadMaterial(shader, L"Village_Rival_Roof_old", eRenderingMode::CutOut);

		LoadTexture(L"Village_Rival_Fountain_old", L"..\\Resource\\Texture\\Village_house\\Village_Rival_Fountain_old.png");
		LoadMaterial(shader, L"Village_Rival_Fountain_old", eRenderingMode::CutOut);

		LoadTexture(L"Village_Rival_Desk_old", L"..\\Resource\\Texture\\Village_house\\Village_Rival_Desk_old.png");
		LoadMaterial(shader, L"Village_Rival_Desk_old", eRenderingMode::CutOut);

		LoadTexture(L"Village_OilLamps_1", L"..\\Resource\\Texture\\Village_house\\Village_OilLamps_1.png"); // 좌측
		LoadMaterial(shader, L"Village_OilLamps_1", eRenderingMode::CutOut);

		LoadTexture(L"Village_OilLamps_2", L"..\\Resource\\Texture\\Village_house\\Village_OilLamps_2.png"); // 정면
		LoadMaterial(shader, L"Village_OilLamps_2", eRenderingMode::CutOut);

		LoadTexture(L"Village_Sign_Desert", L"..\\Resource\\Texture\\Village_Sign\\Village_Sign_Desert.png"); 
		LoadMaterial(shader, L"Village_Sign_Desert", eRenderingMode::CutOut);

		LoadTexture(L"Village_Sign_Golem", L"..\\Resource\\Texture\\Village_Sign\\Village_Sign_Golem.png");
		LoadMaterial(shader, L"Village_Sign_Golem", eRenderingMode::CutOut);

		LoadTexture(L"Village_Sign_Forest", L"..\\Resource\\Texture\\Village_Sign\\Village_Sign_Forest.png");
		LoadMaterial(shader, L"Village_Sign_Forest", eRenderingMode::CutOut);

		LoadTexture(L"Village_Sign_Tesla", L"..\\Resource\\Texture\\Village_Sign\\Village_Sign_Tesla.png");
		LoadMaterial(shader, L"Village_Sign_Tesla", eRenderingMode::CutOut);

		LoadTexture(L"Village_Sign_DungeonRight", L"..\\Resource\\Texture\\Village_Sign\\Village_Sign_DungeonRight.png");
		LoadMaterial(shader, L"Village_Sign_DungeonRight", eRenderingMode::CutOut);

		LoadTexture(L"Village_Sign_DungeonUp", L"..\\Resource\\Texture\\Village_Sign\\Village_Sign_DungeonUp.png");
		LoadMaterial(shader, L"Village_Sign_DungeonUp", eRenderingMode::CutOut);

		LoadTexture(L"Village_Sign_EnemyLeft", L"..\\Resource\\Texture\\Village_Sign\\Village_Sign_EnemyLeft.png");
		LoadMaterial(shader, L"Village_Sign_EnemyLeft", eRenderingMode::CutOut);

		LoadTexture(L"Village_Sign_BlacksmithRight", L"..\\Resource\\Texture\\Village_Sign\\Village_Sign_BlacksmithRight.png");
		LoadMaterial(shader, L"Village_Sign_BlacksmithRight", eRenderingMode::CutOut);

		LoadTexture(L"Village_Sign_WitchDown", L"..\\Resource\\Texture\\Village_Sign\\Village_Sign_WitchDown.png");
		LoadMaterial(shader, L"Village_Sign_WitchDown", eRenderingMode::CutOut);

		LoadTexture(L"Village_Sign_WitchLeft", L"..\\Resource\\Texture\\Village_Sign\\Village_Sign_WitchLeft.png");
		LoadMaterial(shader, L"Village_Sign_WitchLeft", eRenderingMode::CutOut);

		LoadTexture(L"Will_Shop_Sign", L"..\\Resource\\Texture\\Village_Sign\\Will_Shop_Sign.png");
		LoadMaterial(shader, L"Will_Shop_Sign", eRenderingMode::CutOut);

		LoadTexture(L"Will_Shop_Sign", L"..\\Resource\\Texture\\Village_Sign\\Will_Shop_Sign.png");
		LoadMaterial(shader, L"Will_Shop_Sign", eRenderingMode::CutOut);

		LoadTexture(L"Village_Barrel_Right", L"..\\Resource\\Texture\\Village_house\\Village_Barrel_Right.png");
		LoadMaterial(shader, L"Village_Barrel_Right", eRenderingMode::CutOut);

		LoadTexture(L"Village_Barrel_Left", L"..\\Resource\\Texture\\Village_house\\Village_Barrel_Left.png");
		LoadMaterial(shader, L"Village_Barrel_Left", eRenderingMode::CutOut);

		LoadTexture(L"Village_Box_Right", L"..\\Resource\\Texture\\Village_house\\Village_Box_Right.png");
		LoadMaterial(shader, L"Village_Box_Right", eRenderingMode::CutOut);

		LoadTexture(L"Village_Box_Left", L"..\\Resource\\Texture\\Village_house\\Village_Box_Left.png");
		LoadMaterial(shader, L"Village_Box_Left", eRenderingMode::CutOut);

		LoadTexture(L"Village_Bench_1", L"..\\Resource\\Texture\\Village_house\\Village_Bench_1.png");
		LoadMaterial(shader, L"Village_Bench_1", eRenderingMode::CutOut);

		LoadTexture(L"Village_Bench_2", L"..\\Resource\\Texture\\Village_house\\Village_Bench_2.png");
		LoadMaterial(shader, L"Village_Bench_2", eRenderingMode::CutOut);

		LoadTexture(L"Village_Bench_3", L"..\\Resource\\Texture\\Village_house\\Village_Bench_3.png");
		LoadMaterial(shader, L"Village_Bench_3", eRenderingMode::CutOut);

		LoadTexture(L"Village_Bench_4", L"..\\Resource\\Texture\\Village_house\\Village_Bench_4.png");
		LoadMaterial(shader, L"Village_Bench_4", eRenderingMode::CutOut);

		LoadTexture(L"Village_BigStone", L"..\\Resource\\Texture\\Village_house\\Village_BigStone.png");
		LoadMaterial(shader, L"Village_BigStone", eRenderingMode::CutOut);

		LoadTexture(L"Village_Flowerpots_1", L"..\\Resource\\Texture\\Village_house\\Village_Flowerpots_1.png");
		LoadMaterial(shader, L"Village_Flowerpots_1", eRenderingMode::CutOut);

		LoadTexture(L"Village_Flowerpots_2", L"..\\Resource\\Texture\\Village_house\\Village_Flowerpots_2.png");
		LoadMaterial(shader, L"Village_Flowerpots_2", eRenderingMode::CutOut);

		LoadTexture(L"Village_Flowerpots_3", L"..\\Resource\\Texture\\Village_house\\Village_Flowerpots_3.png");
		LoadMaterial(shader, L"Village_Flowerpots_3", eRenderingMode::CutOut);

		LoadTexture(L"Village_CuttedTree_01", L"..\\Resource\\Texture\\Village_house\\Village_CuttedTree_01.png");
		LoadMaterial(shader, L"Village_CuttedTree_01", eRenderingMode::CutOut);

		LoadTexture(L"Village_CuttedTree_02", L"..\\Resource\\Texture\\Village_house\\Village_CuttedTree_02.png");
		LoadMaterial(shader, L"Village_CuttedTree_02", eRenderingMode::CutOut);

		LoadTexture(L"Village_Bush", L"..\\Resource\\Texture\\Village_house\\Village_Bush.png");
		LoadMaterial(shader, L"Village_Bush", eRenderingMode::CutOut);
	}
	{ // shop
		LoadTexture(L"Shop_Background", L"..\\Resource\\Texture\\Shop\\Shop_Background.png");
		LoadMaterial(shader, L"Shop_Background", eRenderingMode::Opaque);

		LoadTexture(L"bed_carpet", L"..\\Resource\\Texture\\Shop\\bed_carpet.png");
		LoadMaterial(shader, L"bed_carpet", eRenderingMode::CutOut);

		LoadTexture(L"will_bed", L"..\\Resource\\Texture\\Shop\\will_bed.png");
		LoadMaterial(shader, L"will_bed", eRenderingMode::CutOut);

		LoadTexture(L"room_stove", L"..\\Resource\\Texture\\Shop\\room_stove.png");
		LoadMaterial(shader, L"room_stove", eRenderingMode::CutOut);

		LoadTexture(L"room_table", L"..\\Resource\\Texture\\Shop\\room_table.png");
		LoadMaterial(shader, L"room_table", eRenderingMode::CutOut);

		LoadTexture(L"room_stool", L"..\\Resource\\Texture\\Shop\\room_stool.png");
		LoadMaterial(shader, L"room_stool", eRenderingMode::CutOut);

		LoadTexture(L"room_mirror_frame", L"..\\Resource\\Texture\\Shop\\room_mirror_frame.png");
		LoadMaterial(shader, L"room_mirror_frame", eRenderingMode::CutOut);

		LoadTexture(L"room_mirror", L"..\\Resource\\Texture\\Shop\\room_mirror.png");
		LoadMaterial(shader, L"room_mirror", eRenderingMode::CutOut);

		LoadTexture(L"bed_chest", L"..\\Resource\\Texture\\Shop\\bed_chest.png");
		LoadMaterial(shader, L"bed_chest", eRenderingMode::CutOut);

		LoadTexture(L"shop_chest", L"..\\Resource\\Texture\\Shop\\shop_chest.png");
		LoadMaterial(shader, L"shop_chest", eRenderingMode::CutOut);

		LoadTexture(L"shop_stove", L"..\\Resource\\Texture\\Shop\\shop_stove.png");
		LoadMaterial(shader, L"shop_stove", eRenderingMode::CutOut);

		LoadTexture(L"shop_cauldron", L"..\\Resource\\Texture\\Shop\\shop_cauldron.png");
		LoadMaterial(shader, L"shop_cauldron", eRenderingMode::CutOut);

		LoadTexture(L"shop_main_table", L"..\\Resource\\Texture\\Shop\\shop_main_table.png");
		LoadMaterial(shader, L"shop_main_table", eRenderingMode::CutOut);

		LoadTexture(L"entrance_carpet", L"..\\Resource\\Texture\\Shop\\entrance_carpet.png");
		LoadMaterial(shader, L"entrance_carpet", eRenderingMode::CutOut);

		LoadTexture(L"shop_table", L"..\\Resource\\Texture\\Shop\\shop_table.png");
		LoadMaterial(shader, L"shop_table", eRenderingMode::CutOut);

		LoadTexture(L"cash_register", L"..\\Resource\\Texture\\Shop\\cash_register.png");
		LoadMaterial(shader, L"cash_register", eRenderingMode::CutOut);

		LoadTexture(L"shop_door", L"..\\Resource\\Texture\\Shop\\shop_door.png");
		LoadMaterial(shader, L"shop_door", eRenderingMode::CutOut);

		LoadTexture(L"shop_shoes", L"..\\Resource\\Texture\\Shop\\shop_shoes.png");
		LoadMaterial(shader, L"shop_shoes", eRenderingMode::CutOut);
	}
	{ // DungeonsEntrance
		LoadTexture(L"DungeonsEntrance_Background", L"..\\Resource\\Texture\\DungeonsEntrance\\DungeonsEntrance_Background.png");
		LoadMaterial(shader, L"DungeonsEntrance_Background", eRenderingMode::CutOut);

		LoadTexture(L"DungeonsEntrance_Background_Cover", L"..\\Resource\\Texture\\DungeonsEntrance\\DungeonsEntrance_Background_Cover.png");
		LoadMaterial(shader, L"DungeonsEntrance_Background_Cover", eRenderingMode::CutOut);

		LoadTexture(L"LockedPortal_1", L"..\\Resource\\Texture\\DungeonsEntrance\\LockedPortal_1.png");
		LoadMaterial(shader, L"LockedPortal_1", eRenderingMode::CutOut);

		LoadTexture(L"LockedPortal_2", L"..\\Resource\\Texture\\DungeonsEntrance\\LockedPortal_2.png");
		LoadMaterial(shader, L"LockedPortal_2", eRenderingMode::CutOut);

		LoadTexture(L"LockedPortal_3", L"..\\Resource\\Texture\\DungeonsEntrance\\LockedPortal_3.png");
		LoadMaterial(shader, L"LockedPortal_3", eRenderingMode::CutOut);

		LoadTexture(L"DungeonEntrance_5thDoor", L"..\\Resource\\Texture\\DungeonsEntrance\\DungeonEntrance_5thDoor.png");
		LoadMaterial(shader, L"DungeonEntrance_5thDoor", eRenderingMode::CutOut);

		LoadTexture(L"DungeonEntrance_Fabric", L"..\\Resource\\Texture\\DungeonsEntrance\\DungeonEntrance_Fabric.png");
		LoadMaterial(shader, L"DungeonEntrance_Fabric", eRenderingMode::CutOut);

		LoadTexture(L"DungeonEntrance_Pillar", L"..\\Resource\\Texture\\DungeonsEntrance\\DungeonEntrance_Pillar.png");
		LoadMaterial(shader, L"DungeonEntrance_Pillar", eRenderingMode::CutOut);

		LoadTexture(L"DungeonEntrance_Wall", L"..\\Resource\\Texture\\DungeonsEntrance\\DungeonEntrance_Wall.png");
		LoadMaterial(shader, L"DungeonEntrance_Wall", eRenderingMode::CutOut);
	}
	{ // item
		LoadTexture(L"Item_Potion", L"..\\Resource\\Texture\\Item\\Item_Potion.png");
		LoadMaterial(shader, L"Item_Potion", eRenderingMode::CutOut);

		LoadTexture(L"Item_Coin", L"..\\Resource\\Texture\\Item\\Item_Coin.png");
		LoadMaterial(shader, L"Item_Coin", eRenderingMode::CutOut);
	}
	{ // Atlas
		LoadTexture(L"linkSprites", L"..\\Resource\\Texture\\linkSprites.png");
		LoadMaterial(aniShader, L"linkSprites", eRenderingMode::CutOut);

		 ( L"Will_Idle_Down", 10);
		LoadMaterial(aniShader, L"atlas_Will_Idle_Down", eRenderingMode::CutOut);

		CreateAtlas(L"Will_Idle_Left", 10);
		LoadMaterial(aniShader, L"atlas_Will_Idle_Left", eRenderingMode::CutOut);

		
	}
	// Create Scene
	/*CSceneMgr::GetInst()->AddScene<CPlayScene>(L"PlayScene");
	CSceneMGr::GetInst()->AddScene<CVillageScene>*/
	CSceneMgr::GetInst()->Initialize();
}


void CRenderMgr::LoadTexture(const std::wstring& textureName, const std::wstring& path)
{
	std::shared_ptr<CTexture> tex = std::make_shared<CTexture>();
	tex->ResourceLoad(textureName, path);
	CResourceMgr::GetInst()->Insert(textureName, tex);
}

void CRenderMgr::LoadMaterial(std::shared_ptr<CShader> shader,const std::wstring& textureName, eRenderingMode renderMode)
{
	std::shared_ptr<CTexture> tex = CResourceMgr::GetInst()->Find<CTexture>(textureName);

	std::shared_ptr<CMaterial> mt = std::make_shared<CMaterial>();
	mt->SetName(L"mt_" + textureName);
	mt->SetShader(shader);
	mt->SetTexture(tex);
	mt->SetRenderMode(renderMode);
	CResourceMgr::GetInst()->Insert(L"mt_" + textureName, mt);
}

void CRenderMgr::Update()
{
	CSceneMgr::GetInst()->Update();
}

void CRenderMgr::LateUpdate()
{
	CSceneMgr::GetInst()->LateUpdate();
}

void CRenderMgr::Render()
{
	for (CCamera* cam : cameras)
	{
		if (cam == nullptr)
		{
			continue;
		}
		cam->Render();
	}
	cameras.clear();
}

void CRenderMgr::BindConstantBuffer(eShaderStage stage, CConstantBuffer* tCB)
{
	switch (stage)
	{
	case eShaderStage::VS:
		mGraphicContext->VSSetConstantBuffers((UINT)tCB->GetConstantType(), 1, (tCB->GetConstantBuffer().GetAddressOf()));
		break;
	case eShaderStage::HS:
		mGraphicContext->HSSetConstantBuffers((UINT)tCB->GetConstantType(), 1, (tCB->GetConstantBuffer().GetAddressOf()));
		break;
	case eShaderStage::DS:
		mGraphicContext->DSSetConstantBuffers((UINT)tCB->GetConstantType(), 1, (tCB->GetConstantBuffer().GetAddressOf()));
		break;
	case eShaderStage::GS:
		mGraphicContext->GSSetConstantBuffers((UINT)tCB->GetConstantType(), 1, (tCB->GetConstantBuffer().GetAddressOf()));
		break;
	case eShaderStage::PS:
		mGraphicContext->PSSetConstantBuffers((UINT)tCB->GetConstantType(), 1, (tCB->GetConstantBuffer().GetAddressOf()));
		break;
	case eShaderStage::CS:
		mGraphicContext->CSSetConstantBuffers((UINT)tCB->GetConstantType(), 1, (tCB->GetConstantBuffer().GetAddressOf()));
		break;
	case eShaderStage::End:
		break;
	default:
		break;
	}
}

void CRenderMgr::SetUpState()
{
	// Set Up Sampler State
	D3D11_SAMPLER_DESC samplerDecs = {};
	samplerDecs.AddressU = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDecs.AddressV = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDecs.AddressW = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDecs.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
	HRESULT hr = CDevice::GetInst()->GetDevice()->CreateSamplerState(&samplerDecs, samplerState[(UINT)eSamplerType::Point].GetAddressOf());
	BindSampler(eShaderStage::PS, 0, samplerState[(UINT)eSamplerType::Point].GetAddressOf());

	samplerDecs.Filter = D3D11_FILTER_ANISOTROPIC;
	CDevice::GetInst()->GetDevice()->CreateSamplerState(&samplerDecs, samplerState[(UINT)eSamplerType::Anisotropic].GetAddressOf());
	BindSampler(eShaderStage::PS, 1, samplerState[(UINT)eSamplerType::Anisotropic].GetAddressOf());



	// Set Up Rasterizer State
	D3D11_RASTERIZER_DESC rasterizerDesc = {};
	rasterizerDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
	rasterizerDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_BACK;
	CDevice::GetInst()->GetDevice()->CreateRasterizerState(&rasterizerDesc
		, rasterizerStates[(UINT)eRSType::SolidBack].GetAddressOf());

	rasterizerDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
	rasterizerDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_FRONT;
	CDevice::GetInst()->GetDevice()->CreateRasterizerState(&rasterizerDesc
		, rasterizerStates[(UINT)eRSType::SolidFront].GetAddressOf());

	rasterizerDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
	rasterizerDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;
	CDevice::GetInst()->GetDevice()->CreateRasterizerState(&rasterizerDesc
		, rasterizerStates[(UINT)eRSType::SolidNone].GetAddressOf());

	rasterizerDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_WIREFRAME;
	rasterizerDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;
	CDevice::GetInst()->GetDevice()->CreateRasterizerState(&rasterizerDesc
		, rasterizerStates[(UINT)eRSType::WireframeNone].GetAddressOf());



	// Set Up DepthStencil State
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc = {};

	//less
	depthStencilDesc.DepthEnable = true;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDesc.StencilEnable = false;

	CDevice::GetInst()->GetDevice()->CreateDepthStencilState(&depthStencilDesc
		, depthStencilStates[(UINT)eDSType::Less].GetAddressOf());

	//Greater
	depthStencilDesc.DepthEnable = true;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_GREATER;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDesc.StencilEnable = false;

	CDevice::GetInst()->GetDevice()->CreateDepthStencilState(&depthStencilDesc
		, depthStencilStates[(UINT)eDSType::Greater].GetAddressOf());

	//No Write
	depthStencilDesc.DepthEnable = true;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
	depthStencilDesc.StencilEnable = false;

	CDevice::GetInst()->GetDevice()->CreateDepthStencilState(&depthStencilDesc
		, depthStencilStates[(UINT)eDSType::NoWrite].GetAddressOf());

	//None
	depthStencilDesc.DepthEnable = false;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
	depthStencilDesc.StencilEnable = false;

	CDevice::GetInst()->GetDevice()->CreateDepthStencilState(&depthStencilDesc
		, depthStencilStates[(UINT)eDSType::None].GetAddressOf());



	// Set Up Blend State
	D3D11_BLEND_DESC blendDesc = {};

	//default
	blendStates[(UINT)eBSType::Default] = nullptr;

	// Alpha Blend
	blendDesc.AlphaToCoverageEnable = false;
	blendDesc.IndependentBlendEnable = false;
	blendDesc.RenderTarget[0].BlendEnable = true;
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	CDevice::GetInst()->GetDevice()->CreateBlendState(&blendDesc
		, blendStates[(UINT)eBSType::AlphaBlend].GetAddressOf());

	// one one
	blendDesc.AlphaToCoverageEnable = false;
	blendDesc.IndependentBlendEnable = false;

	blendDesc.RenderTarget[0].BlendEnable = true;
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	CDevice::GetInst()->GetDevice()->CreateBlendState(&blendDesc
		, blendStates[(UINT)eBSType::OneOne].GetAddressOf());
}

void CRenderMgr::BindSampler(eShaderStage stage, UINT StartSlot, ID3D11SamplerState** ppSamplerState)
{
	switch (stage)
	{
	case eShaderStage::VS:
		mGraphicContext->VSSetSamplers(StartSlot, 1, ppSamplerState);
		break;
	case eShaderStage::HS:
		mGraphicContext->HSSetSamplers(StartSlot, 1, ppSamplerState);
		break;
	case eShaderStage::DS:
		mGraphicContext->DSSetSamplers(StartSlot, 1, ppSamplerState);
		break;
	case eShaderStage::GS:
		mGraphicContext->GSSetSamplers(StartSlot, 1, ppSamplerState);
		break;
	case eShaderStage::PS:
		mGraphicContext->PSSetSamplers(StartSlot, 1, ppSamplerState);
		break;
	case eShaderStage::CS:
		mGraphicContext->CSSetSamplers(StartSlot, 1, ppSamplerState);
		break;
	case eShaderStage::End:
		break;
	default:
		break;
	}
}

//void CRenderMgr::CreateAtlas(const std::wstring& path, const std::wstring& spriteName, int spriteNum)
void CRenderMgr::CreateAtlas(const std::wstring& spriteName, int spriteNum)
{
	std::shared_ptr<CTexture> atlasTex = std::make_shared<CTexture>(); // 최종 아틀라스 텍스쳐
	std::shared_ptr<CTexture> tex = std::make_shared<CTexture>(); // 각 Sprite 가 담길 
	bool isMade = false; // 아틀라스 이미지의 처음 규격 생성 여부
	std::filesystem::path Path = L"..\\Resource\\Texture\\Animation\\";
	Path += spriteName;  // 폴더명
	Path += L"\\";
	Path += spriteName;  // 폴더명과 같은 각 sprite 의 공통된 이름
	Path += L"_";

	ScratchImage atlasImage;
	size_t atlasImageWidth;
	size_t atlasImageHeight;

	for (int i = 0; i < spriteNum; i++)
	{
		std::filesystem::path path = Path;
		path += std::to_wstring(i + 1);
		path += L".png";
		HRESULT hr = tex->ResourceLoad(spriteName, path);
		if (hr == S_OK)
		{
			if (isMade == false)
			{
				atlasImageWidth = (tex->GetWidth()) * spriteNum;
				atlasImageHeight = tex->GetHeight();
				atlasImage.Initialize2D(DXGI_FORMAT_R8G8B8A8_UNORM, atlasImageWidth, atlasImageHeight, 1, 1);
				isMade = true;
			}
		}

		/*hr = CopyRectangle(
			*tex->GetScratchImage(),
			Rect(0, 0, tex->GetWidth(), tex->GetHeight()),
			*atlasImage.GetImages(),
			TEX_FILTER_DEFAULT,
			(i % 10) * (tex->GetWidth()),
			(i / 10) * (tex->GetHeight())
		);*/

		hr = CopyRectangle(
			*tex->GetScratchImage(),
			Rect(0, 0, tex->GetWidth(), tex->GetHeight()),
			*atlasImage.GetImages(),
			TEX_FILTER_DEFAULT,
			i * (tex->GetWidth()),
			0
		);

		//tex->CreateSRV(&atlasImage);
	}

	atlasTex->InitScratImage(atlasImageWidth, atlasImageHeight);

	CopyRectangle(
		*atlasImage.GetImages(),
		Rect(0, 0, atlasImage.GetMetadata().width, atlasImage.GetMetadata().height),
		*atlasTex->GetScratchImage(),
		TEX_FILTER_DEFAULT,
		0, 0
	);

	atlasTex->CreateSRV();

	CResourceMgr::GetInst()->Insert(L"atlas_" + spriteName, atlasTex);
}