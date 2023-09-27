#include "CkatamariScript.h"
#include "CGameObject.h"

CkatamariScript::CkatamariScript()
{
	mAimSight = new CAimSight;
	mState = new CState;
	mState->SetState(eState::Pause);
	mState->SetState(eState::Pause);
	mAimSight->SetSight(CAimSight::eSight::Down);
}

CkatamariScript::~CkatamariScript()
{
}

void CkatamariScript::Initialize()
{
}

void CkatamariScript::Update()
{
	CAnimator* thisAt = this->GetOwner()->GetComponent<CAnimator>(eComponentType::Animator);
	CCollider2D* thisCD = this->GetOwner()->GetComponent<CCollider2D>(eComponentType::Collider2D);
	std::wstring aniName = L"Monster_Katamari_Attack_";

	switch (mAimSight->GetSight())
	{
	case CAimSight::eSight::Down :
		aniName += L"Down_";
		break;
	case CAimSight::eSight::Right :
		aniName += L"Right_";
		break;
	case CAimSight::eSight::Left :
		aniName += L"Left_";
		break;
	case CAimSight::eSight::Up :
		aniName += L"Up_";
		break;
	}

	if (mState->GetCurState() == eState::Idle && mState->GetPrevState() == eState::Pause)
	{
		aniName += L"First";
		thisAt->PlayAnimation(aniName, false);
	}
	if (mState->GetCurState() == eState::Idle && thisAt->GetCurAnimation()->IsComplete() == true)
	{
		mState->SetState(eState::Attack);
		aniName += L"Second";
		thisAt->PlayAnimation(aniName, true);
	}

	if (thisCD->GetColliderData(eLayerType::Background).id != 0 && mState->GetCurState() == eState::Attack)
	{
		mState->SetState(eState::Pause);
		aniName += L"Third";
		thisAt->PlayAnimation(aniName, false);
	}
}

void CkatamariScript::LateUpdate()
{
}
