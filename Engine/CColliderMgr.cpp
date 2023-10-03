#include "CColliderMgr.h"

CColliderMgr::CColliderMgr()
	: CComponent(eComponentType::ColliderList)
{
}

CColliderMgr::~CColliderMgr()
{
}

void CColliderMgr::Initialize()
{
}

void CColliderMgr::Update()
{
	for (CCollider2D* collider : ColliderList)
	{
		collider->Update();
	}
}

void CColliderMgr::LateUpdate()
{
	for (CCollider2D* collider : ColliderList)
	{
		collider->LateUpdate(this->GetOwner()->GetComponent<CTransform>(eComponentType::Transform));
	}
}

void CColliderMgr::Render()
{
	for (CCollider2D* collider : ColliderList)
	{
		collider->Render();
	}
}
