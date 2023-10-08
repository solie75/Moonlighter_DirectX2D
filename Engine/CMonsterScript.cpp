    #include "CMonsterScript.h"
#include "CColliderMgr.h"

CMonsterScript::CMonsterScript()
	: mOwner(nullptr)
{
	mState = new CState;
	mState->SetState(eState::End);
	mState->SetState(eState::Pause);
	mAimSight = new CAimSight;
	mAimSight->SetSight(CAimSight::eSight::Down);
	mHitTime = 0.f;
	//mHitColId = 0;
}

CMonsterScript::~CMonsterScript()
{
}

void CMonsterScript::Initialize()
{
	CScript::Initialize();
}

void CMonsterScript::Update()
{
	CCollider2D* HitCol = nullptr;
	
	if (mOwner != nullptr)
	{
		HitCol = mOwner->GetComponent<CColliderMgr>(eComponentType::ColliderList)->GetCollider(eCollideType::Hit);	
	}


	// 몬스터가 플레이어의 투척물에 충돌한 경우
	if (mState->GetCurState() != eState::Hit)
	{
		if (HitCol->GetColliderData(eLayerType::PlayerProjectile).id != 0)
		{
			mState->SetState(eState::Hit);
			if (mState->GetPrevState() != eState::Hit)
			{
				// 몬스터의 hp 에 Damage 적용
				UINT damage = HitCol->GetColliderData(eLayerType::PlayerProjectile).damage;
				mOwner->SetHP(mOwner->GetHP() - damage);
				// AnimationType 을 HitRed 로 한다.
				CAnimation* curAni = mOwner->GetComponent<CAnimator>(eComponentType::Animator)->GetCurAnimation();
				curAni->SetAnimationType(eAnimationType::HitRed);
			}
		}
	}  
	else if (mState->GetCurState() == eState::Hit)
	{
		// 여기에서 시간의 흐름에 따라 AnimationPS.hlsl 에서 쓰일 AnimationType 을 변경한다.
		mHitTime += CTimeMgr::GetDeltaTime();
		CAnimation* curAni = mOwner->GetComponent<CAnimator>(eComponentType::Animator)->GetCurAnimation();
		if (mHitTime > 1.f && curAni->GetAnimationType() != eAnimationType::HitWhite)
		{
			curAni->SetAnimationType(eAnimationType::HitWhite);
		}
		else if (mHitTime > 1.5f && curAni->GetAnimationType() != eAnimationType::HitRed)
		{
			curAni->SetAnimationType(eAnimationType::HitRed);
		}
		else if (mHitTime > 2.0f)
		{
			curAni->SetAnimationType(eAnimationType::Basic);
			mHitTime = 0.f;
			mState->SetState(eState::Idle);
		}
	}
	CScript::Update();
}

void CMonsterScript::LateUpdate()
{
	CScript::LateUpdate();
}
