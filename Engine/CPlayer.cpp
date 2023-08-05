#include "CPlayer.h"
#include "CAnimator.h"
#include "CTimeMgr.h"
#include "CPlayerMoveScript.h"
#include "CCollider2D.h"

CPlayer::CPlayer()
	: mCreatureType(eCreatureType::Player)
{
	mState = new CState();
	mAimSight = new CAimSight();
	this->AddComponent<CPlayerMoveScript>();
	CCollider2D* cd = this->AddComponent<CCollider2D>();
	cd->SetSize(Vector2(0.7f, 0.7f));
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

		// Roll
		if (mState->GetCurState() == eState::Roll && mState->GetPrevState() != eState::Roll)
		{
			switch (mAimSight->GetAimSight())
			{
			case eAimSight::Left:
				at->PlayAnimation(L"Will_Roll_Left", false);
				break;
			case eAimSight::Right:
				at->PlayAnimation(L"Will_Roll_Right", false);
				break;
			case eAimSight::Up:
				at->PlayAnimation(L"Will_Roll_Up", false);
				break;
			case eAimSight::Down:
				at->PlayAnimation(L"Will_Roll_Down", false);
				break;
			}
			mState->SetState(eState::Roll);
		}

		if (mState->GetCurState() == eState::Roll && mState->GetPrevState() == eState::Roll)
		{
			float time = mState->GetStateTime();
			time += CTimeMgr::GetInst()->GetDeltaTime();
			mState->SetStateTime(time);

			CTransform* tr = this->GetComponent<CTransform>(eComponentType::Transform);
			Vector3 pos = tr->GetPosition();

			switch (mAimSight->GetAimSight())
			{
			case eAimSight::Left: // 특정 시간 동안, 특정 거리 만큼, 이동한다.
				pos.x -= (float)(2.0 * CTimeMgr::GetInst()->GetDeltaTime());
				tr->SetPosition(pos);
				break;
			case eAimSight::Right:
				pos.x += (float)(2.0 * CTimeMgr::GetInst()->GetDeltaTime());
				tr->SetPosition(pos);
				break;
			case eAimSight::Up:
				pos.y += (float)(2.0 * CTimeMgr::GetInst()->GetDeltaTime());
				tr->SetPosition(pos);
				break;
			case eAimSight::Down:
				pos.y -= (float)(2.0 * CTimeMgr::GetInst()->GetDeltaTime());
				tr->SetPosition(pos);
				break;
			}

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

		// Attack
		if (mState->GetCurState() == eState::Attack && mState->GetPrevState() != eState::Attack)
		{
			CTransform* tr = this->GetComponent<CTransform>(eComponentType::Transform);

			switch (mAimSight->GetAimSight())
			{
			/*case eAimSight::Left:
				at->PlayAnimation(L"Will_Walk_Left", true);
				break;*/
			case eAimSight::Right:
				at->PlayAnimation(L"will_bow_secondary_animation_right", false);
				tr->SetScale(Vector3(0.45f, 0.65f, 0.0f));
				break;
			/*case eAimSight::Up:
				at->PlayAnimation(L"Will_Walk_Up", true);
				break;*/
			case eAimSight::Down:
				at->PlayAnimation(L"Will_BigSwordCombo_Down", false);
				tr->SetScale(Vector3(1.0f, 1.4f, 0.0f));
				break;
			}
			
			mState->SetState(eState::Attack);
		}

		if (mState->GetCurState() == eState::Attack && mState->GetPrevState() == eState::Attack)
		{
			if (at->GetCurAnimation()->IsComplete() == true)
			{
				CTransform* tr = this->GetComponent<CTransform>(eComponentType::Transform);
				tr->SetScale(Vector3(0.25f, 0.47f, 0.0f));
				mState->SetBoolStateChange(true);
				mState->SetState(eState::Idle);
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
