#include "CDesertBossScript.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CTransform.h"

CDesertBossScript::CDesertBossScript()
{
}

CDesertBossScript::~CDesertBossScript()
{
}

void CDesertBossScript::Initialize()
{
}

void CDesertBossScript::Update()
{
	CTransform* tr = this->GetOwner()->GetComponent<CTransform>(eComponentType::Transform);
	Vector3 pos = tr->GetPosition();

	if (CKeyMgr::GetInst()->GetKeyState(KEY::F) == KEY_STATE::PRESSED)
	{
		pos.x -= (float)(2.0 * CTimeMgr::GetInst()->GetDeltaTime());
		tr->SetPosition(pos);
	}
	if (CKeyMgr::GetInst()->GetKeyState(KEY::H) == KEY_STATE::PRESSED)
	{
		pos.x += (float)(2.0 * CTimeMgr::GetInst()->GetDeltaTime());
		tr->SetPosition(pos);
	}
	if (CKeyMgr::GetInst()->GetKeyState(KEY::T) == KEY_STATE::PRESSED)
	{
		pos.y += (float)(2.0 * CTimeMgr::GetInst()->GetDeltaTime());
		tr->SetPosition(pos);
	}
	if (CKeyMgr::GetInst()->GetKeyState(KEY::G) == KEY_STATE::PRESSED)
	{
		pos.y -= (float)(2.0 * CTimeMgr::GetInst()->GetDeltaTime());
		tr->SetPosition(pos);
	}
}

void CDesertBossScript::LateUpdate()
{
}

void CDesertBossScript::Render()
{
}
