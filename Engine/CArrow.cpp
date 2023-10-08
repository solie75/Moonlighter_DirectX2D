#include "CArrow.h"
#include "CTimeMgr.h"
#include "CCollider2D.h"
#include "CColliderMgr.h"
#include "CPlayerMoveScript.h"

CArrow::CArrow(UINT BowType, UINT sight, UINT arrowType)
{
	mBowType = (eBowType)BowType;
	mSight = (CAimSight::eSight)sight;
	speed = 0.0f;
	mArrowType = (eArrowType)arrowType;

	CColliderMgr* CDList = this->AddComponent<CColliderMgr>(eComponentType::ColliderList);
	CCollider2D* CDforBackground = new CCollider2D();
	CDforBackground->SetSize(Vector2(0.07f, 0.32f));
	CDforBackground->SetCollideType(eCollideType::Background);
	CCollider2D* CDforHit = new CCollider2D();
	CDforHit->SetCollideType(eCollideType::Hit);
	CDforHit->SetColliderDamage(50);
	CDforHit->SetSize(Vector2(0.07f, 0.32f));
	CDList->AddCollider(CDforBackground);
	CDList->AddCollider(CDforHit);
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
		break; // 시계방향 으로 90도
	case CAimSight::eSight::Left:
		Tr->SetRotation(Vector3(0.0f, 0.0f, -(pi / 2)));
		direction = Vector3(-1.0f, 0.0f, 0.0f);
		break; // 반시계방향으로 90도
	case CAimSight::eSight::Up:
		Tr->SetRotation(Vector3(0.0f, 0.0f, pi));
		direction = Vector3(0.0f, 1.0f, 0.0f);
		break; // 어디든 180도 
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
		CColliderMgr* cdList = this->GetComponent<CColliderMgr>(eComponentType::ColliderList);
		CCollider2D* CDforBackground = cdList->GetCollider(eCollideType::Background);
		CCollider2D* CDforHit = cdList->GetCollider(eCollideType::Hit);

		
		if (CDforBackground->GetIsCollider() == false && CDforHit->GetIsCollider() == false)
		{
			if (time > speed)
			{
				Vector3 pos = Tr->GetPosition();
				pos.x += direction.x * 0.1;
				pos.y += direction.y * 0.1;
				/*pos.x += direction.x * 0.0f;
				pos.y += direction.y * 0.0f;*/
				Tr->SetPosition(pos);
				time = 0;
			}
		}
		else
		{
			// 화살이 몬스터와 충돌한 경우
			if (CDforHit->GetColliderData(eLayerType::Monster).id != 0)
			{
				if (mArrowType == eArrowType::Main)
				{
					At->PlayAnimation(L"Weapon_Arrow_Hunter_Collide", false);
					this->SetState(eObjectState::Paused);
				}
				else if (mArrowType == eArrowType::SubAttack)
				{
					// arrow 가 SubAttack 일 때 몬스터와 충돌한 경우
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
			// 화살이 배경 벽과 충돌한 경우
			else if (CDforBackground->GetColliderData(eLayerType::Background).id != 0)
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
