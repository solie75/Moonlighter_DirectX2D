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


	// ���Ͱ� �÷��̾��� ��ô���� �浹�� ���
	if (mState->GetCurState() != eState::Hit)
	{
		if (HitCol->GetColliderData(eLayerType::PlayerProjectile).id != 0)
		{
			mState->SetState(eState::Hit);
			if (mState->GetPrevState() != eState::Hit)
			{
				// ������ hp �� Damage ����
				UINT damage = HitCol->GetColliderData(eLayerType::PlayerProjectile).damage;
				mOwner->SetHP(mOwner->GetHP() - damage);
				// AnimationType �� HitRed �� �Ѵ�.
				CAnimation* curAni = mOwner->GetComponent<CAnimator>(eComponentType::Animator)->GetCurAnimation();
				curAni->SetAnimationType(eAnimationType::HitRed);
			}
		}
	}
	else if (mState->GetCurState() == eState::Hit)
	{
		// ���⿡�� �ð��� �帧�� ���� AnimationPS.hlsl ���� ���� AnimationType �� �����Ѵ�.
		mHitTime += CTimeMgr::GetDeltaTime();
		CAnimation* curAni = mOwner->GetComponent<CAnimator>(eComponentType::Animator)->GetCurAnimation();
		if (mHitTime > 0.2f && curAni->GetAnimationType() != eAnimationType::HitWhite)
		{
			curAni->SetAnimationType(eAnimationType::HitWhite);
		}
		else if (mHitTime > 0.4f && curAni->GetAnimationType() != eAnimationType::HitRed)
		{
			curAni->SetAnimationType(eAnimationType::HitRed);
		}
		else if (mHitTime > 0.6)
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
