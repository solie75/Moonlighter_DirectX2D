#include "CArrow.h"
#include "CTimeMgr.h"
#include "CCollider2D.h"
#include "CPlayerMoveScript.h"


CArrow::CArrow(UINT BowType, UINT sight, UINT arrowType)
{
	mBowType = (eBowType)BowType;
	mSight = (CAimSight::eSight)sight;
	speed = 0.0f;
	mArrowType = (eArrowType)arrowType;
}
  
CArrow::~CArrow()
{
}

void CArrow::Initialize()
{
	CGameObject::Initialize();
}

void CArrow::Update()
{
	time += CTimeMgr::GetInst()->GetDeltaTime();

	CTransform* Tr = this->GetComponent<CTransform>(eComponentType::Transform);
	CAnimator* At = this->GetComponent<CAnimator>(eComponentType::Animator);
	Tr->SetScale(Vector3(0.08f, 0.3f, 0.0f));
	double pi = 3.14159265358979323846;

	switch (mSight)
	{
	case CAimSight::eSight::Down :
		direction = Vector3(0.0f, -1.0f, 0.0f);
		break;
	case CAimSight::eSight::Right:
		Tr->SetRotation(Vector3(0.0f, 0.0f, pi/2));
		direction = Vector3(1.0f, 0.0f, 0.0f);
		break; // �ð���� ���� 90��
	case CAimSight::eSight::Left:
		Tr->SetRotation(Vector3(0.0f, 0.0f, -(pi / 2)));
		direction = Vector3(-1.0f, 0.0f, 0.0f);
		break; // �ݽð�������� 90��
	case CAimSight::eSight::Up:
		Tr->SetRotation(Vector3(0.0f, 0.0f, pi));
		direction = Vector3(0.0f, 1.0f, 0.0f);
		break; // ���� 180�� 
	}

	CPlayer* player = dynamic_cast<CPlayer*>(this->GetParentObject()->GetParentObject());
	CAnimator* playerAt = player->GetComponent<CAnimator>(eComponentType::Animator);
	CPlayerMoveScript* playerScript = player->GetComponent<CPlayerMoveScript>(eComponentType::Script);
	
	/*if (playerScript->GetSubAttackState() == CPlayerMoveScript::eSubAttackState::Stay)
	{
		player
	}*/


	if (this->GetState() != CGameObject::eObjectState::Paused)
	{
		CCollider2D* cd = this->GetComponent<CCollider2D>(eComponentType::Collider2D);
		
		if (cd->GetIsCollider() == false)
		{
			if (time > speed)
			{
				Vector3 pos = Tr->GetPosition();
				pos.x += direction.x * 0.1;
				pos.y += direction.y * 0.1;
				Tr->SetPosition(pos);
				time = 0;
			}
		}
		else
		{
			// ȭ���� ���Ϳ� �浹�� ���
			if (cd->GetColliderData(eLayerType::Monster).id != 0)
			{
				if (mArrowType == eArrowType::Main)
				{
					At->PlayAnimation(L"Weapon_Arrow_Hunter_Collide", false);
					this->SetState(eObjectState::Paused);
				}
				else if (mArrowType == eArrowType::SubAttack)
				{
					// arrow �� SubAttack �� �� ���Ϳ� �浹�� ���
					if (time > speed)
					{
						Vector3 pos = Tr->GetPosition();
						pos.x += direction.x * 0.1;
						pos.y += direction.y * 0.1;
						Tr->SetPosition(pos);
						time = 0;
					}
				}
			}
			// ȭ���� ��� ���� �浹�� ���
			else if (cd->GetColliderData(eLayerType::Background).id != 0)
			{
				At->PlayAnimation(L"Weapon_Arrow_Hunter_Collide", false);
				this->SetState(eObjectState::Paused);
			}
		}
	}
	else if(this->GetState() == CGameObject::eObjectState::Paused)
	{
		if (At->GetCurAnimation()->IsComplete() == true)
		{
			this->SetState(eObjectState::Dead);
		}
	}

	CGameObject::Update();
}

void CArrow::LateUpdate()
{
	CGameObject::LateUpdate();
}

void CArrow::Render()
{
	CGameObject::Render();
}