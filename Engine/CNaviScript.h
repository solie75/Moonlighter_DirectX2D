#pragma once
#include "CScript.h"
#include "CDungeonMgr.h"
#include <queue>

class CNaviScript :
    public CScript
{
public:
    struct sNode
    {
        UINT id;
        UINT total;
        UINT heuristicValue;
        UINT stepValue;
        Vector2 nodePos;
        //sNode* ParentNode;
        UINT ParentNodeId;
        //CGameObject* nodeObj;
        bool IsCollide;
    };

private:
    Vector2 mNodeSize;
    Vector2 mObjScaleforDongeonMap;
    std::map<UINT, sNode> mTotalNodeList;
    CScene* mCurScene;
    UINT mMapNum;
    Vector2 mMapPos;
    CScript* OwnerScript;
    UINT mStartNodeId;
    UINT mGoalNodeId;
    UINT curStepOnMoving;
    std::map<UINT, vector<sNode>> mAStarNodeList;


    UINT mNextNodeId;
    //std::map<UINT, sNode> mAroundNodeList;
    std::map<UINT, sNode> mWayNodeList;

public:
    CNaviScript();
    ~CNaviScript();

    virtual void Initialize();
    virtual void Update();
    virtual void LateUpdate();

    void SetIsCollide(UINT mapNum);
    void SetAStarNodeList(UINT stepNum);
    //void SetGrid(Vector2 mapSize, UINT mapNum);
    void SetScene(CScene* scene) { mCurScene = scene; }
    // map position range (x : -3.1 ~ 3.1, y : -1.7 + 1.7) 
    void SetNodeList(Vector2 ObjColSize, UINT mapNum);
    void SetObjScaleforDongeonMap(Vector2 scale) { mObjScaleforDongeonMap = scale; }
    void SetMapNum(UINT num) { mMapNum = num; }
    void SetMapPos(Vector2 vec) { mMapPos = vec; };
    void SetOwnerScript(CScript* script) { OwnerScript = script; }
    void SetStartNode(Vector2 startObjPos);
    void SetGoalNode(Vector2 goalObjPos);
    void SetAroundNodeList(UINT NodeId);
    UINT SetWayNodeList(); // 총 단계의 수를 반환한다.
    void WayNodeListClear();
    void SetNodeSize(Vector2 size) { mNodeSize = size; }
    UINT GetNodeId(Vector2 NodePos);
    UINT GetHeuristicValue(UINT StartId);
    UINT GetNextNode();
    bool IsCollideNode(UINT nodeId);
    Vector2 GetMovingDirection(Vector2 curPos);

};

