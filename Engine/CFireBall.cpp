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
			// 충돌 상태여서 PlayAnimation 이 계속 호출됨 -> 애니메이션의 첫번째 프레임만 계속 보임
		}
	}

	CGameObject::Update();
}

void CFireBall::LateUpdate()
{
	CGameObject::LateUpdate(); // 위의 CFireBall::Update() 의 CGameOBject::Update() 의 CCollider2D::Update() 에서 IsCollider 가 true 가 된다.
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
		//this->SetState(eObjectState::Dead); // 이후에 CAppDestroy 에서
	}
}

void CFireBall::Render()
{
	CGameObject::Render();
}
