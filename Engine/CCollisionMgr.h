#pragma once
#include "Header.h"
#include "Enum.h"
#include "CSingleton.h"
#include "CCollider2D.h"

class CCollisionMgr
	: public CSingleton<CCollisionMgr>
{
private:
	//std::map<UINT64, bool> mCollisionMap;
	// �迭 mMatrix �� eLayerType::End ���� ��Ҹ� ������ �� ��Ҵ� 10���� ��Ʈ�� ���� bitset�̴�.
	std::bitset <(UINT)eLayerType::End> mMatrix[(UINT)eLayerType::End];
	//UINT64 mCollisionID;

public:
	/*struct collisionID
	{
		struct
		{
			UINT Left;
			UINT Right;
		};
		UINT64 CollisionId;
	};*/

	CCollisionMgr();
	~CCollisionMgr();

	void Update();
	void LateUpdate();
	void DecreaseColliderCount(eLayerType leftLayer, eLayerType rightLayer);
	void ObjectCollision(eLayerType leftLayer, eLayerType rightLayer);
	void ColliderCollision(CCollider2D* leftCol, CCollider2D* rightCol);
	bool Intersect(CCollider2D* leftCol, CCollider2D* rightCol);
	void SetCollideLayer(eLayerType leftLayer, eLayerType rightLeyer, bool enable);
	void Clear();
};

//UINT64 CCollisionMgr::mCollisionID = 0;
