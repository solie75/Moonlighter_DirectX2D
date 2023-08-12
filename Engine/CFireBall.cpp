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
			// �浹 ���¿��� PlayAnimation �� ��� ȣ��� -> �ִϸ��̼��� ù��° �����Ӹ� ��� ����
		}
	}
	
	CGameObject::Update();
}

void CFireBall::LateUpdate()
{
	CGameObject::LateUpdate(); // ���� CFireBall::Update() �� CGameOBject::Update() �� CCollider2D::Update() ���� IsCollider �� true �� �ȴ�.
	CCollider2D* cd = this->GetComponent<CCollider2D>(eComponentType::Collider2D);
	CAnimator* at = this->GetComponent<CAnimator>(eComponentType::Animator);
	if (cd->GetIsCollider() == true)
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
