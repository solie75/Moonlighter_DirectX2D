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
	AttackCount = 1;
	CollideCount = 0;
	mCurAttackState = eAttackState::End;
	mPrevAttackState = eAttackState::End;
	FireAttackTime = 0.0f;
	PartsAttackTime = 0.0f;
	mDiffAimNormal = mAimNormal;
	speed = 1.5f;
}

void CDesertBossScript::Update()
{
	if (CKeyMgr::GetInst()->GetKeyState(KEY::Z) == KEY_STATE::TAP)
	{
		GetOwner()->SetHP(GetOwner()->GetHP() - 100);
	}


	CGameObject* parentObj = this->GetOwner()->GetParentObject();
	CTransform* tr = this->GetOwner()->GetComponent<CTransform>(eComponentType::Transform);
	CCollider2D* cd = this->GetOwner()->GetComponent<CCollider2D>(eComponentType::Collider2D);
	Vector3 pos = tr->GetPosition();

	if (GetOwner()->GetHP() <= 0)
	{
		this->GetOwner()->SetState(CGameObject::eObjectState::Dead);
	}

	if (parentObj->GetState() != CGameObject::eObjectState::Paused)
	{
		return;
	}

	// 현재 Parts Attack 상태 일 때
	if(mCurAttackState == eAttackState::Parts)
	{
		PartsAttackTime += CTimeMgr::GetInst()->GetDeltaTime();

		// Parts Attack Enter 의 10.f 이후 다시 원래대로
		if (PartsAttackTime > 10.f)
		{
			PartsAttackTime = 0.0f;
			ChangeCurAttackState(eAttackState::End);
			mState.SetState(eState::Idle);
			AttackCount = 0;
			speed = 1.5f;
			FireAttackTime = 0.0f;
		}
	}
	else
	{
		// Parts Attack 상태가 아닐 때 움직인다.
		pos.x += (float)(mAimNormal.x * speed * CTimeMgr::GetInst()->GetDeltaTime());
		pos.y += (float)(mAimNormal.y * speed * CTimeMgr::GetInst()->GetDeltaTime());
		tr->SetPosition(pos);

		// 충돌체를 실제 객체의 Aim 기준 앞에 둔다.
		cd->SetOffset(Vector2(mAimNormal.x * (1.5f), mAimNormal.y * (1.5f)));

		// 현재 Head 가 충돌 중인 경우
		if (cd->GetIsCollider())
		{
			// 배경 벽 과 충돌하였을 경우
			if (cd->GetColliderData(eLayerType::Background).id != 0) 
			{
				mState.SetState(eState::Turn);
			}

			// 충돌 했는데 충돌 대상들 중에 배경 충돌체가 없는 경우
			if (mState.GetCurState() != eState::Turn)
			{ 
				mState.SetState(eState::Collide);
			}
		}

		FireAttackTime += CTimeMgr::GetInst()->GetDeltaTime();
	}

	if (FireAttackTime > 5.f * AttackCount)
	{
		switch (mCurAttackState)
		{
		case eAttackState::End :
			ChangeCurAttackState(eAttackState::Circle);
			AttackCount++;
			break;
		case eAttackState::Circle:
			ChangeCurAttackState(eAttackState::Rhombus);
			AttackCount++;
			break;
		case eAttackState::Rhombus:
			ChangeCurAttackState(eAttackState::Triangle);
			AttackCount++;
			break;
		case eAttackState::Triangle:
			ChangeCurAttackState(eAttackState::End);
			AttackCount++;
			break;
		}
	}


	CScript::Update();
}

void CDesertBossScript::LateUpdate()
{
	CTransform* tr = this->GetOwner()->GetComponent<CTransform>(eComponentType::Transform);
	Vector3 pos = tr->GetPosition();
	CCollider2D* cd = this->GetOwner()->GetComponent<CCollider2D>(eComponentType::Collider2D);
	Vector2 otherPos;

	if (0 != cd->GetColliderData(eLayerType::Player).id)
	{
		//DecreaseHP(1);
		//DecreaseHP(cd->GetColliderData(eLayerType::Player).damage);
	}

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

	// 배경 충돌체와의 충돌이 6번 일 때 원점을 예상 벡터로 설정한다.
	if (TurnCount >= 6 && mState.GetCurState() != eState::Attack)
	{
		mExpectedAimNormal = Vector2(-pos.x, -pos.y);
		speed = 0.3f;
		if (fabs(pos.x) < 0.1f)
		{
			// Head 가 원점에 가까우면 Attack 상태로 만들어 Parts Attack 을 시작한다.
			mState.SetState(eState::Attack);
			FireAttackTime = 0.0f;
			TurnCount = 0;
			mAimNormal.Normalize();
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
			mCurAttackState = eAttackState::Parts;
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

//void CDesertBossScript::DecreaseHP(UINT value)
//{
//	mHP -= value;
//}