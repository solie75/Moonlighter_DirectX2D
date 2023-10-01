#include "CPlayer.h"
#include "CAnimator.h"
#include "CTimeMgr.h"
#include "CPlayerMoveScript.h"
#include "CCollider2D.h"
#include "CWeapon.h"

CPlayer::CPlayer()
	: mCreatureType(eCreatureType::Player)
	, mWeaponTypeStr(L"")
	, mSightStr(L"")
{
	mState = new CState();
	mAimSight = new CAimSight();
	this->AddComponent<CPlayerMoveScript>();
	CCollider2D* CDforBackground = this->AddComponent<CCollider2D>();
	CDforBackground->SetCollideType(eCollideType::Background);
	CDforBackground->SetSize(Vector2(0.7f, 0.15f));
	CDforBackground->SetOffset(Vector2(0.f, -0.1f));
	CCollider2D* CDforHit = this->AddComponent<CCollider2D>();
	CDforHit->SetCollideType(eCollideType::Hit);
	CDforHit->SetSize(Vector2(0.7f, 0.7f));
	
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

	// Set String about Sight
	{
		std::wstring str;

		switch (mAimSight->GetSight())
		{
		case CAimSight::eSight::Left:
			str = L"_Left";
			break;
		case CAimSight::eSight::Right:
			str = L"_Right";
			break;
		case CAimSight::eSight::Down:
			str = L"_Down";
			break;
		case CAimSight::eSight::Up:
			str = L"_Up";
			break;
		}

		SetStrAboutState(str);
	}

	// Idle 상태일 때
	if (mState->GetCurState() == eState::Idle && mState->GetPrevState() != eState::Idle)
	{
		playerScript->ResetComboAttackNum();

		std::wstring str = L"Will_Idle";
		str += mSightStr;
		at->PlayAnimation(str, true);
		mState->SetState(eState::Idle);
	}

	// Roll
	if (mState->GetCurState() == eState::Roll && mState->GetPrevState() != eState::Roll)
	{
		std::wstring str = L"Will_Roll";
		str += mSightStr;
		at->PlayAnimation(str, false);
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
		std::wstring str = L"Will_Walk";
		str += mSightStr;
		at->PlayAnimation(str, false);
	}
	
	// Attack
	if (mState->GetCurState() == eState::Attack)
	{
		// Attack Stay
		if (mState->GetPrevState() == eState::Attack)
		{
			if (at->GetCurAnimation()->IsComplete() == true)
			{
				if (mWeapon->GetWeaponType() == CWeapon::eWeaponType::BigSword)
				{
					if (playerScript->GetBoolNextCombo())
					{
						mState->SetState(eState::End);
						mState->SetState(eState::Attack);
					}
					else
					{
						playerScript->ResetComboAttackNum();
						tr->SetScale(Vector3(0.25f, 0.47f, 0.0f));
						mState->SetBoolStateChange(true);
						mState->SetState(eState::Idle);
					}
				}
				else
				{
					tr->SetScale(Vector3(0.25f, 0.47f, 0.0f));
					mState->SetBoolStateChange(true);
					mState->SetState(eState::Idle);
				}
			}
		}

		// Attack Enter
		else
		{
			// BigSword
			if (mWeapon->GetWeaponType() == CWeapon::eWeaponType::BigSword)
			{
				std::wstring aniString = L"Will_BigSword";

				if (playerScript->GetSubAttackState() == CPlayerMoveScript::eSubAttackState::Enter)
				{
					aniString += L"_SubAttack";
					at->PlayAnimation(aniString, false);
					tr->SetScale(Vector3(0.4f, 0.5f, 0.0f));
					CGameObject::Update();
					return;
				}
				else if (playerScript->GetSubAttackState() == CPlayerMoveScript::eSubAttackState::Stay)
				{
					CGameObject::Update();
					return;
				}
				else if (playerScript->GetSubAttackState() == CPlayerMoveScript::eSubAttackState::Exit)
				{
					mState->SetBoolStateChange(true);
					mState->SetState(eState::Idle);
					tr->SetScale(Vector3(0.25f, 0.47f, 0.0f));
					playerScript->SetSubAttackState(CPlayerMoveScript::eSubAttackState::End);
					CGameObject::Update();
					return;
				}

				aniString += mSightStr;

				// Combo
				switch (playerScript->GetComboAttackNum())
				{
				case 1:
					aniString += L"_First";
					mWeapon->SetComboNum(1);
					break;
				case 2:
					aniString += L"_Second";
					mWeapon->SetComboNum(2);
					break;
				case 3:
					aniString += L"_Third";
					mWeapon->SetComboNum(3);
					break;
				}

				at->PlayAnimation(aniString, false);
				playerScript->SetBoolNextCombo(false);
				tr->SetScale(Vector3(0.35f, 0.5f, 0.0f));
				mState->SetState(eState::Attack);
				
			}

			// Bow
			else if (mWeapon->GetWeaponType() == CWeapon::eWeaponType::Bow)
			{
				std::wstring aniString = L"Will_Bow";

				// SubAttack
				if (playerScript->GetSubAttackState() == CPlayerMoveScript::eSubAttackState::End)
				{
					aniString += mSightStr;
					at->PlayAnimation(aniString, false);
					
					mState->SetState(eState::Attack);
					CGameObject::Update();
					return;
				}
				else
				{
					switch (playerScript->GetSubAttackState())
					{
					case CPlayerMoveScript::eSubAttackState::Enter:
						aniString += L"_SubAttack";
						aniString += mSightStr;
						tr->SetScale(Vector3(0.4f, 0.45f, 0.0f));
						at->PlayAnimation(aniString, false);
						break;
					case CPlayerMoveScript::eSubAttackState::Stay:
						break;
					case CPlayerMoveScript::eSubAttackState::Exit:
						mState->SetBoolStateChange(true);
						mState->SetState(eState::Idle);
						tr->SetScale(Vector3(0.25f, 0.47f, 0.0f));
						playerScript->SetSubAttackState(CPlayerMoveScript::eSubAttackState::End);
						break;
					}
				}
			}

			// Spear
			else if (mWeapon->GetWeaponType() == CWeapon::eWeaponType::Spear)
			{
				std::wstring aniString = L"Will_Spear";

				at->PlayAnimation(aniString, false);
				mState->SetState(eState::Attack);
			}
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
