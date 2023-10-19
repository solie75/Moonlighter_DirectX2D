#include "CNaviScript.h"
#include "CColliderMgr.h"
#include "CCollisionMgr.h"
#include "CGameObject.h"
#include "CSceneMgr.h"
#include <queue>

CNaviScript::CNaviScript()
{
	curStepOnMoving = 0;
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
}

void CNaviScript::LateUpdate()
{
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

			sNode nodeData;
			nodeData.nodePos = NodePos;
			nodeData.IsCollide = false;
			nodeData.id = (UINT)100 * j + i;

			// 여기에서 처음의 sNode 를 초기화
			mTotalNodeList.insert(std::make_pair((UINT)100 * j + i, nodeData)); // 천과 백자리 -> x  십과 일자리-> y
		}
	}

	// Back Col 과 충돌한 Node 초기화;
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

			if (DiffX < BackColSize.x / 2.f + mObjScaleforDongeonMap.x / 2.f && DiffY < BackColSize.y / 2.f + mObjScaleforDongeonMap.y / 2.f)
			{
				iter->second.IsCollide = true;
			}
		}
	}
}

// 현재 객체의 위치가 어는 Node 위에 있는지 검색
void CNaviScript::SetStartNode(Vector2 startObjPos)
{
	mStartNodeId = GetNodeId(startObjPos);
}

void CNaviScript::SetGoalNode(Vector2 goalObjPos)
{
	mGoalNodeId = GetNodeId(goalObjPos);
}

UINT CNaviScript::GetNodeId(Vector2 NodePos)
{
	std::map<UINT, sNode>::iterator iter = mTotalNodeList.begin();
	float firstNodeLeftPos = iter->second.nodePos.x - mObjScaleforDongeonMap.x / 2.0f;
	float firstNodeUpPos = iter->second.nodePos.y + mObjScaleforDongeonMap.y / 2.0f;

	UINT NodeNumBitweenMapLeftAndStartObj = (NodePos.x - firstNodeLeftPos) / mObjScaleforDongeonMap.x;
	UINT NodeNumBitweenMapUpAndstartObj = (firstNodeUpPos - NodePos.y) / mObjScaleforDongeonMap.y;

	return NodeNumBitweenMapLeftAndStartObj * 100 + NodeNumBitweenMapUpAndstartObj;
}

UINT CNaviScript::GetHeuristicValue(UINT StartId)
{
	int DiffX = std::abs((int)(StartId / 100) - (int)(mGoalNodeId / 100));
	int DiffY = std::abs((int)(StartId % 100) - (int)(mGoalNodeId % 100));

	return DiffX + DiffY;
}

void CNaviScript::SetAroundNodeList(UINT NodeId)
{

}

UINT CNaviScript::SetWayNodeList()
{
	// 시작 지점을 추가
	//std::map<UINT, vector<sNode>> mAStarNodeList; //<stepValue, sNode>
	//mAStarNodeList
	// 이미 추가 된 경우 
	mAStarNodeList.clear();

	vector<UINT> closedNodeIdList;

	// step 0 단계
	vector<sNode> firstStepNodeList;
	sNode startNode;
	startNode.id = mStartNodeId;
	startNode.IsCollide = false;
	startNode.ParentNodeId = 0;
	startNode.stepValue = 0;
	startNode.heuristicValue = GetHeuristicValue(mStartNodeId);
	startNode.total = GetHeuristicValue(mStartNodeId);
	firstStepNodeList.push_back(startNode);
	mAStarNodeList.insert(std::make_pair(0, firstStepNodeList));

	closedNodeIdList.push_back(startNode.id);

	// 1. 기준 노드의 상하좌우 방향존재 하는 노드를 리스트에 추가한다. 이때 배경 충돌체와 충돌 상태이면 추가하지 않는다.
	 // 기준 되는 노드의 상하좌우 노드를 추가하는 배열
	UINT fourSideNodeCalStandard[4] = { -1, 100, +1, -100 }; // Up, Right, Down, Left 순서

	int i = 0;
	for (i; ; i++) // mAStarNodeList 기준 반복문 (goalNode 에 도달할 때까지 채워질 것임)
	{
		std::map<UINT, vector<sNode>>::iterator iter = mAStarNodeList.find(i);
		vector<sNode> sNodeList = iter->second;
		for (int k = 0; k < sNodeList.size(); k++) // 각 stepValue 별 존재하는 Node 반복문 (k 번재 단계에 존재하는 sNode 들의 사방향 Node 검사)
		{
			vector<sNode> tempList;
			vector<sNode> fourSideList;
			UINT lowestTotalValue = 1000;

			for (int j = 0; j < 4; j++)
			{
				 // 추가 되는 상하 좌우 노드 중에 가장 작은 total값 만이 각 stepValue에 추가될 수 있다.
				UINT findId = sNodeList[k].id + fourSideNodeCalStandard[j];
				if (IsCollideNode(findId) == false) // 충돌하지 않은 Node 의 경우
				{
					if (std::find(closedNodeIdList.begin(), closedNodeIdList.end(), findId) == closedNodeIdList.end())
					{ // 해당 노드가 closedNodeIdList 에 있지 않은 경우
						sNode node;
						node.id = findId;
						node.ParentNodeId = sNodeList[k].id;
						node.stepValue = i + 1;
						
						int tempHeuristicValue = GetHeuristicValue(findId);
						
						node.heuristicValue = tempHeuristicValue;
						node.total = i + 1 + tempHeuristicValue;

						if (tempHeuristicValue == 0) // 검사하는 노드가 도착지인 경우 return으로 함수를 종료한다.
						{
							tempList.push_back(node);
							mAStarNodeList.insert(std::make_pair(i + 1, tempList));
							i++;
							return i;
						}

						if (lowestTotalValue > node.total)
						{
							lowestTotalValue = node.total;
						}

						fourSideList.push_back(node);
					}
				}
			}

			for (int p = 0; p < fourSideList.size(); p++)
			{
				if (fourSideList[p].total == lowestTotalValue)
				{
					tempList.push_back(fourSideList[p]);
					closedNodeIdList.push_back(fourSideList[p].id);
				}
			}
			mAStarNodeList.insert(std::make_pair(i + 1, tempList));
		}
	}
 
}

void CNaviScript::SetAStarNodeList(UINT stepNum)
{
	int i = stepNum;
	std::map<UINT, vector<sNode>>::iterator iter = mAStarNodeList.find(i);
	mWayNodeList.insert(std::make_pair(i, iter->second[0]));
	int parentId = iter->second[0].ParentNodeId;
	i--;

	for (; i > -1; i--)
	{
		iter = mAStarNodeList.find(i);
		for (int j = 0; j < iter->second.size(); j++)
		{
			if (iter->second[j].id == parentId)
			{
				mWayNodeList.insert(std::make_pair(i, iter->second[j]));
				parentId = iter->second[j].ParentNodeId;
				break;
			}
		}
	}
}


void CNaviScript::WayNodeListClear()
{
	mWayNodeList.clear();
}

bool CNaviScript::IsCollideNode(UINT nodeId)
{
	std::map<UINT, sNode>::iterator iter = mTotalNodeList.find(nodeId);
	if (iter != mTotalNodeList.end())
	{
		return iter->second.IsCollide;
	}
	else
	{ // 찾으려는 NodeId 가 없는 경우, true 를 반환하여 불가능한 Node 로 취급되게 한다.
		return true;
	}
}

Vector2 CNaviScript::GetMovingDirection(Vector2 curPos)
{
	std::map<UINT, sNode>::iterator iterWithWay = mWayNodeList.find(curStepOnMoving);
	std::map<UINT, sNode>::iterator iterWithTotal = mTotalNodeList.find(iterWithWay->second.id);
	
	Vector2 goalNodePos = iterWithTotal->second.nodePos;
	Vector2::Normalize(Vector2(goalNodePos.x - curPos.x, goalNodePos.y - curPos.y));
	return Vector2();
}

//UINT CNaviScript::GetNextNode(UINT curNodeId, UINT DestNodeId)
//{
//	UINT NextNodeId;
//
//	return NextNodeId;
//}
