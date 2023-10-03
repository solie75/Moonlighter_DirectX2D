#pragma once
#include "Header.h"
#include "Enum.h"
#include "CSingleton.h"
#include "CCollider2D.h"
#include "CColliderMgr.h"

class CCollisionMgr
	: public CSingleton<CCollisionMgr>
{
private:
	//std::map<UINT64, bool> mCollisionMap;
	// 배열 mMatrix 는 eLayerType::End 개의 요소를 가지며 각 요소는 10개의 비트를 가진 bitset이다.
	std::bitset <(UINT)eLayerType::End> mMatrix[(UINT)eLayerType::End];
	//UINT64 mCollisionID;

public:
	CCollisionMgr();
	~CCollisionMgr();

	void Update();
	void LateUpdate();
	void DecreaseDeadObject(eLayerType leftLayer, eLayerType rightLayer);
	void ObjectCollision(eLayerType leftLayer, eLayerType rightLayer);
	void ColliderListCollision(CColliderMgr* leftColList, CColliderMgr* rightColList);
	void ColliderCollision(CCollider2D* leftCol, CCollider2D* rightCol);
	bool Intersect(CCollider2D* leftCol, CCollider2D* rightCol);
	void SetCollideLayer(eLayerType leftLayer, eLayerType rightLeyer, bool enable);
	void Clear();
};

//UINT64 CCollisionMgr::mCollisionID = 0;
