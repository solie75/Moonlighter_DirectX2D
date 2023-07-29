#include "CCollisionMgr.h"
#include "CGameObject.h"


CCollisionMgr::CCollisionMgr()
{
}

CCollisionMgr::~CCollisionMgr()
{
}

void CCollisionMgr::Update()
{
	for (UINT column = 0; column < (UINT)eLayerType::End; column++)
	{
		for (UINT row = 0; row < (UINT)eLayerType::End; row++)
		{
			if (mMatrix[column][row] == true)
			{
				ObjectCollision((eLayerType)column, (eLayerType)row);
			}
		}
	}
}

void CCollisionMgr::ObjectCollision(eLayerType leftLayer, eLayerType rightLayer)
{
	const std::vector<CGameObject*>& lefts = 
		CSceneMgr::GetInst()->GetActiveScene()->GetLayer(leftLayer).GetGameObjects();

	const std::vector<CGameObject*>& rights =
		CSceneMgr::GetInst()->GetActiveScene()->GetLayer(rightLayer).GetGameObjects();

	for (CGameObject* leftObj : lefts)
	{
		CCollider2D* leftCol = leftObj->GetComponent<CCollider2D>(eComponentType::Collider2D);

		if (leftCol == nullptr || leftObj->GetState() != CGameObject::eState::Active)
		{
			continue;
		}

		for (CGameObject* rightObj : rights)
		{
			CCollider2D* rightCol = rightObj->GetComponent<CCollider2D>(eComponentType::Collider2D);
			if (leftObj == rightObj)
			{
				continue;
			}
			if (rightCol == nullptr || rightObj->GetState() != CGameObject::eState::Active);
			{
				continue;
			}

			ColliderCollision(leftCol, rightCol);
		}
	}
}

void CCollisionMgr::ColliderCollision(CCollider2D* leftCol, CCollider2D* rightCol)
{
	collisionID colID = {};
	colID.Left = leftCol->GetColliderID();
	colID.Right = rightCol->GetColliderID();

	// 충돌 정보
	std::map<UINT64, bool>::iterator iter = mCollisionMap.find(colID.CollisionId);
	if (iter == mCollisionMap.end())
	{
		mCollisionMap.insert(std::make_pair(colID.CollisionId, false));
		iter = mCollisionMap.find(colID.CollisionId);
	}

	if (Intersect(leftCol, rightCol));
}

bool CCollisionMgr::Intersect(CCollider2D* leftCol, CCollider2D* right)
{
	return false;
	Vector3 arrLocalPos[4] =
	{
		Vector3(-0.5f, 0.5f, 0.0f),
		Vector3(0.5f, 0.5f, 0.0f),
		Vector3(0.5f, -0.5f, 0.0f),
		Vector3(-0.5f, -0.5f, 0.0f)
	};

	
}
