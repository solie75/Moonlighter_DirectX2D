#include "CWeapon.h"
#include "CPlayer.h"

CWeapon::CWeapon()
	:  mMainWeaponType(eWeaponType::End)
	, mBigSwordType(eBigSwordType::End)
	, mBowType(eBowType::End)
	, mSpearType(eSpearType::End)
{
	ResetWeaponAniName();
}

CWeapon::~CWeapon()
{
}

void CWeapon::Initialize()
{
}

void CWeapon::Update()
{
	CState* playerState = mOwner->GetState();
	CAimSight* playerSight = mOwner->GetAimSight();

	if (playerState->GetCurState() == eState::Attack)
	{
		// ���� ������ (���� ����ġ)
		switch (mMainWeaponType)
		{
		case eWeaponType::BigSword :
			mAniName += L"_BigSword";
			switch (mBigSwordType)
			{
			case eBigSwordType::Vulcan :
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
		case eWeaponType::Bow :
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
		case eWeaponType::Spear :
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

		// ����
		switch (playerSight->GetSight())
		{
		case CAimSight::eSight::Down :
			mAniName += L"_Down";
		case CAimSight::eSight::Left :
			mAniName += L"_Left";
		case CAimSight::eSight::Right:
			mAniName += L"_Right";
		case CAimSight::eSight::Up:
			mAniName += L"_Up";
		}


		// ���� ������ BigSword ��� �޺� �ܰ踦 �߰��Ѵ�.
		if (mMainWeaponType == eWeaponType::BigSword)
		{
			player->
		}









		switch (playerSight->GetSight())
		{
		case CAimSight::eSight::Down :
			aniString += L""
		}
	}

}

void CWeapon::LateUpdate()
{
}

void CWeapon::Render()
{
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
	// �̶��� ����� ��� �⺻ ���·� ���ư���. ���� �⺻ ���⸦ ���Ƿ� ����.
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

