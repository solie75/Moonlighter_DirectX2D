#include "CPlayerMoveScript.h"
#include "CTimeMgr.h"
#include "CAnimator.h"


CPlayerMoveScript::CPlayerMoveScript()
	: mKey(KEY::END)
	, CurState(KEY_STATE::NONE)
	, PrevState(KEY_STATE::NONE)
	, bAni(true) // true 일때 애니메이션 작동 // false 일때 애니메이션 비작동
	, bAniTime(0.0f)
{
}

CPlayerMoveScript::~CPlayerMoveScript()
{
}

void CPlayerMoveScript::Initialize()
{
	CAnimator* at = GetOwner()->GetComponent<CAnimator>(eComponentType::Animator);
	at->CompleteEvent(L"Will_Idle_Down");
}

void CPlayerMoveScript::Update()
{
	CTransform* tr = GetOwner()->GetComponent<CTransform>(eComponentType::Transform);
	Vector3 pos = tr->GetPosition();

	if (CKeyMgr::GetInst()->GetKeyState(KEY::LEFT) == KEY_STATE::PRESSED)
	{
		pos.x -= (float)(2.0 * CTimeMgr::GetInst()->GetDeltaTime());
		tr->SetPosition(pos);
	}
	if (CKeyMgr::GetInst()->GetKeyState(KEY::RIGHT) == KEY_STATE::PRESSED)
	{
		pos.x += (float)(2.0 * CTimeMgr::GetInst()->GetDeltaTime());
		tr->SetPosition(pos);
	}
	if (CKeyMgr::GetInst()->GetKeyState(KEY::UP) == KEY_STATE::PRESSED)
	{
		pos.y += (float)(2.0 * CTimeMgr::GetInst()->GetDeltaTime());
		tr->SetPosition(pos);
	}
	if (CKeyMgr::GetInst()->GetKeyState(KEY::DOWN) == KEY_STATE::PRESSED)
	{
		pos.y -= (float)(2.0 * CTimeMgr::GetInst()->GetDeltaTime());
		tr->SetPosition(pos);
	}
	
//	if (bAni == true)
//	{
//		if (CKeyMgr::GetInst()->GetKeyState(KEY::LEFT) == KEY_STATE::PRESSED)
//		{
//			GetOwner()->SetBehave(CGameObject::eBehave::Walk);
//			GetOwner()->SetDirection(CGameObject::eDirection::Left);
//			pos.x -= (float)(2.0 * CTimeMgr::GetInst()->GetDeltaTime());
//			tr->SetPosition(pos);
//		}
//		if (CKeyMgr::GetInst()->GetKeyState(KEY::RIGHT) == KEY_STATE::PRESSED)
//		{
//			GetOwner()->SetBehave(CGameObject::eBehave::Walk);
//			GetOwner()->SetDirection(CGameObject::eDirection::Right);
//			pos.x += (float)(2.0 * CTimeMgr::GetInst()->GetDeltaTime());
//			tr->SetPosition(pos);
//		}
//		if (CKeyMgr::GetInst()->GetKeyState(KEY::UP) == KEY_STATE::PRESSED)
//		{
//			GetOwner()->SetBehave(CGameObject::eBehave::Walk);
//			GetOwner()->SetDirection(CGameObject::eDirection::Up);
//			pos.y += (float)(2.0 * CTimeMgr::GetInst()->GetDeltaTime());
//			tr->SetPosition(pos);
//		}
//		if (CKeyMgr::GetInst()->GetKeyState(KEY::DOWN) == KEY_STATE::PRESSED)
//		{
//			GetOwner()->SetBehave(CGameObject::eBehave::Walk);
//			GetOwner()->SetDirection(CGameObject::eDirection::Down);
//			pos.y -= (float)(2.0 * CTimeMgr::GetInst()->GetDeltaTime());
//			tr->SetPosition(pos);
//		}
//
//		//
//		if (CKeyMgr::GetInst()->GetKeyState(KEY::LEFT) == KEY_STATE::NONE
//			&& CKeyMgr::GetInst()->GetKeyState(KEY::RIGHT) == KEY_STATE::NONE
//			&& CKeyMgr::GetInst()->GetKeyState(KEY::UP) == KEY_STATE::NONE
//			&& CKeyMgr::GetInst()->GetKeyState(KEY::DOWN) == KEY_STATE::NONE)
//		{
//			GetOwner()->SetBehave(CGameObject::eBehave::Idle);
//		}
//	}
//	
//	if (CKeyMgr::GetInst()->GetKeyState(KEY::SPACE) == KEY_STATE::TAP)
//	{
//		GetOwner()->SetBehave(CGameObject::eBehave::Roll);
//	}
//
//	if(GetOwner()->GetBehave() == CGameObject::eBehave::Roll)
//	{
//		if (GetOwner()->GetDirection() == CGameObject::eDirection::Down)
//		{
//			pos.y -= (float)(2.0 * CTimeMgr::GetInst()->GetDeltaTime());
//			tr->SetPosition(pos);
//		}
//		else if (GetOwner()->GetDirection() == CGameObject::eDirection::Left)
//		{
//			pos.x -= (float)(2.0 * CTimeMgr::GetInst()->GetDeltaTime());
//			tr->SetPosition(pos);
//		}
//		else if (GetOwner()->GetDirection() == CGameObject::eDirection::Right)
//		{
//			pos.x += (float)(2.0 * CTimeMgr::GetInst()->GetDeltaTime());
//			tr->SetPosition(pos);
//		}
//		else if (GetOwner()->GetDirection() == CGameObject::eDirection::Up)
//		{
//			pos.y += (float)(2.0 * CTimeMgr::GetInst()->GetDeltaTime());
//			tr->SetPosition(pos);
//		}
//
//		
//		bAniTime += CTimeMgr::GetInst()->GetDeltaTime();
//		if (0.6f <= bAniTime)
//		{
//			bAniTime = 0.0f;
//			bAni = true;
//			GetOwner()->SetBehave(CGameObject::eBehave::Idle);
//		}
//	}
}

void CPlayerMoveScript::LateUpdate()
{
	//CAnimator* at = GetOwner()->GetComponent<CAnimator>(eComponentType::Animator);
	//if (GetOwner()->GetBehave() == CGameObject::eBehave::Roll && bAni == true)
	//{
	//	switch (GetOwner()->GetDirection())
	//	{
	//	case CGameObject::eDirection::Down:
	//		bAni = false;
	//		at->PlayAnimation(L"Will_Roll_Down", false);
	//		break;
	//	case CGameObject::eDirection::Left:
	//		bAni = false;
	//		at->PlayAnimation(L"Will_Roll_Left", false);
	//		break;
	//	case CGameObject::eDirection::Right:
	//		bAni = false;
	//		at->PlayAnimation(L"Will_Roll_Right", false);
	//		break;
	//	case CGameObject::eDirection::Up:
	//		bAni = false;
	//		at->PlayAnimation(L"Will_Roll_Up", false);
	//		break;
	//	}
	//}
	//if (GetOwner()->GetBehave() == CGameObject::eBehave::Walk && GetOwner()->GetPrevBehave() != CGameObject::eBehave::Walk)
	//{
	//	switch (GetOwner()->GetDirection())
	//	{
	//	case CGameObject::eDirection::Down :
	//		at->PlayAnimation(L"Will_Walk_Down", true);
	//		break;
	//	case CGameObject::eDirection::Left :
	//		at->PlayAnimation(L"Will_Walk_Left", true);
	//		break;
	//	case CGameObject::eDirection::Right :
	//		at->PlayAnimation(L"Will_Walk_Right", true);
	//		break;
	//	case CGameObject::eDirection::Up :
	//		at->PlayAnimation(L"Will_Walk_Up", true);
	//		break;
	//	}
	//}
	//if (GetOwner()->GetBehave() == CGameObject::eBehave::Idle && GetOwner()->GetPrevBehave() != CGameObject::eBehave::Idle)
	//{
	//	switch (GetOwner()->GetDirection())
	//	{
	//	case CGameObject::eDirection::Down:
	//		at->PlayAnimation(L"Will_Idle_Down", true);
	//		break;
	//	case CGameObject::eDirection::Left:
	//		at->PlayAnimation(L"Will_Idle_Left", true);
	//		break;
	//	case CGameObject::eDirection::Right:
	//		at->PlayAnimation(L"Will_Idle_Right", true);
	//		break;
	//	case CGameObject::eDirection::Up:
	//		at->PlayAnimation(L"Will_Idle_Up", true);
	//		break;
	//	}
	//}
}
