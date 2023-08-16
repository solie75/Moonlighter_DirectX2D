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
	double pi = 3.14159265358979323846;
	Vector2 vec = Vector2(-cos((pi/180.f)*45), -sin((pi / 180.f) * 45));
	vec.Normalize();
	mAimNormal = vec;
	CircleAttackNum = 1;
	RhombusAttackNum = 1;
	TriangleAttackNum = 1;
	CollideCount = 0;
	mAttackState = eAttackState::End;
	time = 0.0f;
}

void CDesertBossScript::Update()
{
	CGameObject* parentObj = this->GetOwner()->GetParentObject();
	if (parentObj->GetState() != CGameObject::eObjectState::Paused)
	{
		return;
	}

	CTransform* tr = this->GetOwner()->GetComponent<CTransform>(eComponentType::Transform);
	Vector3 pos = tr->GetPosition();

	CCollider2D* cd = this->GetOwner()->GetComponent<CCollider2D>(eComponentType::Collider2D);
	//cd->SetOffset(Vector2(pos.x + mAimNormal.x, pos.y + mAimNormal.y));

	if (cd->GetIsCollider())
	{
		mState.SetState(eState::Collide);
		CollideCount++;
	}
	else
	{
		mState.SetState(eState::Idle);
	}

	//double pi = 3.14159265358979323846;
	time += CTimeMgr::GetInst()->GetDeltaTime();
	if (time > 7.f * CircleAttackNum)
	{
		mAttackState = eAttackState::Circle;
		CircleAttackNum++;
	}
	if (time > 9.f * RhombusAttackNum)
	{
		mAttackState = eAttackState::Rhombus;
		RhombusAttackNum++;
	}
	if (time > 11.f * TriangleAttackNum)
	{
		mAttackState = eAttackState::Triangle;
		TriangleAttackNum++;
	}
	

	// boss3 의 상태가 Idle 및 Attack 일 때 움직인다.
	if (mState.GetCurState() == eState::Idle || mState.GetCurState() == eState::Collide)
	{
		pos.x += (float)(mAimNormal.x * 1.5 * CTimeMgr::GetInst()->GetDeltaTime());
		pos.y += (float)(mAimNormal.y * 1.5 * CTimeMgr::GetInst()->GetDeltaTime());
		tr->SetPosition(pos);

		float angle = -acos(mAimNormal.x);
		if (mAimNormal.x == 0 && mAimNormal.y > 0)
		{
			angle *= -1.0f;
		}
		tr->SetRotation(Vector3(0.0f, 0.0f, angle));
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
		if (otherPos.y != 0) 
		{
			mAimNormal.x = otherPos.x - pos.x;
			mAimNormal.y = 0.0f;
			if (otherPos.y > 0) // backgroundup
			{
				tr->SetPosition(Vector3(pos.x, pos.y - 0.06f, pos.z));
			}
			if (otherPos.y < 0)
			{
				tr->SetPosition(Vector3(pos.x, pos.y + 0.06f, pos.z));
			}
		}
		if (otherPos.x != 0)
		{
			mAimNormal.x = 0.0f;
			mAimNormal.y = otherPos.y - pos.y;
			if (otherPos.x > 0) // background right
			{
				tr->SetPosition(Vector3(pos.x - 0.06f, pos.y , pos.z));
			}
			if (otherPos.x < 0)
			{
				tr->SetPosition(Vector3(pos.x + 0.2f, pos.y , pos.z));
			}
		}
		// 여기에 충돌하면 각도를 조금씩 변화시키는 코드 추가할 것

		mAimNormal.Normalize();
	}

	CScript::LateUpdate();
}

void CDesertBossScript::Render()
{
	CScript::Render();
}
