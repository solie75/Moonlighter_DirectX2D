#include "CCameraMoveScript.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"

CCameraMoveScript::CCameraMoveScript()
{
}

CCameraMoveScript::~CCameraMoveScript()
{
}

void CCameraMoveScript::Initialize()
{
	OnFixed = false;
	CScript::Initialize();
}

void CCameraMoveScript::Update()
{
	CTransform* tr = GetOwner()->GetComponent<CTransform>(eComponentType::Transform);
	Vector3 pos = tr->GetPosition();
	if (OnFixed == false)
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
	else // 플레이어에 고정
	{
		pos.x = playerPos.x;
		pos.y = playerPos.y;
		tr->SetPosition(pos);
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
