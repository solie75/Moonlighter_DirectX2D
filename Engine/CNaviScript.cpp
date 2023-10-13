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
	// 맵 변경시에 Node 는 한 번만 변경한다.
	SetNodeList(mObjScaleforDongeonMap, mMapNum);

}

void CNaviScript::Update()
{
	// 매 업데이트 마다. Node 를 새로 생성한다. 

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

	// NodeList 초기화
	int i = 1;
	int j = 1;
	for (; i < NodeNumY + 1; i++) //
	{
		//float NodePosY = mMapPos.y + (1.7f + NodeSize.y / 2.0f) - (i * NodeSize.y);
		float NodePosY = mMapPos.y + 1.7f - (i * NodeSize.y) + (NodeSize.y / 2.0f);
		for (; j < NodeNumX + 1; j++)
		{
			//float NodePosX = mMapPos.x + (j * NodeSize.x) - (3.1f + (NodeSize.x / 2.0f));
			float NodePosX = mMapPos.x - 3.1f + (j * NodeSize.x) - (NodeSize.x / 2.0f);
			
			Vector2 NodePos = Vector2(NodePosX, NodePosY);
			mNodeList.insert(std::make_pair((UINT)100 * j + i, NodePos)); // 천과 백자리 -> x  십과 일자리-> y
		}
	}

	// 초기화된 노드 중 Background 와 충돌하는 노드 제거
	vector<CDungeonMgr::sColliderOnMap> BackColList = CDungeonMgr::GetInst()->GetColliderData(mapNum);
	// NodePos 의 위치를 Collider 에 비교하고 몬스터가 Background 에 부딪혔을 때에는 미끄러지듯이 Background 를 피해서 앞으로 진행하도록 한다.
	vector<CDungeonMgr::sColliderOnMap>::iterator ColListIter = BackColList.begin();

	BackColList;
}
