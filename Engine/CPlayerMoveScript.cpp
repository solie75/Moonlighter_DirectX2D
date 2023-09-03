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

	// 방향전환
	//if (CKeyMgr::GetInst()->GetKeyState(KEY::LEFT) == KEY_STATE::TAP)
	//{
	//	aimSight->SetAimSight(eAimSight::Left);
	//	//mLeftKey = KEY_STATE::TAP;
	//}
	//if (CKeyMgr::GetInst()->GetKeyState(KEY::RIGHT) == KEY_STATE::TAP)
	//{
	//	aimSight->SetAimSight(eAimSight::Right);
	//	//mRightKey = KEY_STATE::TAP;
	//}
	//if (CKeyMgr::GetInst()->GetKeyState(KEY::UP) == KEY_STATE::TAP)
	//{
	//	aimSight->SetAimSight(eAimSight::Up);
	//	//mUpKey = KEY_STATE::TAP;
	//}
	//if (CKeyMgr::GetInst()->GetKeyState(KEY::DOWN) == KEY_STATE::TAP)
	//{
	//	aimSight->SetAimSight(eAimSight::Down);
	//	//mDownKey = KEY_STATE::TAP;
	//}

	if (state->IsStateChange()) // 키 입력 가능 여부
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

		// 공격 상태로 변환
		if (CKeyMgr::GetInst()->GetKeyState(KEY::G) == KEY_STATE::TAP)
		{
			// 공격 별로 유지 시간 또는 발동 조건 콤보 유무 등이 다르기 때문에 현재 들고 있는 main Weapon 에 따라 다른 코드를 호출한다.
			switch (CWeapon::GetInst()->GetWeaponType())
			{
			case CWeapon::eWeaponType::BigSword :
				break;
			case CWeapon::eWeaponType::Bow :
				break;
			case CWeapon::eWeaponType::Spear :
				break;
			}

			/*if (player->GetMainWeaponType() == CPlayer::eWeapon::BigSword)
			{
				mComboAttackNum++;
			}*/
			state->SetBoolStateChange(false);
			state->SetState(eState::Attack);
		}
	}
}

void CPlayerMoveScript::LateUpdate()
{
}
