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
	mHP = 1000;
}

void CDesertBossScript::Update()
{
	CGameObject* parentObj = this->GetOwner()->GetParentObject();
	CTransform* tr = this->GetOwner()->GetComponent<CTransform>(eComponentType::Transform);
	CCollider2D* cd = this->GetOwner()->GetComponent<CCollider2D>(eComponentType::Collider2D);
	Vector3 pos = tr->GetPosition();

	if (mHP <= 0)
	{
		this->GetOwner()->SetState(CGameObject::eObjectState::Dead);
	}

	if (parentObj->GetState() != CGameObject::eObjectState::Paused)
	{
		return;
	}

	// ���� Parts Attack ���� �� ��
	if(mAttackState == eAttackState::Parts)
	{
		PartsAttackTime += CTimeMgr::GetInst()->GetDeltaTime();

		// Parts Attack Enter �� 10.f ���� �ٽ� �������
		if (PartsAttackTime > 10.f)
		{
			PartsAttackTime = 0.0f;
			mAttackState = eAttackState::End;
			mState.SetState(eState::Idle);
			CircleAttackNum = 0;
			RhombusAttackNum = 0;
			TriangleAttackNum = 0;
			speed = 1.5f;
			FireAttackTime = 0.0f;
		}
	}
	else
	{
		// Parts Attack ���°� �ƴ� �� �����δ�.
		pos.x += (float)(mAimNormal.x * speed * CTimeMgr::GetInst()->GetDeltaTime());
		pos.y += (float)(mAimNormal.y * speed * CTimeMgr::GetInst()->GetDeltaTime());
		tr->SetPosition(pos);

		// �浹ü�� ���� ��ü�� Aim ���� �տ� �д�.
		cd->SetOffset(Vector2(mAimNormal.x * (1.5f), mAimNormal.y * (1.5f)));

		// ���� Head �� �浹 ���� ���
		if (cd->GetIsCollider())
		{
			// ��� �� �� �浹�Ͽ��� ���
			if (cd->GetColliderData(eLayerType::Background).id != 0) 
			{
				mState.SetState(eState::Turn);
			}

			// �浹 �ߴµ� �浹 ���� �߿� ��� �浹ü�� ���� ���
			if (mState.GetCurState() != eState::Turn)
			{ 
				mState.SetState(eState::Collide);
			}
		}

		FireAttackTime += CTimeMgr::GetInst()->GetDeltaTime();
	}
	
	// ���� ����
	if (FireAttackTime > 5.f * CircleAttackNum)
	{
		mAttackState = eAttackState::Circle;
		CircleAttackNum++;
	}
	if (FireAttackTime > 8.f * RhombusAttackNum)
	{
		mAttackState = eAttackState::Rhombus;
		RhombusAttackNum++;
	}
	if (FireAttackTime > 12.f * TriangleAttackNum)
	{
		mAttackState = eAttackState::Triangle;
		TriangleAttackNum++;
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
		DecreaseHP(1);
		//DecreaseHP(cd->GetColliderData(eLayerType::Player).damage);
	}

	// Turn ���°� �Ǿ� ���� ���� ���͸� �����Ѵ�.
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

	// ��� �浹ü���� �浹�� 6�� �� �� ������ ���� ���ͷ� �����Ѵ�.
	if (TurnCount >= 6 && mState.GetCurState() != eState::Attack)
	{
		mExpectedAimNormal = Vector2(-pos.x, -pos.y);
		speed = 0.3f;
		if (fabs(pos.x) < 0.1f)
		{
			// Head �� ������ ������ Attack ���·� ����� Parts Attack �� �����Ѵ�.
			mState.SetState(eState::Attack);
			FireAttackTime = 0.0f;
			TurnCount = 0;
			mAimNormal.Normalize();
		}
	}

	// ���� ���� ���Ϳ� ���� ���� ���Ͱ��� ��
	mDiffAimNormal.x = mExpectedAimNormal.x - mAimNormal.x;
	mDiffAimNormal.y = mExpectedAimNormal.y - mAimNormal.y;

	// �� ƽ�� ������ ���� ������ ��ȭ��, ����� ������ ���� ������ ���� ���� ���ϸ� Idle �� ���� ��ȭ
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

	// �̹����� ȸ��
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
		// Parts Attack ���� �ִϸ��̼� ����
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

		// Parts Animation �� ������ �κ��� 29 ��° �����ӿ��� AttackState �� Parts �� �����Ѵ�.
		if (at->GetCurAnimation()->GetAnimationIndex() == 29)
		{
			mAttackState = eAttackState::Parts;
		}
	}
	else
	{
		// ���� �ٶ󺸰� �ִ� ���⿡ ���� �̹��� ��ȯ
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

	// ��ȯ�� �̹����� ���� ��ȭ
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

void CDesertBossScript::DecreaseHP(UINT value)
{
	mHP -= value;
}