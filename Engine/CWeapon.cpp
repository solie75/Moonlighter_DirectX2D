#include "CWeapon.h"
#include "CPlayerMoveScript.h"
#include "CCollider2D.h"
#include "CColliderMgr.h"


CWeapon::CWeapon()
	:  mMainWeaponType(eWeaponType::Bow)
	, mBigSwordType(eBigSwordType::Vulcan)
	, mBowType(eBowType::Hunter)
	, mSpearType(eSpearType::End)
	, mComboNum(0)
	, mbArrow(true)
{
	ResetWeaponAniName();
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
	CPlayer* mPlayer = dynamic_cast<CPlayer*>(this->GetParentObject());

	if (this->GetParentObject() != nullptr)
	{
		CAnimator* At = GetComponent<CAnimator>(eComponentType::Animator);
		CTransform* Tr = GetComponent<CTransform>(eComponentType::Transform);
		
		//Vector3 v = Tr->GetPosition();
		CTransform* playerTr = this->GetParentObject()->GetComponent<CTransform>(eComponentType::Transform);
		Vector3 vec = playerTr->GetPosition();
		vec.z -= 0.001f;
		Tr->SetPosition(vec);
		

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

			// 무기 종류가 BigSword 라면 콤보 단계를 추가한다.
			if (mMainWeaponType == eWeaponType::BigSword) 
			{

				// SubAttack
				if (playerScript->GetSubAttackState() == CPlayerMoveScript::eSubAttackState::Enter)
				{
					mAniName += L"_SubAttack";
					At->PlayAnimation(mAniName, false);
					CGameObject::Update();
					return;
				}
				else if (playerScript->GetSubAttackState() == CPlayerMoveScript::eSubAttackState::Exit)
				{
					At->PlayAnimation(L"", false);
					CGameObject::Update();
					return;
				}
				else if (playerScript->GetSubAttackState() == CPlayerMoveScript::eSubAttackState::End)
				{
					mAniName += mPlayer->GetSightStr();

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

				Tr->SetScale(Vector3(1.0f, 1.4f, 0.0f));
				
			}
			else if(mMainWeaponType == eWeaponType::Bow)
			{
				// SubAttack
				if (playerScript->GetSubAttackState() == CPlayerMoveScript::eSubAttackState::Enter)
				{
					mAniName += L"_SubAttack";
					mAniName += mPlayer->GetSightStr();
					Tr->SetScale(Vector3(0.5f, 0.7f, 0.0f));
					At->PlayAnimation(mAniName, false);
					CGameObject::Update();
					return;
				}
				else if (playerScript->GetSubAttackState() == CPlayerMoveScript::eSubAttackState::Stay)
				{
					switch (playerSight->GetSight())
					{
					case CAimSight::eSight::Left:
						vec.x -= 0.1f;
						break;
					case CAimSight::eSight::Right:
						vec.x += 0.1f;
						break;
					case CAimSight::eSight::Down:
						vec.y -= 0.2f;
						break;
					case CAimSight::eSight::Up:
						vec.y += 0.2f;
						break;
					}
					Tr->SetPosition(vec);

					if (At->GetCurAnimation()->GetAnimationIndex() == 18 && mbArrow == true)
					{
						CArrow* arrow = new CArrow((UINT)mBowType, (UINT)playerSight->GetSight(), (UINT)CArrow::eArrowType::SubAttack);
						arrow->SetParentObject(this);
						arrow->SetSpeed(0.01f);

						ownScene->AddGameObject(eLayerType::PlayerProjectile, arrow, L"Arrow", Tr->GetPosition()
							, Vector3(1.0f, 1.0f, 0.0f), true, L"Mesh", L"", true);
						
						//CCollider2D* arrowCd = arrow->AddComponent<CCollider2D>();
						CAnimator* arrowAt = arrow->GetComponent<CAnimator>(eComponentType::Animator);
						arrowAt->PlayAnimation(L"Weapon_Arrow_Hunter_Idle", true);
						mbArrow = false;
					}
					CGameObject::Update();
					return;
				}
				else if (playerScript->GetSubAttackState() == CPlayerMoveScript::eSubAttackState::Exit)
				{
					At->PlayAnimation(L"", false);
					mbArrow = true;
					CGameObject::Update();
					return;
				}
				else if (playerScript->GetSubAttackState() == CPlayerMoveScript::eSubAttackState::End)
				{ // Bow 의 SubAttack 이 아닐 때 -> 일반 공격일 때 
					// Bow 에서 규격 수정
					if (playerSight->GetSight() == CAimSight::eSight::Left)
					{
						vec.x += 0.05f;
						Tr->SetPosition(vec);
					}
					else if (playerSight->GetSight() == CAimSight::eSight::Right)
					{
						vec.x -= 0.05f;
						Tr->SetPosition(vec);
					}

					Tr->SetScale(Vector3(0.5f, 0.7f, 0.0f));
					if (mComboNum == 0)
					{
						mAniName += mPlayer->GetSightStr();
						At->PlayAnimation(mAniName, false); // Weapon:Bow 의 Animation;
						mComboNum += 1;
					}
					else
					{
						if (At->GetCurAnimation()->IsComplete() == true)
						{
							SetComboNum(0);
							mbArrow = true;
						}
						else if(At->GetCurAnimation()->GetAnimationIndex() == 3 && mbArrow == true)
						{ // 한 번의 animation Index 에 두번의 Tick이 된다.
							CArrow* arrow = new CArrow((UINT)mBowType, (UINT)playerSight->GetSight(), (UINT)CArrow::eArrowType::Main);
							arrow->SetParentObject(this);
							arrow->SetSpeed(0.015f);

							ownScene->AddGameObject(eLayerType::PlayerProjectile, arrow, L"Arrow", Tr->GetPosition()
								, Vector3(1.0f, 1.0f, 0.0f), true, L"Mesh", L"", true);

							CTransform* arrowTr = arrow->GetComponent<CTransform>(eComponentType::Transform);
							CAnimator* arrowAt = arrow->GetComponent<CAnimator>(eComponentType::Animator);
							/*CColliderMgr* arrowCdList = arrow->GetComponent<CColliderMgr>(eComponentType::ColliderList);
							CCollider2D* arrowCDforBackground = arrowCdList->GetCollider(eCollideType::Background);

							CCollider2D* arrowCd = arrow->AddComponent<CCollider2D>(eComponentType::ColliderList);*/

							arrowAt->PlayAnimation(L"Weapon_Arrow_Hunter_Idle", true);
							mbArrow = false;
						}
					}

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

