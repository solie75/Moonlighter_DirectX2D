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
	cd->SetOffset(Vector2(mAimNormal.x * (1.5f), mAimNormal.y * (1.5f))); // �浹ü�� aim ���� �տ��� �д�. �̶� ����� �Ÿ�

	

	if (cd->GetIsCollider())
	{
		CCollider2D::ColliderData df = cd->GetColliderData(eLayerType::Background);
		if (cd->GetColliderData(eLayerType::Background).id != -1) // ��� �� �� �浹�Ͽ��� ���
		{
			mState.SetState(eState::Turn);
		}

		if (mState.GetCurState() != eState::Turn)
		{ // �浹 �ߴµ� �浹 ���� �߿� ��� �浹ü�� ���� ���
			mState.SetState(eState::Collide);
		}
	}

	if (mAttackState != eAttackState::Parts)
	{
		// ���� ������ Parts �� ��쿡�� �ٸ� ���������� �����.
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


	// boss3 �� ���°� Idle �� Turn�� �� �����δ�.
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

	// ��� �浹ü���� �浹�� 2�� �� �� ������ ���� ���ͷ� �����Ѵ�.
	if (TurnCount >= 2)
	{
		mExpectedAimNormal = Vector2(-pos.x, -pos.y);
		speed = 0.3f;
		if (fabs(pos.x) < 0.1f)
		{
			mState.SetState(eState::Attack);
			
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
		if (mAttackState == eAttackState::Parts)
		{
			PartsAttackTime += CTimeMgr::GetInst()->GetDeltaTime();
		}
		
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
