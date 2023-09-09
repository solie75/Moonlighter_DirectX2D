#include "CWeapon.h"
#include "CPlayerMoveScript.h"


CWeapon::CWeapon()
	:  mMainWeaponType(eWeaponType::BigSword)
	, mBigSwordType(eBigSwordType::Vulcan)
	, mBowType(eBowType::End)
	, mSpearType(eSpearType::End)
	, mComboNum(0)
{
	ResetWeaponAniName();
	mPlayer = nullptr;
}

CWeapon::~CWeapon()
{
}

void CWeapon::Initialize()
{
	CGameObject::Initialize();
}

void CWeapon::Update()
{
	if (mPlayer != nullptr)
	{
		CAnimator* At = GetComponent<CAnimator>(eComponentType::Animator);
		CTransform* Tr = GetComponent<CTransform>(eComponentType::Transform);
		
		//Vector3 v = Tr->GetPosition();
		CTransform* playerTr = mPlayer->GetComponent<CTransform>(eComponentType::Transform);
		Vector3 vec = playerTr->GetPosition();
		vec.z -= 0.001f;
		Tr->SetPosition(vec);
		Tr->SetScale(Vector3(1.0f, 1.4f, 0.0f));

		CState* playerState = mPlayer->GetState();
		CAimSight* playerSight = mPlayer->GetAimSight();
		CPlayerMoveScript* playerScript = mPlayer->GetComponent<CPlayerMoveScript>(eComponentType::Script);

		mAniName = L"Weapon";

		if (playerState->GetCurState() == eState::Attack)
		{
			// 무기 종류별 (이중 스위치)
			switch (mMainWeaponType)
			{
			case eWeaponType::BigSword:
				mAniName += L"_BigSword";
				switch (mBigSwordType)
				{
				case eBigSwordType::Vulcan:
					mAniName += L"_Vulcan";
					break;
				case eBigSwordType::Storm:
					mAniName += L"_Storm";
					break;
				case eBigSwordType::Blaze:
					mAniName += L"_Blaze";
					break;
				case eBigSwordType::Wild:
					mAniName += L"_Wild";
					break;
				}
				break;
			case eWeaponType::Bow:
				mAniName += L"_Bow";
				switch (mBowType)
				{
				case eBowType::Hunter:
					mAniName += L"_Hunter";
					break;
				case eBowType::Soldier:
					mAniName += L"_Soldier";
					break;
				case eBowType::Poison:
					mAniName += L"_Poison";
					break;
				case eBowType::FlameThrower:
					mAniName += L"_FlameThrower";
					break;
				}
				break;
			case eWeaponType::Spear:
				mAniName += L"_Spear";
				switch (mSpearType)
				{
				case eSpearType::Warrior:
					mAniName += L"_Warrior";
					break;
				case eSpearType::Fighter:
					mAniName += L"_Fighter";
					break;
				case eSpearType::Venom:
					mAniName += L"_Venom";
					break;
				case eSpearType::Hell:
					mAniName += L"_Hell";
					break;
				}
				break;
			}

			// subAttack
			if (playerScript->GetSubAttackState() == CPlayerMoveScript::eSubAttackState::Enter)
			{
				mAniName += L"_SubAttack";
				At->PlayAnimation(mAniName, false);
				return;
			}
			else if(playerScript->GetSubAttackState() == CPlayerMoveScript::eSubAttackState::Exit)
			{
				At->PlayAnimation(L"", false);
				return;
			}

			// 방향
			switch (playerSight->GetSight())
			{
			case CAimSight::eSight::Down :
				mAniName += L"_Down";
				break;
			case CAimSight::eSight::Left :
				mAniName += L"_Left";
				break;
			case CAimSight::eSight::Right :
				mAniName += L"_Right";
				break;
			case CAimSight::eSight::Up:
				mAniName += L"_Up";
				break;
			}


			// 무기 종류가 BigSword 라면 콤보 단계를 추가한다.
			if (mMainWeaponType == eWeaponType::BigSword)
			{
				switch (mComboNum)
				{
				case 1:
					mAniName += L"_First";
					At->PlayAnimation(mAniName, false);
					mComboNum = 0;
					break;
				case 2:
					mAniName += L"_Second";
					At->PlayAnimation(mAniName, false);
					mComboNum = 0;
					break;
				case 3:
					mAniName += L"_Third";
					At->PlayAnimation(mAniName, false);
					mComboNum = 0;
					break;
				}
			}
		}
		else // 공격상태가 아닐 때
		{
			At->PlayAnimation(L"", false);
		}
	}
	CGameObject::Update();
}

void CWeapon::LateUpdate()
{
	CGameObject::LateUpdate();
}

void CWeapon::Render()
{
	CGameObject::Render();
}

void CWeapon::SetBigSwordType()
{
	if (mBigSwordType != eBigSwordType::End)
	{
		mBigSwordType = (eBigSwordType)((UINT)mBigSwordType + 1);
	}
}

void CWeapon::SetBowType()
{
	if (mBowType != eBowType::End)
	{
		mBowType = (eBowType)((UINT)mBowType + 1);
	}
}

void CWeapon::SetSpearType()
{
	if (mSpearType != eSpearType::End)
	{
		mSpearType = (eSpearType)((UINT)mSpearType + 1);
	}
}

void CWeapon::ResetUpgrade(eWeaponType type)
{
	// 이때의 무기는 모두 기본 상태로 돌아간다. 현재 기본 무기를 임의로 지정.
	switch (type)
	{
	case eWeaponType::BigSword :
		mBigSwordType = eBigSwordType::Vulcan;
		break;
	case eWeaponType::Bow :
		mBowType = eBowType::Hunter;
		break;
	case eWeaponType::Spear :
		mSpearType = eSpearType::Warrior;
		break;
	}
}

