#include "CPlayer.h"
#include "CAnimator.h"
#include "CTimeMgr.h"
#include "CPlayerMoveScript.h"
#include "CCollider2D.h"
#include "CWeapon.h"

CPlayer::CPlayer()
	: mCreatureType(eCreatureType::Player)
{
	mState = new CState();
	mAimSight = new CAimSight();
	this->AddComponent<CPlayerMoveScript>();
	CCollider2D* cd = this->AddComponent<CCollider2D>();
	cd->SetSize(Vector2(0.7f, 0.7f));
}

CPlayer::~CPlayer()
{
}

void CPlayer::Initialize()
{
}

void CPlayer::Update()
{

	CAnimator* at = this->GetComponent<CAnimator>(eComponentType::Animator);
	CTransform* tr = this->GetComponent<CTransform>(eComponentType::Transform);
	CPlayerMoveScript* playerScript = this->GetComponent<CPlayerMoveScript>(eComponentType::Script);

	// Idle 상태일 때
	if (mState->GetCurState() == eState::Idle && mState->GetPrevState() != eState::Idle)
	{
		switch (mAimSight->GetSight())
		{
		case CAimSight::eSight::Left:
			at->PlayAnimation(L"Will_Idle_Left", true);
			break;
		case CAimSight::eSight::Right:
			at->PlayAnimation(L"Will_Idle_Right", true);
			break;
		case CAimSight::eSight::Up:
			at->PlayAnimation(L"Will_Idle_Up", true);
			break;
		case CAimSight::eSight::Down:
			at->PlayAnimation(L"Will_Idle_Down", true);
			break;
		}
		mState->SetState(eState::Idle);
	}

	// Roll
	if (mState->GetCurState() == eState::Roll && mState->GetPrevState() != eState::Roll)
	{
		switch (mAimSight->GetSight())
		{
		case CAimSight::eSight::Left:
			at->PlayAnimation(L"Will_Roll_Left", false);
			break;
		case CAimSight::eSight::Right:
			at->PlayAnimation(L"Will_Roll_Right", false);
			break;
		case CAimSight::eSight::Up:
			at->PlayAnimation(L"Will_Roll_Up", false);
			break;
		case CAimSight::eSight::Down:
			at->PlayAnimation(L"Will_Roll_Down", false);
			break;
		}
		mState->SetState(eState::Roll);
	}

	// Move in Roll
	if (mState->GetCurState() == eState::Roll && mState->GetPrevState() == eState::Roll)
	{
		float time = mState->GetStateTime();
		time += CTimeMgr::GetInst()->GetDeltaTime();
		mState->SetStateTime(time);

		CTransform* tr = this->GetComponent<CTransform>(eComponentType::Transform);
		Vector3 pos = tr->GetPosition();

		switch (mAimSight->GetSight())
		{
		case CAimSight::eSight::Left: // 특정 시간 동안, 특정 거리 만큼, 이동한다.
			pos.x -= (float)(2.0 * CTimeMgr::GetInst()->GetDeltaTime());
			tr->SetPosition(pos);
			break;
		case CAimSight::eSight::Right:
			pos.x += (float)(2.0 * CTimeMgr::GetInst()->GetDeltaTime());
			tr->SetPosition(pos);
			break;
		case CAimSight::eSight::Up:
			pos.y += (float)(2.0 * CTimeMgr::GetInst()->GetDeltaTime());
			tr->SetPosition(pos);
			break;
		case CAimSight::eSight::Down:
			pos.y -= (float)(2.0 * CTimeMgr::GetInst()->GetDeltaTime());
			tr->SetPosition(pos);
			break;
		}

		// Finish Roll
		if (at->GetCurAnimation()->IsComplete() == true)
		{
			mState->SetBoolStateChange(true);
			mState->StateTimeReset();
			mState->SetState(eState::Idle);
		}
	}

	// Walk
	if (mState->GetCurState() == eState::Walk && mState->GetPrevState() != eState::Walk)
	{
		switch (mAimSight->GetSight())
		{
		case CAimSight::eSight::Left:
			at->PlayAnimation(L"Will_Walk_Left", true);
			break;
		case CAimSight::eSight::Right:
			at->PlayAnimation(L"Will_Walk_Right", true);
			break;
		case CAimSight::eSight::Up:
			at->PlayAnimation(L"Will_Walk_Up", true);
			break;
		case CAimSight::eSight::Down:
			at->PlayAnimation(L"Will_Walk_Down", true);
			break;
		}
	}
	
	// Attack
	if (mState->GetCurState() == eState::Attack)
	{
		if (mState->GetPrevState() == eState::Attack)
		{
			if (at->GetCurAnimation()->IsComplete() == true)
			{
				tr->SetScale(Vector3(0.25f, 0.47f, 0.0f));
				mState->SetBoolStateChange(true);
				mState->SetState(eState::Idle);

				if (CWeapon::GetInst()->GetWeaponType() == CWeapon::eWeaponType::BigSword)
				{
					// mComboNum 을 0으로 한다.
					playerScript->ResetComboAttackNum();
				}
			}
			// BigSword 상태에서 현재 애니메이션이 끝나지 않은 상태라면
			else if (CWeapon::GetInst()->GetWeaponType() == CWeapon::eWeaponType::BigSword)
			{
				// curState : Attack ,  PrevState : End 가 되게 한다.
				if (at->GetCurAnimation()->GetAnimationIndex() >= 8 && playerScript->GetComboAttackNum() != 3)
					// 이게 맞나...
				{
					mState->SetState(eState::End);
					mState->SetState(eState::Attack);
				}
			}
		}
		else
		{
			// BigSword
			if (CWeapon::GetInst()->GetWeaponType() == CWeapon::eWeaponType::BigSword)
			{
				std::wstring aniString = L"Will_BigSword";

				// Direction
				switch (mAimSight->GetSight())
				{
				case CAimSight::eSight::Left:
					aniString += L"_Left";
					break;
				case CAimSight::eSight::Right:
					aniString += L"_Right";
					break;
				case CAimSight::eSight::Down:
					aniString += L"_Down";
					break;
				case CAimSight::eSight::Up:
					aniString += L"_Up";
					break;
				}

				// Combo
				CPlayerMoveScript* playerScript = this->GetComponent<CPlayerMoveScript>(eComponentType::Script);
				switch (playerScript->GetComboAttackNum())
				{
				case 1:
					aniString += L"_First";
					break;
				case 2:
					aniString += L"_Second";
					break;
				case 3:
					aniString += L"_Third";
					break;
				}

				at->PlayAnimation(aniString, false);
				tr->SetScale(Vector3(0.35f, 0.5f, 0.0f));
			}

			// Bow
			else if (CWeapon::GetInst()->GetWeaponType() == CWeapon::eWeaponType::Bow)
			{
				std::wstring aniString = L"Will_Bow";

				// Direction
				switch (mAimSight->GetSight())
				{
				case CAimSight::eSight::Left:
					aniString += L"_Left";
					break;
				case CAimSight::eSight::Right:
					aniString += L"_Right";
					break;
				case CAimSight::eSight::Down:
					aniString += L"_Down";
					break;
				case CAimSight::eSight::Up:
					aniString += L"_Up";
					break;
				}

				at->PlayAnimation(aniString, false);
			}

			// Spear
			else if (CWeapon::GetInst()->GetWeaponType() == CWeapon::eWeaponType::Spear)
			{
				std::wstring aniString = L"Will_Spear";

				// Direction
				switch (mAimSight->GetSight())
				{
				case CAimSight::eSight::Left:
					aniString += L"_Left";
					break;
				case CAimSight::eSight::Right:
					aniString += L"_Right";
					break;
				case CAimSight::eSight::Down:
					aniString += L"_Down";
					break;
				case CAimSight::eSight::Up:
					aniString += L"_Up";
					break;
				}

				at->PlayAnimation(aniString, false);
			}

			mState->SetState(eState::Attack);
		}
	}

	CGameObject::Update();
}

void CPlayer::LateUpdate()
{
	CGameObject::LateUpdate();
}

void CPlayer::Render()
{
	CGameObject::Render();
}
