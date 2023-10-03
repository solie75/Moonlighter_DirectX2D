#include "CLavaBall.h"
#include "CCollider2D.h"
#include "CColliderMgr.h"
#include "CTimeMgr.h"

CLavaBall::CLavaBall()
{
	CColliderMgr* thisCdList = this->AddComponent<CColliderMgr>(eComponentType::ColliderList);
	CCollider2D* thisCDforBackground = new CCollider2D;
	thisCDforBackground->SetCollideType(eCollideType::Background);
	thisCdList->AddCollider(thisCDforBackground);
	CCollider2D* thisCDforHit = new CCollider2D;
	thisCDforHit->SetCollideType(eCollideType::Hit);
	thisCdList->AddCollider(thisCDforHit);

	dropSpeed = 0.0f;
	mLavaState = eLavaState::Ball;
	mPrevLavaState = eLavaState::End;
	splashTime = 0.0;
}

CLavaBall::~CLavaBall()
{
}

void CLavaBall::Initialize()
{
	CGameObject::Initialize();
}

void CLavaBall::Update()
{
	CAnimator* at = this->GetComponent<CAnimator>(eComponentType::Animator);
	CTransform* tr = this->GetComponent<CTransform>(eComponentType::Transform);
	Vector3 pos = tr->GetPosition();
	
	speed = Vector2::Distance(Vector2(pos.x, pos.y), mGoalPos);
	if (mLavaState == eLavaState::Ball) // 하드코딩으로 해놨음 조금도 위로 쏴서 포물선의 형태로 구현해보자
	{
		if (pos.x > mGoalPos.x + 0.7f || pos.x < mGoalPos.x - 0.7f)
		{
			pos.x += ((float)(speed * CTimeMgr::GetInst()->GetDeltaTime())) * mAimNormal.x;
			pos.y += ((float)(speed * CTimeMgr::GetInst()->GetDeltaTime())) * mAimNormal.y;
			tr->SetPosition(pos);
		}
		else
		{
			if (pos.y > mGoalPos.y - 1.5f)
			{
				pos.x += ((float)(speed * CTimeMgr::GetInst()->GetDeltaTime())) * mAimNormal.x;
				dropSpeed += (float)CTimeMgr::GetInst()->GetDeltaTime();
				pos.y -= dropSpeed * ((float)(CTimeMgr::GetInst()->GetDeltaTime()));
			}
			else
			{
				ChangeLavaState(eLavaState::SplashEnter);
				
			}
			tr->SetPosition(pos);
		}
	}

	if (mPrevLavaState == eLavaState::Ball && mLavaState == eLavaState::SplashEnter)
	{
		tr->SetScale(Vector3(0.7f, 0.55f, 0.0f));
		tr->SetPosition(pos.x, pos.y, 1.0f + pos.z);
		at->PlayAnimation(L"Lava_Ball_Splash_Enter", false);
		ChangeLavaState(eLavaState::SplashEnter);
	}

	if (mLavaState == eLavaState::SplashEnter && at->GetCurAnimation()->IsComplete())
	{
		ChangeLavaState(eLavaState::SplashStay);
	}

	if (mPrevLavaState == eLavaState::SplashEnter && mLavaState == eLavaState::SplashStay)
	{
		at->PlayAnimation(L"Lava_Ball_Splash_Stay", true);
		ChangeLavaState(eLavaState::SplashStay);
	}

	if (mLavaState == eLavaState::SplashStay)
	{
		if (splashTime > 4.0f)
		{
			this->SetState(eObjectState::Dead);
		}
		splashTime += (float)CTimeMgr::GetInst()->GetDeltaTime();
	}
	
	CGameObject::Update();
}

void CLavaBall::LateUpdate()
{
	CGameObject::LateUpdate();
}

void CLavaBall::Render()
{
	CGameObject::Render();
}


