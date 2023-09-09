#include "CPlayerMoveScript.h"
#include "CTimeMgr.h"
#include "CAnimator.h"
#include "CPlayer.h"
#include "CWeapon.h"


CPlayerMoveScript::CPlayerMoveScript()
	: mComboAttackNum(0)
	, mbNextCombo(false)
	, mSubAttackState(eSubAttackState::End)
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

		// BigSword 인 경우
		if (player->GetWeapon()->GetWeaponType() == CWeapon::eWeaponType::BigSword)
		{
			if (mComboAttackNum == 0)
			{
				mComboAttackNum += 1;
			}

			// 첫번재 콤보의 애니메이션 11개중 8번째 이상부터
			if (mComboAttackNum == 1 && at->GetCurAnimation()->GetAnimationIndex() >= 8)
			{
				if (mbNextCombo == false)
				{
					mComboAttackNum += 1;
					mbNextCombo = true;
				}
			}

			if (mComboAttackNum == 2 && at->GetCurAnimation()->GetAnimationIndex() >= 8)
			{
				if (mbNextCombo == false)
				{
					mComboAttackNum += 1;
					mbNextCombo = true;
				}
			}
		}
	}

	// Sub Attack
	if (CKeyMgr::GetInst()->GetKeyState(KEY::K) == KEY_STATE::TAP)
	{
		state->SetBoolStateChange(false);
		state->SetState(eState::Attack);
		mSubAttackState = eSubAttackState::Enter;
	}
	else if (CKeyMgr::GetInst()->GetKeyState(KEY::K) == KEY_STATE::PRESSED)
	{
		mSubAttackState = eSubAttackState::Stay;
		// 키를 계속 누르고 있지만 이미 동작은 끝난 경우
		if (at->GetCurAnimation()->IsComplete() == true)
		{
			mSubAttackState = eSubAttackState::Exit;
		}
	}
	else if (CKeyMgr::GetInst()->GetKeyState(KEY::K) == KEY_STATE::RELEASE)
	{
		mSubAttackState = eSubAttackState::Exit;
	}
}

void CPlayerMoveScript::LateUpdate()
{
}
