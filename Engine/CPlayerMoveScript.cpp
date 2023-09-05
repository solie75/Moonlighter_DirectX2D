#include "CPlayerMoveScript.h"
#include "CTimeMgr.h"
#include "CAnimator.h"
#include "CPlayer.h"


CPlayerMoveScript::CPlayerMoveScript()
	: 
	mComboAttackNum(0)
	//, mLeftKey(KEY_STATE::NONE)
	//, mRightKey(KEY_STATE::NONE)
	//, mUpKey(KEY_STATE::NONE)
	//, mDownKey(KEY_STATE::NONE)
	//, bAni(true) // true 일때 애니메이션 작동 // false 일때 애니메이션 비작동
	//, mAniTime(0.0f)
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

	if (state->IsStateChange())
	{
		// 캐릭터 위치 변화
		if (CKeyMgr::GetInst()->GetKeyState(KEY::LEFT) == KEY_STATE::PRESSED)
		{
			aimSight->SetSight(CAimSight::eSight::Left);
			pos.x -= (float)(2.0 * CTimeMgr::GetInst()->GetDeltaTime());
			tr->SetPosition(pos);
			state->SetState(eState::Walk);
		}
		if (CKeyMgr::GetInst()->GetKeyState(KEY::RIGHT) == KEY_STATE::PRESSED)
		{
			aimSight->SetSight(CAimSight::eSight::Right);
			pos.x += (float)(2.0 * CTimeMgr::GetInst()->GetDeltaTime());
			tr->SetPosition(pos);
			state->SetState(eState::Walk);
		}
		if (CKeyMgr::GetInst()->GetKeyState(KEY::UP) == KEY_STATE::PRESSED)
		{
			aimSight->SetSight(CAimSight::eSight::Up);
			pos.y += (float)(2.0 * CTimeMgr::GetInst()->GetDeltaTime());
			tr->SetPosition(pos);
			state->SetState(eState::Walk);
		}
		if (CKeyMgr::GetInst()->GetKeyState(KEY::DOWN) == KEY_STATE::PRESSED)
		{
			aimSight->SetSight(CAimSight::eSight::Down);
			pos.y -= (float)(2.0 * CTimeMgr::GetInst()->GetDeltaTime());
			tr->SetPosition(pos);
			state->SetState(eState::Walk);
		}

		// 방향키에서 손을 떼면 Idle 상태로
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

		// 구르기 상태로 변환
		if (CKeyMgr::GetInst()->GetKeyState(KEY::SPACE) == KEY_STATE::TAP)
		{
			state->SetBoolStateChange(false);
			state->SetState(eState::Roll);
		}
	}

	// Trans to Attack State
	
	// Main Attack
	if (CKeyMgr::GetInst()->GetKeyState(KEY::J) == KEY_STATE::TAP)
	{
		state->SetBoolStateChange(false);
		state->SetState(eState::Attack);

		if (mComboAttackNum == 0)
		{
			mComboAttackNum += 1;
		}

		// 첫번재 콤보의 애니메이션 11개중 8번째 이상부터
		if (mComboAttackNum == 1 && at->GetCurAnimation()->GetAnimationIndex() >= 8)
		{
			mComboAttackNum += 1;
		}

		if (mComboAttackNum == 2 && at->GetCurAnimation()->GetAnimationIndex() >= 8)
		{
			mComboAttackNum += 1;
		}
	}

	// Sub Attack
	//if (CKeyMgr::GetInst()->GetKeyState(KEY::K) == KEY_STATE::TAP)
	//{
	//	state->SetBoolStateChange(false);
	//	state->SetState(eState::Attack);
	//}
}

void CPlayerMoveScript::LateUpdate()
{
}
