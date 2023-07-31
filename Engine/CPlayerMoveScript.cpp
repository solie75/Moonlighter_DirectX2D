#include "CPlayerMoveScript.h"
#include "CTimeMgr.h"
#include "CAnimator.h"
#include "CPlayer.h"


CPlayerMoveScript::CPlayerMoveScript()
	: mKey(KEY::END)
	, CurState(KEY_STATE::NONE)
	, PrevState(KEY_STATE::NONE)
	, bAni(true) // true �϶� �ִϸ��̼� �۵� // false �϶� �ִϸ��̼� ���۵�
	, bAniTime(0.0f)
{
}

CPlayerMoveScript::~CPlayerMoveScript() {}

void CPlayerMoveScript::Initialize() {}

void CPlayerMoveScript::Update()
{
	CTransform* tr = GetOwner()->GetComponent<CTransform>(eComponentType::Transform);
	Vector3 pos = tr->GetPosition();
	CAnimator* at = GetOwner()->GetComponent<CAnimator>(eComponentType::Animator);
	CPlayer* player = dynamic_cast<CPlayer*>(GetOwner());
	CState* state = player->GetState();
	CAimSight* aimSight = player->GetAimSight();

	if (player->IsAniChange()) // Ű �Է� ���� ����
	{
		// ������ȯ
		if (CKeyMgr::GetInst()->GetKeyState(KEY::LEFT) == KEY_STATE::TAP)
		{
			aimSight->SetAimSight(eAimSight::Left);
		}
		if (CKeyMgr::GetInst()->GetKeyState(KEY::RIGHT) == KEY_STATE::TAP)
		{
			aimSight->SetAimSight(eAimSight::Right);
		}
		if (CKeyMgr::GetInst()->GetKeyState(KEY::UP) == KEY_STATE::TAP)
		{
			aimSight->SetAimSight(eAimSight::Up);
		}
		if (CKeyMgr::GetInst()->GetKeyState(KEY::DOWN) == KEY_STATE::TAP)
		{
			aimSight->SetAimSight(eAimSight::Down);
		}

		// ĳ���� ��ġ ��ȭ
		if (CKeyMgr::GetInst()->GetKeyState(KEY::LEFT) == KEY_STATE::PRESSED)
		{
			pos.x -= (float)(2.0 * CTimeMgr::GetInst()->GetDeltaTime());
			tr->SetPosition(pos);
			state->SetState(eState::Walk);
		}
		if (CKeyMgr::GetInst()->GetKeyState(KEY::RIGHT) == KEY_STATE::PRESSED)
		{
			pos.x += (float)(2.0 * CTimeMgr::GetInst()->GetDeltaTime());
			tr->SetPosition(pos);
			state->SetState(eState::Walk);
		}
		if (CKeyMgr::GetInst()->GetKeyState(KEY::UP) == KEY_STATE::PRESSED)
		{
			pos.y += (float)(2.0 * CTimeMgr::GetInst()->GetDeltaTime());
			tr->SetPosition(pos);
			state->SetState(eState::Walk);
		}
		if (CKeyMgr::GetInst()->GetKeyState(KEY::DOWN) == KEY_STATE::PRESSED)
		{
			pos.y -= (float)(2.0 * CTimeMgr::GetInst()->GetDeltaTime());
			tr->SetPosition(pos);
			state->SetState(eState::Walk);
		}

		// ����Ű���� ���� ���� Idle ���·�
		if (CKeyMgr::GetInst()->GetKeyState(KEY::LEFT) == KEY_STATE::RELEASE)
		{
			state->SetState(eState::Idle);
		}
		if (CKeyMgr::GetInst()->GetKeyState(KEY::RIGHT) == KEY_STATE::RELEASE)
		{
			state->SetState(eState::Idle);
		}
		if (CKeyMgr::GetInst()->GetKeyState(KEY::UP) == KEY_STATE::RELEASE)
		{
			state->SetState(eState::Idle);
		}
		if (CKeyMgr::GetInst()->GetKeyState(KEY::DOWN) == KEY_STATE::RELEASE)
		{
			state->SetState(eState::Idle);
		}

		// �����̽��ٷ� ������ ���·� ��ȯ
		if (CKeyMgr::GetInst()->GetKeyState(KEY::SPACE) == KEY_STATE::TAP)
		{
			player->SetBoolAniChange(false);
			state->SetState(eState::Roll);

			switch (aimSight->GetAimSight())
			{
			case eAimSight::Left:
				pos.x -= (float)(2.0 * CTimeMgr::GetInst()->GetDeltaTime());
				tr->SetPosition(pos);
				break;
			case eAimSight::Right:
				pos.x += (float)(2.0 * CTimeMgr::GetInst()->GetDeltaTime());
				tr->SetPosition(pos);
				break;
			case eAimSight::Up:
				pos.y += (float)(2.0 * CTimeMgr::GetInst()->GetDeltaTime());
				tr->SetPosition(pos);
				break;
			case eAimSight::Down:
				pos.y -= (float)(2.0 * CTimeMgr::GetInst()->GetDeltaTime());
				tr->SetPosition(pos);
				break;
			}
		}
	}
	
//if (CKeyMgr::GetInst()->GetKeyState(KEY::SPACE) == KEY_STATE::TAP)
//{
//	GetOwner()->SetBehave(CGameObject::eBehave::Roll);
//}
//
//if(GetOwner()->GetBehave() == CGameObject::eBehave::Roll)
//{
//	if (GetOwner()->GetDirection() == CGameObject::eDirection::Down)
//	{
//		pos.y -= (float)(2.0 * CTimeMgr::GetInst()->GetDeltaTime());
//		tr->SetPosition(pos);
//	}
//	else if (GetOwner()->GetDirection() == CGameObject::eDirection::Left)
//	{
//		pos.x -= (float)(2.0 * CTimeMgr::GetInst()->GetDeltaTime());
//		tr->SetPosition(pos);
//	}
//	else if (GetOwner()->GetDirection() == CGameObject::eDirection::Right)
//	{
//		pos.x += (float)(2.0 * CTimeMgr::GetInst()->GetDeltaTime());
//		tr->SetPosition(pos);
//	}
//	else if (GetOwner()->GetDirection() == CGameObject::eDirection::Up)
//	{
//		pos.y += (float)(2.0 * CTimeMgr::GetInst()->GetDeltaTime());
//		tr->SetPosition(pos);
//	}
//
//	
//	bAniTime += CTimeMgr::GetInst()->GetDeltaTime();
//	if (0.6f <= bAniTime)
//	{
//		bAniTime = 0.0f;
//		bAni = true;
//		GetOwner()->SetBehave(CGameObject::eBehave::Idle);
//	}
//}
}

void CPlayerMoveScript::LateUpdate()
{
}
