#include "CNaviScript.h"
#include "CColliderMgr.h"
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

			for (vector<CDungeonMgr::sColliderOnMap>::iterator iter = BackColList.begin(); iter != BackColList.end(); iter++)
			{
				iter
			}

			mNodeList.insert(std::make_pair((UINT)100 * j + i, NodePos)); // õ�� ���ڸ� -> x  �ʰ� ���ڸ�-> y
		}
	}

	// �ʱ�ȭ�� ��� �� Background �� �浹�ϴ� ��� ����
	
	// NodePos �� ��ġ�� Collider �� ���ϰ� ���Ͱ� Background �� �ε����� ������ �̲��������� Background �� ���ؼ� ������ �����ϵ��� �Ѵ�.
	vector<CDungeonMgr::sColliderOnMap>::iterator ColListIter = BackColList.begin();
	for (; ColListIter != BackColList.end(); ColListIter++)
	{

	}

	BackColList;
}

bool CNaviScript::IsNodeCollideToBackground(float nodePos, Vector2 nodeSize, vector<CDungeonMgr::sColliderOnMap> ColList)
{
	
	if()
	return false;
}
  