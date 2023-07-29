#pragma once
#include "Header.h"
#include "Enum.h"
#include "CSingleton.h"
#include "CCollider2D.h"

class CCollisionMgr
	: public CSingleton<CCollisionMgr>
{
private:
	std::map<UINT64, bool> mCollisionMap;
	// 배열 mMatrix 는 eLayerType::End 개의 요소를 가지며 각 요소는 10개의 비트를 가진 bitset이다.
	std::bitset <(UINT)eLayerType::End> mMatrix[(UINT)eLayerType::End];
	
public:
	struct collisionID
	{
		struct
		{
			UINT Left;
			UINT Right;
		};
		UINT64 CollisionId;
	};

	CCollisionMgr();
	~CCollisionMgr();

	void Update();
	void ObjectCollision(eLayerType leftLayer, eLayerType rightLayer);
	void ColliderCollision(CCollider2D* leftCol, CCollider2D* rightCol);
	bool Intersect(CCollider2D* leftCol, CCollider2D* right);
};



