#include "CDesertBossScript.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CTransform.h"
#include "CCollider2D.h"
#include "CMonster.h"

CDesertBossScript::CDesertBossScript()

{
}

CDesertBossScript::~CDesertBossScript()
{
}

void CDesertBossScript::Initialize()
{
	CScript::Initialize();
	mAimAngle = 180.f;
	Vector2 vec = Vector2(cos(mAimAngle), sin(mAimAngle));
	vec.Normalize();
	mAimNormal = vec;
}

void CDesertBossScript::Update()
{
	CTransform* tr = this->GetOwner()->GetComponent<CTransform>(eComponentType::Transform);
	Vector3 pos = tr->GetPosition();

	CCollider2D* cd = this->GetOwner()->GetComponent<CCollider2D>(eComponentType::Collider2D);
	if (cd->GetIsCollider())
	{
		mState.SetState(eState::Collide);
	}
	else
	{
		mState.SetState(eState::Idle);
	}

	Vector2 otherPos;

	// boss3 의 상태가 Idle 및 Attack 일 때 움직인다.
	if (mState.GetCurState() == eState::Idle || mState.GetCurState() == eState::Collide)
	{
		pos.x += (float)(mAimNormal.x * 1.5 * CTimeMgr::GetInst()->GetDeltaTime());
		pos.y += (float)(mAimNormal.y * 1.5 * CTimeMgr::GetInst()->GetDeltaTime());
		tr->SetPosition(pos);
	}

	CScript::Update();
}

void CDesertBossScript::LateUpdate()
{
	CTransform* tr = this->GetOwner()->GetComponent<CTransform>(eComponentType::Transform);
	Vector3 pos = tr->GetPosition();
	CCollider2D* cd = this->GetOwner()->GetComponent<CCollider2D>(eComponentType::Collider2D);
	Vector2 otherPos;
	if (mState.GetPrevState() != eState::Collide && mState.GetCurState() == eState::Collide)
	{
		otherPos = cd->GetColliderData(eLayerType::Background).pos;
		if (otherPos.y != 0) // backgroundup
		{
			mAimNormal.y = 0.0f;
			mAimNormal.x = otherPos.x - pos.x;
			if (otherPos.y > 0)
			{
				tr->SetPosition(Vector3(pos.x, pos.y - 0.04f, pos.z));
				
			}
			if (otherPos.y < 0)
			{
				tr->SetPosition(Vector3(pos.x, pos.y + 0.04f, pos.z));
			}
		}
		if (otherPos.x != 0)
		{
			mAimNormal.x = 0.0f;
			mAimNormal.y = otherPos.y - pos.y;
			if (otherPos.x > 0)
			{
				tr->SetPosition(Vector3(pos.x - 0.04f, pos.y , pos.z));
			}
			if (otherPos.x < 0)
			{
				tr->SetPosition(Vector3(pos.x + 0.04f, pos.y , pos.z));
			}
		}
		mAimNormal.Normalize();
	}

	CScript::LateUpdate();
}

void CDesertBossScript::Render()
{
	CScript::Render();
}
