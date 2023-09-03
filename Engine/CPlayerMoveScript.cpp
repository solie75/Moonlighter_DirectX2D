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
	//, bAni(true) // true �϶� �ִϸ��̼� �۵� // false �϶� �ִϸ��̼� ���۵�
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

	// ������ȯ
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

	if (state->IsStateChange()) // Ű �Է� ���� ����
	{
		// ĳ���� ��ġ ��ȭ
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

		// ������ ���·� ��ȯ
		if (CKeyMgr::GetInst()->GetKeyState(KEY::SPACE) == KEY_STATE::TAP)
		{
			state->SetBoolStateChange(false);
			state->SetState(eState::Roll);
		}

		// ���� ���·� ��ȯ
		if (CKeyMgr::GetInst()->GetKeyState(KEY::G) == KEY_STATE::TAP)
		{
			// ���� ���� ���� �ð� �Ǵ� �ߵ� ���� �޺� ���� ���� �ٸ��� ������ ���� ��� �ִ� main Weapon �� ���� �ٸ� �ڵ带 ȣ���Ѵ�.
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
