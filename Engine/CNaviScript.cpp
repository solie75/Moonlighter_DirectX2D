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
	// �� ����ÿ� Node �� �� ���� �����Ѵ�.
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

			// Node Object ����
			std::wstring NodeIdStr = std::to_wstring(100 * j + i);

			sNode nodeData;
			nodeData.nodePos = NodePos;
			nodeData.IsCollide = false;
			nodeData.id = (UINT)100 * j + i;

			// ���⿡�� ó���� sNode �� �ʱ�ȭ
			mTotalNodeList.insert(std::make_pair((UINT)100 * j + i, nodeData)); // õ�� ���ڸ� -> x  �ʰ� ���ڸ�-> y
		}
	}

	// Back Col �� �浹�� Node �ʱ�ȭ;
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

// ���� ��ü�� ��ġ�� ��� Node ���� �ִ��� �˻�
void CNaviScript::SetStartNode(Vector2 startObjPos)
{
	mStartNodeId = GetNodeId(startObjPos);
}

void CNaviScript::SetGoalNode(Vector2 goalObjPos)
{
	mGoalNodeId = GetNodeId(goalObjPos);
}

void CNaviScript::SetGoalNode(UINT goalObjID)
{
	mGoalNodeId = goalObjID;
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
	// ���� ������ �߰�
	//std::map<UINT, vector<sNode>> mAStarNodeList; //<stepValue, sNode>
	//mAStarNodeList
	// �̹� �߰� �� ��� 
	mAStarNodeList.clear();

	vector<UINT> closedNodeIdList;

	// step 0 �ܰ�
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

	// 1. ���� ����� �����¿� �������� �ϴ� ��带 ����Ʈ�� �߰��Ѵ�. �̶� ��� �浹ü�� �浹 �����̸� �߰����� �ʴ´�.
	 // ���� �Ǵ� ����� �����¿� ��带 �߰��ϴ� �迭
	UINT fourSideNodeCalStandard[4] = { -1, 100, +1, -100 }; // Up, Right, Down, Left ����

	int i = 0;
	for (i; ; i++) // mAStarNodeList ���� �ݺ��� (goalNode �� ������ ������ ä���� ����)
	{
		std::map<UINT, vector<sNode>>::iterator iter = mAStarNodeList.find(i);
		vector<sNode> sNodeList = iter->second;
		for (int k = 0; k < sNodeList.size(); k++) // �� stepValue �� �����ϴ� Node �ݺ��� (k ���� �ܰ迡 �����ϴ� sNode ���� ����� Node �˻�)
		{
			vector<sNode> tempList;
			vector<sNode> fourSideList;
			UINT lowestTotalValue = 1000;

			for (int j = 0; j < 4; j++)
			{
				 // �߰� �Ǵ� ���� �¿� ��� �߿� ���� ���� total�� ���� �� stepValue�� �߰��� �� �ִ�.
				UINT findId = sNodeList[k].id + fourSideNodeCalStandard[j];
				if (IsCollideNode(findId) == false) // �浹���� ���� Node �� ���
				{
					if (std::find(closedNodeIdList.begin(), closedNodeIdList.end(), findId) == closedNodeIdList.end())
					{ // �ش� ��尡 closedNodeIdList �� ���� ���� ���
						sNode node;
						node.id = findId;
						node.ParentNodeId = sNodeList[k].id;
						node.stepValue = i + 1;
						
						int tempHeuristicValue = GetHeuristicValue(findId);
						
						node.heuristicValue = tempHeuristicValue;
						node.total = i + 1 + tempHeuristicValue;

						if (tempHeuristicValue == 0) // �˻��ϴ� ��尡 �������� ��� return���� �Լ��� �����Ѵ�.
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

void CNaviScript::AStarNodeListClear()
{
	mAStarNodeList.clear();
}

bool CNaviScript::IsCollideNode(UINT nodeId)
{
	std::map<UINT, sNode>::iterator iter = mTotalNodeList.find(nodeId);
	/*if (iter != mTotalNodeList.end())
	{
		return iter->second.IsCollide;
	}*/
	return iter->second.IsCollide;
	if(iter == mTotalNodeList.end())
	{ // ã������ NodeId �� ���� ���, true �� ��ȯ�Ͽ� �Ұ����� Node �� ��޵ǰ� �Ѵ�.
		return true;
	}
}

Vector2 CNaviScript::GetMovingDirection(Vector2 curPos)
{
	
	std::map<UINT, sNode>::iterator iterWithWay = mWayNodeList.find(curStepOnMoving);
	std::map<UINT, sNode>::iterator iterWithTotal = mTotalNodeList.find(iterWithWay->second.id);
	Vector2 goalNodePos = iterWithTotal->second.nodePos;

	// ������ ��ü�� ��ġ�� ���� ���� ������ ��ǥ Node �� ����� �� ������ ��ǥ NOde �� ���� ���� �����Ѵ�.
	if (Vector2::Distance(curPos, goalNodePos) < 0.01f)
	{
		iterWithWay = mWayNodeList.find(curStepOnMoving++);
		if (curStepOnMoving == mWayNodeList.size()-1)
		{
			return Vector2(0.0f, 0.0f);
		}
		iterWithTotal = mTotalNodeList.find(iterWithWay->second.id);
		goalNodePos = iterWithTotal->second.nodePos;
	}
	
	//Vector2::Normalize(Vector2(goalNodePos.x - curPos.x, goalNodePos.y - curPos.y));
	Vector2 DirectNormal = Vector2(goalNodePos.x - curPos.x, goalNodePos.y - curPos.y);
	DirectNormal.Normalize();
	return DirectNormal;
}

//UINT CNaviScript::GetNextNode(UINT curNodeId, UINT DestNodeId)
//{
//	UINT NextNodeId;
//
//	return NextNodeId;
//}
