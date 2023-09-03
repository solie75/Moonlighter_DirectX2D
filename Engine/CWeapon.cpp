#include "CWeapon.h"
#include "CPlayer.h"

CWeapon::CWeapon()
	:  mMainWeaponType(eWeaponType::End)
	, mBigSwordType(eBigSwordType::End)
	, mBowType(eBowType::End)
	, mSpearType(eSpearType::End)
{
}

CWeapon::~CWeapon()
{
}

void CWeapon::Initialize()
{
}

void CWeapon::Update()
{
	CPlayer* player = dynamic_cast<CPlayer*>(this->GetParentObject());
	CState* playerState = player->GetState();
	CAimSight* playerSight = player->GetAimSight();

	// 출력할 애니메이션의 이름
	std::wstring aniString = L"Weapon_";

	if (playerState->GetCurState() == eState::Attack)
	{
		switch (mMainWeaponType)
		{
		case eWeaponType::BigSword:
			aniString += L"BigSword";
			break;
		case eWeaponType::Bow:
			aniString += L"Bow";
			break;
		case eWeaponType::Spear:
			aniString += L"Spear";
			break;
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

std::wstring CWeapon::AddWeaponName()
{


	return L"";
}

