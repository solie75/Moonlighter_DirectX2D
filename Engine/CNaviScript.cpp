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
	// 맵 변경시에 Node 는 한 번만 변경한다.
	SetNodeList(mObjScaleforDongeonMap, mMapNum);

}

void CNaviScript::Update()
{
	// 매 업데이트 마다. Node 를 새로 생성한다. 

	/*CColliderMgr* thisColList = GetOwner()->GetComponent<CColliderMgr>(eComponentType::ColliderList);
	CCollider2D* thisColforBackground = thisColList->GetCollider(eCollideType::Background);
	if (thisColforBackground != nullptr)
	{
		Vector2 thisColforBackgroundScale = thisColforBackground->GetSize();
	}*/
	
	//std::map<UINT, sNode>::iterator iter = mTotalNodeList.begin();
	//for (; iter != mTotalNodeList.end(); iter++)
	//{
	//	iter->second.nodeObj->Update();
	//}
}

void CNaviScript::LateUpdate()
{
	//std::map<UINT, sNode>::iterator iter = mTotalNodeList.begin();
	//for (; iter != mTotalNodeList.end(); iter++)
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

			// Node Object 생성
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

			// 여기에서 처음의 sNode 를 초기화
			mTotalNodeList.insert(std::make_pair((UINT)100 * j + i, nodeData)); // 천과 백자리 -> x  십과 일자리-> y
		}
	}

	// mMapPos;
	SetIsCollide(mapNum);
}

void CNaviScript::SetIsCollide(UINT mapNum)
{
	std::map<UINT, sNode>::iterator iter = mTotalNodeList.begin();
	vector<CDungeonMgr::sColliderOnMap> ColliderList = CDungeonMgr::GetInst()->GetColliderData(mapNum);
	for (; iter != mTotalNodeList.end(); iter++)
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

// 현재 객체의 위치가 어는 Node 위에 있는지 검색
void CNaviScript::SetNodeIdOnThisObj(Vector2 startObjPos)
{
	//Vector2 PosBasedOn = Vector2(startObjPos.x - mMapPos.x, startObjPos.y - mMapPos.y);
	std::map<UINT, sNode>::iterator iter = mTotalNodeList.begin();
	float firstNodeLeftPos = iter->second.nodePos.x - mNodeSize.x/2.0f;
	float firstNodeUpPos = iter->second.nodePos.y + mNodeSize.y/2.0f;

	UINT NodeNumBitweenMapLeftAndStartObj = (startObjPos.x - firstNodeLeftPos) / mNodeSize.x;
	UINT NodeNumBitweenMapUpAndstartObj = (firstNodeUpPos - startObjPos.y) / mNodeSize.y;

	mCurNodeId = NodeNumBitweenMapLeftAndStartObj * 10 + NodeNumBitweenMapUpAndstartObj;
}

void CNaviScript::SetAroundNodeList(UINT NodeId)
{

}

void CNaviScript::SetWayNodeList()
{
	GetNextNode();
}

void CNaviScript::WayNodeListClear()
{
	mWayNodeList.clear();
}

UINT CNaviScript::GetNextNode(UINT curNodeId, UINT DestNodeId)
{
	UINT NextNodeId;

	return NextNodeId;
}
