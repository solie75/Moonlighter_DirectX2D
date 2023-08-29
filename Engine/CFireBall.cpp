#include "CFireBall.h"
#include "CTimeMgr.h"
#include "CCollider2D.h"

CFireBall::CFireBall()
	: speed(7.0f)
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
	time += CTimeMgr::GetInst()->GetDeltaTime();

	if (this->GetState() != CGameObject::eObjectState::Paused)
	{
		CTransform* tr = this->GetComponent<CTransform>(eComponentType::Transform);
		CCollider2D* cd = this->GetComponent<CCollider2D>(eComponentType::Collider2D);
		CAnimator* at = this->GetComponent<CAnimator>(eComponentType::Animator);
		if (cd->GetIsCollider() == false)
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
