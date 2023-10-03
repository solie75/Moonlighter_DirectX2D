#include "CFireBall.h"
#include "CTimeMgr.h"
#include "CCollider2D.h"
#include "CColliderMgr.h"

CFireBall::CFireBall()
	: speed(7.0f)
{
	CColliderMgr* CDList = this->AddComponent<CColliderMgr>(eComponentType::ColliderList);
	CCollider2D* CDforBackground = new CCollider2D();
	CDforBackground->SetCollideType(eCollideType::Background);
	CDforBackground->SetSize(Vector2(0.5f, 0.5f));
	CCollider2D* CDforHit = new CCollider2D();
	CDforHit->SetCollideType(eCollideType::Hit);
	CDList->AddCollider(CDforBackground);
	CDList->AddCollider(CDforHit);
}

CFireBall::~CFireBall()
{
}

void CFireBall::Initialize()
{
	CGameObject::Initialize();
}

void CFireBall::Update()
{
	time += CTimeMgr::GetInst()->GetDeltaTime();

	if (this->GetState() != CGameObject::eObjectState::Paused)
	{
		CTransform* tr = this->GetComponent<CTransform>(eComponentType::Transform);
		/*CCollider2D* cd = this->GetComponent<CCollider2D>(eComponentType::Collider2D);*/
		CColliderMgr* CdList = this->GetComponent<CColliderMgr>(eComponentType::ColliderList);
		CCollider2D* CDforBackground = CdList->GetCollider(eCollideType::Background);
		CCollider2D* CDforHit = CdList->GetCollider(eCollideType::Hit);
		CAnimator* at = this->GetComponent<CAnimator>(eComponentType::Animator);
		if (CDforBackground->GetIsCollider() == false && CDforHit->GetIsCollider() == false)
		{
			if (time > 0.005f)
			{
				Vector3 pos = tr->GetPosition();
				pos.x += direction.x * 0.1;
				pos.y += direction.y * 0.1;
				tr->SetPosition(pos);
				time = 0;
			}

		}
		else
		{
			at->PlayAnimation(L"Fire_Ball_Explosion", false);
			this->SetState(eObjectState::Paused);
			// �浹 ���¿��� PlayAnimation �� ��� ȣ��� -> �ִϸ��̼��� ù��° �����Ӹ� ��� ����
		}
	}

	CGameObject::Update();
}

void CFireBall::LateUpdate()
{
	CGameObject::LateUpdate(); // ���� CFireBall::Update() �� CGameOBject::Update() �� CCollider2D::Update() ���� IsCollider �� true �� �ȴ�.
	//CCollider2D* cd = this->GetComponent<CCollider2D>(eComponentType::Collider2D);
	CColliderMgr* CdList = this->GetComponent<CColliderMgr>(eComponentType::ColliderList);
	CCollider2D* CDforBackground = CdList->GetCollider(eCollideType::Background);
	CCollider2D* CDforHit = CdList->GetCollider(eCollideType::Hit);
	CAnimator* at = this->GetComponent<CAnimator>(eComponentType::Animator);
	if (CDforBackground->GetIsCollider() == true || CDforHit->GetIsCollider() == true)
	{
		if (at->GetCurAnimation()->IsComplete() == true)
		{
			this->SetState(eObjectState::Dead);
		}
		//this->SetState(eObjectState::Dead); // ���Ŀ� CAppDestroy ����
	}
}

void CFireBall::Render()
{
	CGameObject::Render();
}
