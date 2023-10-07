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
	if (HitCol->GetColliderData(eLayerType::PlayerProjectile).id != 0)
	{
		mState->SetState(eState::Hit);
	}

	CScript::Update();
}

void CMonsterScript::LateUpdate()
{
	CScript::LateUpdate();
}
