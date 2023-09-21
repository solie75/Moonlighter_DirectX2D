#include "CCameraMoveScript.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"

CCameraMoveScript::CCameraMoveScript()
	: cameraFocused(eCameraFocusing::None)
{
	//cameraFocused = eCameraFocusing::None;

}

CCameraMoveScript::~CCameraMoveScript()
{
}

void CCameraMoveScript::Initialize()
{
	
	CScript::Initialize();
}

void CCameraMoveScript::Update()
{
	CTransform* tr = GetOwner()->GetComponent<CTransform>(eComponentType::Transform);
	Vector3 pos = tr->GetPosition();

	if (cameraFocused == eCameraFocusing::None)
	{
		if (CKeyMgr::GetInst()->GetKeyState(KEY::A) == KEY_STATE::PRESSED)
		{
			pos.x -= (float)(5.0 * CTimeMgr::GetInst()->GetDeltaTime());
			tr->SetPosition(pos);
		}
		if (CKeyMgr::GetInst()->GetKeyState(KEY::D) == KEY_STATE::PRESSED)
		{
			pos.x += (float)(5.0 * CTimeMgr::GetInst()->GetDeltaTime());
			tr->SetPosition(pos);
		}
		if (CKeyMgr::GetInst()->GetKeyState(KEY::S) == KEY_STATE::PRESSED)
		{
			pos.y -= (float)(5.0 * CTimeMgr::GetInst()->GetDeltaTime());
			tr->SetPosition(pos);
		}
		if (CKeyMgr::GetInst()->GetKeyState(KEY::W) == KEY_STATE::PRESSED)
		{
			pos.y += (float)(5.0 * CTimeMgr::GetInst()->GetDeltaTime());
			tr->SetPosition(pos);
		}
		if (CKeyMgr::GetInst()->GetKeyState(KEY::Q) == KEY_STATE::PRESSED)
		{
			pos.z -= (float)(5.0 * CTimeMgr::GetInst()->GetDeltaTime());
			tr->SetPosition(pos);
		}
		if (CKeyMgr::GetInst()->GetKeyState(KEY::E) == KEY_STATE::PRESSED)
		{
			pos.z += (float)(5.0 * CTimeMgr::GetInst()->GetDeltaTime());
			tr->SetPosition(pos);
		}
	}
	else if(cameraFocused == eCameraFocusing::Player)// 플레이어에 고정
	{
		if (nullptr != PlayerTr)
		{
			Vector3 PlayerPos = PlayerTr->GetPosition();
			pos.x = PlayerPos.x;
			pos.y = PlayerPos.y;
			tr->SetPosition(pos);
		}
	}
	else if (cameraFocused == eCameraFocusing::Map)
	{
		MoveCameraForMap();
	}
	else if (cameraFocused == eCameraFocusing::End)
	{

	}
	CScript::Update();
}

void CCameraMoveScript::LateUpdate()
{
	CScript::LateUpdate();
}

void CCameraMoveScript::Render()
{
	CScript::Render();
}

void CCameraMoveScript::MoveCameraForMap()
{
}
