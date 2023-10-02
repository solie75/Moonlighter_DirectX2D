#include "CColliderMgr.h"

CColliderMgr::CColliderMgr()
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
		collider->LateUpdate();
	}
}

void CColliderMgr::Render()
{
	for (CCollider2D* collider : ColliderList)
	{
		collider->Render();
	}
}
