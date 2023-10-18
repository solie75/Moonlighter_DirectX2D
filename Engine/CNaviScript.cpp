#include "CNaviScript.h"
#include "CColliderMgr.h"
#include "CCollisionMgr.h"
#include "CGameObject.h"
#include "CSceneMgr.h"

CNaviScript::CNaviScript()
{
}

CNaviScript::~CNaviScript()
{
}

void CNaviScript::Initialize()
{
	// �� ����ÿ� Node �� �� ���� �����Ѵ�.
	SetNodeList(mObjScaleforDongeonMap, mMapNum);

}

void CNaviScript::Update()
{
	// �� ������Ʈ ����. Node �� ���� �����Ѵ�. 

	/*CColliderMgr* thisColList = GetOwner()->GetComponent<CColliderMgr>(eComponentType::ColliderList);
	CCollider2D* thisColforBackground = thisColList->GetCollider(eCollideType::Background);
	if (thisColforBackground != nullptr)
	{
		Vector2 thisColforBackgroundScale = thisColforBackground->GetSize();
	}*/
	
	//std::map<UINT, sNode>::iterator iter = mNodeList.begin();
	//for (; iter != mNodeList.end(); iter++)
	//{
	//	iter->second.nodeObj->Update();
	//}
}

void CNaviScript::LateUpdate()
{
	//std::map<UINT, sNode>::iterator iter = mNodeList.begin();
	//for (; iter != mNodeList.end(); iter++)
	//{
	//	iter->second.nodeObj->LateUpdate();
	//}
}

void CNaviScript::SetNodeList(Vector2 ObjColSize, UINT mapNum)
{
	UINT NodeNumX = (int)(6.2f / mObjScaleforDongeonMap.x);
	UINT NodeNumY = (int)(3.4f / mObjScaleforDongeonMap.y);
	Vector2 NodeSize = Vector2(6.2f / NodeNumX, 3.4f / NodeNumY);

	//vector<CDungeonMgr::sColliderOnMap> BackColList = CDungeonMgr::GetInst()->GetColliderData(mapNum);

	for (int i =1; i < NodeNumY + 1; i++) //
	{
		float NodePosY = mMapPos.y + 1.7f - (i * NodeSize.y) + (NodeSize.y / 2.0f);
		for (int j = 1; j < NodeNumX + 1; j++)
		{
			float NodePosX = mMapPos.x - 3.1f + (j * NodeSize.x) - (NodeSize.x / 2.0f);
			Vector2 NodePos = Vector2(NodePosX, NodePosY);

			// Node Object ����
			std::wstring NodeIdStr = std::to_wstring(100 * j + i);
			//CGameObject* NodeObject = new CGameObject;
			/*CTransform* NodeObjTr = new CTransform;
			NodeObjTr->SetPosition(Vector3(NodePos.x, NodePos.y, 0.0f));
			NodeObjTr->SetScale(Vector3(NodeSize.x, NodeSize.y, 0.0f));
			NodeObject->AddComponent<CTransform>(eComponentType::Transform);*/
			//CColliderMgr* NodeObjColList = NodeObject->AddComponent<CColliderMgr>(eComponentType::ColliderList);
			/*CCollider2D* NodeObjCol = new CCollider2D;
			NodeObjCol->SetCollideType(eCollideType::Node);
			NodeObjColList->AddCollider(NodeObjCol);*/

			/*CSceneMgr::GetInst()->GetActiveScene()->AddGameObject(eLayerType::Node, NodeObject, L"NodeObject_" + NodeIdStr,
				Vector3(NodePos.x, NodePos.y, 0.0f), Vector3(NodeSize.x, NodeSize.y, 0.0f),
				true, L"Mesh", L"", false);*/

			sNode nodeData;
			//nodeData.nodeObj = NodeObject;
			nodeData.nodePos = NodePos;
			nodeData.IsCollide = false;

			// ���⿡�� ó���� sNode �� �߱�ȭ
			mNodeList.insert(std::make_pair((UINT)100 * j + i, nodeData)); // õ�� ���ڸ� -> x  �ʰ� ���ڸ�-> y
		}
	}

	// mMapPos;
	SetIsCollide(mapNum);
}

void CNaviScript::SetIsCollide(UINT mapNum)
{
	std::map<UINT, sNode>::iterator iter = mNodeList.begin();
	vector<CDungeonMgr::sColliderOnMap> ColliderList = CDungeonMgr::GetInst()->GetColliderData(mapNum);
	for (; iter != mNodeList.end(); iter++)
	{
		for (int i = 0; i < ColliderList.size(); i++)
		{
			Vector2 BackColPos = Vector2(mMapPos.x + ColliderList[i].vColliderPos.x, mMapPos.y + ColliderList[i].vColliderPos.y);
			Vector2 BackColSize = ColliderList[i].vColliderScale;

			Vector2 NodePos = iter->second.nodePos;

			float DiffX = 0.f;
			float DiffY = 0.f;
			if (BackColPos.x > NodePos.x)
			{
				DiffX = BackColPos.x - NodePos.x;
			}
			else
			{
				DiffX = NodePos.x - BackColPos.x;
			}

			if (BackColPos.y > NodePos.y)
			{
				DiffY = BackColPos.y - NodePos.y;
			}
			else
			{
				DiffY = NodePos.y - BackColPos.y;
			}

			if (DiffX < BackColSize.x / 2.f + mNodeSize.x / 2.f && DiffY < BackColSize.y / 2.f + mNodeSize.y / 2.f)
			{
				iter->second.IsCollide = true;
			}
		}
	}


}

void CNaviScript::DeleteNodeCollideWithBackCol(std::vector<CGameObject*> mBackColObj)
{
	//std::map<UINT, sNode>::iterator iter = mNodeList.begin();

	//for (; iter != mNodeList.end(); iter++)
	//{
	//	CCollider2D* iterCdforBack = iterCdMgr->GetCollider(eCollideType::Node);

	//	for (int i = 0; i < mBackColObj.size(); i++)
	//	{
	//		CCollider2D* backCol  =  mBackColObj[i]->GetComponent<CColliderMgr>(eComponentType::ColliderList)->GetCollider(eCollideType::Background);
	//		if (CCollisionMgr::GetInst()->Intersect(iterCdforBack, backCol))
	//		{
	//			iter->second.IsCollide = true;
	//			//a++;
	//		}
	//	}
	//}

	//for (; iter != mNodeList.end(); iter++) {
	//	if (iter->second.IsCollide == true)
	//	{
	//		iter->second.nodeObj->SetState(CGameObject::eObjectState::Dead);
	//	}
	//}
}

Vector2 CNaviScript::GetNextNodePos(Vector2 startObjPos, Vector2 DestObjPos)
{


	return Vector2();
}
