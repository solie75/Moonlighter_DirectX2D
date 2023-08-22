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
	Vector2 vec = Vector2(0.0f, -1.0f);
	vec.Normalize();
	mAimNormal = vec;
	CircleAttackNum = 1;
	RhombusAttackNum = 1;
	TriangleAttackNum = 1;
	CollideCount = 0;
	mAttackState = eAttackState::End;
	time = 0.0f;
	mDiffAimNormal = mAimNormal;
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
	cd->SetOffset(Vector2(mAimNormal.x * (1.5f), mAimNormal.y * (1.5f))); // 충돌체를 aim 기준 앞에다 둔다. 이때 상수는 거리

	if (cd->GetIsCollider())
	{
		CCollider2D::ColliderData df = cd->GetColliderData(eLayerType::Background);
		if (cd->GetColliderData(eLayerType::Background).id != -1) // 배경 벽 과 충돌하였을 경우
		{
			mState.SetState(eState::Turn);
		}

		if (mState.GetCurState() != eState::Turn)
		{ // 충돌 했는데 충돌 대상들 중에 배경 충돌체가 없는 경우
			mState.SetState(eState::Collide);
		}
	}

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
	if (mState.GetCurState() == eState::Idle || mState.GetCurState() == eState::Turn)
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
	
	if (mState.GetPrevState() != eState::Turn && mState.GetCurState() == eState::Turn)
	{
		 
		otherPos = cd->GetColliderData(eLayerType::Background).pos;
		 if (otherPos.y != 0)
		{
			mExpectedAimNormal.x = otherPos.x - pos.x;
			mExpectedAimNormal.y = 0.0f;
		}
		if (otherPos.x != 0)
		{
			mExpectedAimNormal.x = 0.0f;
			mExpectedAimNormal.y = otherPos.y - pos.y;
		}
		mExpectedAimNormal.Normalize();

		mDiffAimNormal.x = mExpectedAimNormal.x - mAimNormal.x;
		mDiffAimNormal.y = mExpectedAimNormal.y - mAimNormal.y;
		mState.SetState(eState::Turn);
	}

	if (mState.GetCurState() == eState::Turn)
	{
		if (fabs(mExpectedAimNormal.x - mAimNormal.x) > 0.01f)
		{
			mAimNormal.x += mDiffAimNormal.x / 30;
			mAimNormal.y += mDiffAimNormal.y / 30;
		}
		else
		{
			mState.SetState(eState::Idle);
		}
	}
	double pi = 3.14159265358979323846;
	float a, b;
	a = mAimNormal.x;
	b = mAimNormal.y;
	if (mAimNormal.y < 0)
	{
		b *= -1;
	}

	float c = sqrt(pow(a, 2) + pow(b, 2));
	float angle = acosf(a / c);
	if (mAimNormal.y < 0)
	{
		angle = 2 * pi - angle;
	}
	tr->SetRotation(Vector3(0.0f, 0.0f, angle));
	CScript::LateUpdate();
}

void CDesertBossScript::Render()
{
	CScript::Render();
}
