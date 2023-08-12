#include "CFireBall.h"
#include "CTimeMgr.h"
#include "CCollider2D.h"

CFireBall::CFireBall()
	: speed(3.0f)
{
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
	if (this->GetState() != CGameObject::eObjectState::Paused)
	{
		CTransform* tr = this->GetComponent<CTransform>(eComponentType::Transform);
		CCollider2D* cd = this->GetComponent<CCollider2D>(eComponentType::Collider2D);
		CAnimator* at = this->GetComponent<CAnimator>(eComponentType::Animator);
		if (cd->GetIsCollider() == false)
		{
			Vector3 pos = tr->GetPosition();
			pos.x += ((float)(speed * CTimeMgr::GetInst()->GetDeltaTime())) * direction.x;
			pos.y += ((float)(speed * CTimeMgr::GetInst()->GetDeltaTime())) * direction.y;
			tr->SetPosition(pos);
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
	CCollider2D* cd = this->GetComponent<CCollider2D>(eComponentType::Collider2D);
	CAnimator* at = this->GetComponent<CAnimator>(eComponentType::Animator);
	if (cd->GetIsCollider() == true)
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
