#include "CPlayer.h"
#include "CAnimator.h"

CPlayer::CPlayer()
	: mCreatureType(eCreatureType::Player)
{
	mState = new CState();
	mAimSight = new CAimSight();
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

	// Idle 상태일 때
	if (mState->GetCurState() == eState::Idle && mState->GetPrevState() != eState::Idle)
	{
		switch (mAimSight->GetAimSight())
		{
		case eAimSight::Left:
			at->PlayAnimation(L"Will_Idle_Left", true);
			break;
		case eAimSight::Right:
			at->PlayAnimation(L"Will_Idle_Right", true);
			break;
		case eAimSight::Up:
			at->PlayAnimation(L"Will_Idle_Up", true);
			break;
		case eAimSight::Down:
			at->PlayAnimation(L"Will_Idle_Down", true);
			break;
		}
		mState->SetState(eState::Idle);
	}

	if (mState->GetCurState() == eState::Roll && mState->GetPrevState() != eState::Roll)
	{
		switch (mAimSight->GetAimSight())
		{
		case eAimSight::Left:
			at->PlayAnimation(L"Will_Roll_Left", true);
			break;
		case eAimSight::Right:
			at->PlayAnimation(L"Will_Roll_Right", true);
			break;
		case eAimSight::Up:
			at->PlayAnimation(L"Will_Roll_Up", true);
			break;
		case eAimSight::Down:
			at->PlayAnimation(L"Will_Roll_Down", true);
			break;
		}
	}

	if (mState->GetCurState() == eState::Walk && mState->GetPrevState() != eState::Walk)
	{
		switch (mAimSight->GetAimSight())
		{
		case eAimSight::Left:
			at->PlayAnimation(L"Will_Walk_Left", true);
			break;
		case eAimSight::Right:
			at->PlayAnimation(L"Will_Walk_Right", true);
			break;
		case eAimSight::Up:
			at->PlayAnimation(L"Will_Walk_Up", true);
			break;
		case eAimSight::Down:
			at->PlayAnimation(L"Will_Walk_Down", true);
			break;
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
