#include "CStartMenuScene.h"
//#include "CCameraMoveScript.h"

CStartMenuScene::CStartMenuScene()
{
}

CStartMenuScene::~CStartMenuScene()
{
}

void CStartMenuScene::Initialize()
{
	{ // Background
		CGameObject* Start_Intro_Door_Right = new CGameObject();
		AddGameObject(eLayerType::Background, Start_Intro_Door_Right, L"Start_Intro_Door_Right", Vector3(2.1f, 0.02f, -0.03f),
			Vector3(4.1f, 4.55f, 0.0f), true, L"Mesh", L"mt_Start_Intro_Door_Right", false);

		CGameObject* Start_Intro_Door_Left = new CGameObject();
		AddGameObject(eLayerType::Background, Start_Intro_Door_Left, L"Start_Intro_Door_Left", Vector3(-2.05f, 0.02f, -0.04f),
			Vector3(4.1f, 4.55f, 0.0f), true, L"Mesh", L"mt_Start_Intro_Door_Left",false);

		/*CGameObject* Start_Intro_Door_Right = new CGameObject(); // 문이 완전히 열렸을 때
		AddGameObject(eLayerType::Background, Start_Intro_Door_Right, L"Start_Intro_Door_Right", Vector3(5.0f, 0.02f, -0.03f),
			Vector3(4.1f, 4.55f, 0.0f), true, L"Mesh", L"mt_Start_Intro_Door_Right",false);

		CGameObject* Start_Intro_Door_Left = new CGameObject();
		AddGameObject(eLayerType::Background, Start_Intro_Door_Left, L"Start_Intro_Door_Left", Vector3(-5.0f, 0.02f, -0.04f),
			Vector3(4.1f, 4.55f, 0.0f), true, L"Mesh", L"mt_Start_Intro_Door_Left",false);*/
	}
	{ // logo
		CGameObject* GameLogo = new CGameObject(); // 완전 투명에서 서서히 완전 불투명으로 나타남
		AddGameObject(eLayerType::Background, GameLogo, L"GameLogo", Vector3(0.f, 0.85f, -0.05f),
			Vector3(1.85f, 1.5f, 0.0f), true, L"Mesh", L"mt_GameLogo",false);
	}
	{ // animation
		CGameObject* Main_menu_1_1 = new CGameObject(); // 완전 투명에서 서서히 완전 불투명으로 나타남
		AddGameObject(eLayerType::Background, Main_menu_1_1, L"Main_menu_1_1", Vector3(0.f, 0.0f, -0.02f),
			Vector3(5.9f, 4.7f, 0.0f), true, L"Mesh", L"mt_Main_menu_1_1",false);

		CGameObject* Main_menu_2_1 = new CGameObject(); // 완전 투명에서 서서히 완전 불투명으로 나타남
		AddGameObject(eLayerType::Background, Main_menu_2_1, L"Main_menu_2_1", Vector3(0.f, 0.0f, -0.01f),
			Vector3(5.9f, 4.7f, 0.0f), true, L"Mesh", L"mt_Main_menu_2_1",false);
	}
	{ // camera
		CGameObject* mainCamera = new CGameObject();
		AddGameObject(eLayerType::Player, mainCamera, L"MainCamera", Vector3(0.0f, 0.0f, -10.0f),
			Vector3(1.0f, 1.0f, 1.0f), false, L"", L"",false);
		CCamera* mainCamComp = mainCamera->AddComponent<CCamera>(eComponentType::Camera);
		mainCamComp->SetCameraType(eCameraType::Main);
		//mainCamera->AddComponent<CCameraMoveScript>();
	}
}

void CStartMenuScene::Update()
{
	CScene::Update();
}

void CStartMenuScene::LateUpdate()
{
	CScene::LateUpdate();
}

void CStartMenuScene::Render()
{
	CScene::Render();
}
