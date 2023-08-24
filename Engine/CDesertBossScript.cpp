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
	FireAttackTime = 0.0f;
	PartsAttackTime = 0.0f;
	mDiffAimNormal = mAimNormal;
	speed = 1.5f;
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

	if (mAttackState != eAttackState::Parts)
	{
		// 공격 패턴이 Parts 인 경우에는 다른 공격패턴을 멈춘다.
		FireAttackTime += CTimeMgr::GetInst()->GetDeltaTime();
	}
	
	if (FireAttackTime > 7.f * CircleAttackNum)
	{
		mAttackState = eAttackState::Circle;
		CircleAttackNum++;
	}
	if (FireAttackTime > 9.f * RhombusAttackNum)
	{
		mAttackState = eAttackState::Rhombus;
		RhombusAttackNum++;
	}
	if (FireAttackTime > 11.f * TriangleAttackNum)
	{
		mAttackState = eAttackState::Triangle;
		TriangleAttackNum++;
	}


	// boss3 의 상태가 Idle 및 Turn일 때 움직인다.
	if (mState.GetCurState() == eState::Idle || mState.GetCurState() == eState::Turn)
	{
		pos.x += (float)(mAimNormal.x * speed * CTimeMgr::GetInst()->GetDeltaTime());
		pos.y += (float)(mAimNormal.y * speed * CTimeMgr::GetInst()->GetDeltaTime());
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

	// Turn 상태가 되어 예상 방향 벡터를 설정한다.
	if (mState.GetPrevState() != eState::Turn && mState.GetCurState() == eState::Turn)
	{
		TurnCount++;
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

		mState.SetState(eState::Turn);
	}

	// 배경 충돌체와의 충돌이 2번 일 때 원점을 예상 벡터로 설정한다.
	if (TurnCount >= 2)
	{
		mExpectedAimNormal = Vector2(-pos.x, -pos.y);
		speed = 0.3f;
		if (fabs(pos.x) < 0.1f)
		{
			mState.SetState(eState::Attack);
			
		}
	}


	// 예상 방향 벡터와 현재 방향 벡터간의 차
	mDiffAimNormal.x = mExpectedAimNormal.x - mAimNormal.x;
	mDiffAimNormal.y = mExpectedAimNormal.y - mAimNormal.y;

	// 한 틱에 적용할 방향 벡터의 변화량, 예상과 현재의 방향 벡터의 차가 일정 이하면 Idle 로 상태 변화
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

	// 이미지의 회전
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
	float Degree = DirectX::XMConvertToDegrees(angle);

	CAnimator* at = this->GetOwner()->GetComponent<CAnimator>(eComponentType::Animator);

	if (mState.GetCurState() == eState::Attack)
	{
		if (mAttackState == eAttackState::Parts)
		{
			PartsAttackTime += CTimeMgr::GetInst()->GetDeltaTime();
		}
		
		// Parts Attack 공격 애니메이션 시작
		if (mState.GetPrevState() != eState::Attack)
		{
			//time = 0.0f;
			if (Degree > 45 && Degree <= 135)
			{
				at->PlayAnimation(L"Boss3_Head_PartsAttack_Down", false);
			}
			if (Degree > 135 && Degree <= 225)
			{
				at->PlayAnimation(L"Boss3_Head_PartsAttack_Left", false);
			}
			if (Degree > 225 && Degree <= 315)
			{
				at->PlayAnimation(L"Boss3_Head_PartsAttack_Up", false);
			}
			if (Degree > 315 || Degree <= 45)
			{
				at->PlayAnimation(L"Boss3_Head_PartsAttack_Right", false);
			}
			mState.SetState(eState::Attack);
		}

		// Parts Animation 이 터지는 부분인 29 번째 프레임에서 AttackState 를 Parts 로 변경한다.
		if (at->GetCurAnimation()->GetAnimationIndex() == 29)
		{
			mAttackState = eAttackState::Parts;
		}
	}
	else
	{
		// 현재 바라보고 있는 방향에 따라 이미지 변환
		CMeshRender* Mr = this->GetOwner()->GetComponent<CMeshRender>(eComponentType::MeshRender);
		if (Degree > 45 && Degree <= 135)
		{
			at->PlayAnimation(L"Boss3_Head_Down", false);
		}
		if (Degree > 135 && Degree <= 225)
		{
			at->PlayAnimation(L"Boss3_Head_Left", false);
		}
		if (Degree > 225 && Degree <= 315)
		{
			at->PlayAnimation(L"Boss3_Head_Up", false);
		}
		if (Degree > 315 || Degree <= 45)
		{
			at->PlayAnimation(L"Boss3_Head_Right", false);
		}
	}

	// 변환한 이미지의 각도 변화
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
