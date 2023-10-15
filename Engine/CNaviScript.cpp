#include "CNaviScript.h"
#include "CColliderMgr.h"
//#include "CCollisionMgr.h"
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

	CColliderMgr* thisColList = GetOwner()->GetComponent<CColliderMgr>(eComponentType::ColliderList);
	CCollider2D* thisColforBackground = thisColList->GetCollider(eCollideType::Background);
	if (thisColforBackground != nullptr)
	{
		Vector2 thisColforBackgroundScale = thisColforBackground->GetSize();
		/*mCurScene->Get
		SetNodeList(thisColforBackgroundScale, )*/
	}
	
}

void CNaviScript::LateUpdate()
{
	
}

void CNaviScript::SetNodeList(Vector2 ObjColSize, UINT mapNum)
{
	//Vector2 objUnitPos = Vector2(ObjColSize.x / 2.0f, ObjColSize.y / 2.0f);
	//Vector2 NodeNum = Vector2(6.2f / mObjScaleforDongeonMap.x, 3.4f / mObjScaleforDongeonMap.y);
	UINT NodeNumX = (int)(6.2f / mObjScaleforDongeonMap.x);
	UINT NodeNumY = (int)(3.4f / mObjScaleforDongeonMap.y);
	Vector2 NodeSize = Vector2(6.2f / NodeNumX, 3.4f / NodeNumY);

	// NodeList �ʱ�ȭ
	/*int i = 1;
	int j = 1;*/
	vector<CDungeonMgr::sColliderOnMap> BackColList = CDungeonMgr::GetInst()->GetColliderData(mapNum);
	//vector<CDungeonMgr::sColliderOnMap>::iterator backColIter = BackColList.begin();

	for (int i =1; i < NodeNumY + 1; i++) //
	{
		//float NodePosY = mMapPos.y + (1.7f + NodeSize.y / 2.0f) - (i * NodeSize.y);
		float NodePosY = mMapPos.y + 1.7f - (i * NodeSize.y) + (NodeSize.y / 2.0f);
		for (int j = 1; j < NodeNumX + 1; j++)
		{
			//float NodePosX = mMapPos.x + (j * NodeSize.x) - (3.1f + (NodeSize.x / 2.0f));
			float NodePosX = mMapPos.x - 3.1f + (j * NodeSize.x) - (NodeSize.x / 2.0f);
			Vector2 NodePos = Vector2(NodePosX, NodePosY);

			// background Col �� Node �� �浹 ���� // �浹 �ÿ� mNodeList �� �߰����� �ʴ´�.
			if (IsNodeCollideToBackground(NodePos, NodeSize, BackColList) == false)
			{
				// ���⿡�� ó���� sNode �� �߱�ȭ
				mNodeList.insert(std::make_pair((UINT)100 * j + i, NodePos)); // õ�� ���ڸ� -> x  �ʰ� ���ڸ�-> y

				std::wstring NodeIdStr = std::to_wstring(100 * j + i);
				CGameObject* NodeObject = new CGameObject;
				CSceneMgr::GetInst()->GetActiveScene()->AddGameObject(eLayerType::Node, NodeObject, L"NodeObject_" + NodeIdStr,
					Vector3(NodePos.x, NodePos.y, 0.0f), Vector3(NodeSize.x, NodeSize.y, 0.0f),
					true, L"Mesh", L"", false);
				CColliderMgr* NodeObjColList = NodeObject->AddComponent<CColliderMgr>(eComponentType::ColliderList);
				CCollider2D* NodeObjCol = new CCollider2D;
				NodeObjCol->SetCollideType(eCollideType::Node);
				NodeObjColList->AddCollider(NodeObjCol);
			}
		}
	}

	// �ʱ�ȭ�� ��� �� Background �� �浹�ϴ� ��� ����
	
	// NodePos �� ��ġ�� Collider �� ���ϰ� ���Ͱ� Background �� �ε����� ������ �̲��������� Background �� ���ؼ� ������ �����ϵ��� �Ѵ�.
	/*vector<CDungeonMgr::sColliderOnMap>::iterator ColListIter = BackColList.begin();
	for (; ColListIter != BackColList.end(); ColListIter++)
	{

	}

	BackColList;*/
}

void CNaviScript::DeleteNodeCollideWithBackCol(vector<CDungeonMgr::sColliderOnMap> ColList)
{
	std::map<UINT, Vector2>::iterator iter = mNodeList.begin();
	for (; iter != mNodeList.end(); iter++)
	{
		iter->Get
	}
}

//bool CNaviScript::IsNodeCollideToBackground(Vector2 nodePos, Vector2 nodeSize, vector<CDungeonMgr::sColliderOnMap> ColList)
//{
//	for (vector<CDungeonMgr::sColliderOnMap>::iterator iter = ColList.begin(); iter != ColList.end(); iter++)
//	{
//		float DiffX;
//		if (iter->vColliderPos.x > nodePos.x)
//		{
//			DiffX = iter->vColliderPos.x - nodePos.x;
//		}
//		else if (iter->vColliderPos.x < nodePos.x)
//		{
//			DiffX = nodePos.x - iter->vColliderPos.x;
//		}
//
//		float DiffY;
//		if (iter->vColliderPos.y > nodePos.y)
//		{
//			DiffY = iter->vColliderPos.y - nodePos.y;
//		}
//		else if (iter->vColliderPos.y < nodePos.y)
//		{
//			DiffY = nodePos.y - iter->vColliderPos.y;
//		}
//
//		if (DiffX < nodeSize.x / 2.f + iter->vColliderScale.x / 2.f && DiffY < nodeSize.y / 2.f + iter->vColliderScale.y / 2.f)
//		{
//			// Node �� backCollider �� �浹�� ���
//			return true;
//		}
//	}
//
//	return false;
//}
  