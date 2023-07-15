#include "CCameraMoveScript.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"

void CCameraMoveScript::Update()
{
	CTransform* tr = GetOwner()->GetComponent<CTransform>(eComponentType::Transform);
	Vector3 pos = tr->GetPosition();

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
