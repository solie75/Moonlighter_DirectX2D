#include "CPlayerMoveScript.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"

void CPlayerMoveScript::Update()
{
	CTransform* tr = GetOwner()->GetComponent<CTransform>(eComponentType::Transform);
	Vector3 pos = tr->GetPosition();

	if (CKeyMgr::GetInst()->GetKeyState(KEY::LEFT) == KEY_STATE::PRESSED)
	{
		pos.x -= (float)(5.0 * CTimeMgr::GetInst()->GetDeltaTime());
		tr->SetPosition(pos);
	}
	if (CKeyMgr::GetInst()->GetKeyState(KEY::RIGHT) == KEY_STATE::PRESSED)
	{
		pos.x += (float)(5.0 * CTimeMgr::GetInst()->GetDeltaTime());
		tr->SetPosition(pos);
	}
	if (CKeyMgr::GetInst()->GetKeyState(KEY::UP) == KEY_STATE::PRESSED)
	{
		pos.y += (float)(5.0 * CTimeMgr::GetInst()->GetDeltaTime());
		tr->SetPosition(pos);
	}
	if (CKeyMgr::GetInst()->GetKeyState(KEY::DOWN) == KEY_STATE::PRESSED)
	{
		pos.y -= (float)(5.0 * CTimeMgr::GetInst()->GetDeltaTime());
		tr->SetPosition(pos);
	}
}
