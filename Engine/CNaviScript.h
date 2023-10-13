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
        UINT total;
        UINT heuristicValue;
        UINT curSideValue;
        Vector2 nodePos;
        sNode* ParentNode;
    };

private:
    Vector2 mNodeSize;
    Vector2 mObjScaleforDongeonMap;
    std::map<UINT, Vector2> mNodeList;
    CScene* mCurScene;
    UINT mMapNum;
    Vector2 mMapPos;
    CScript* OwnerScript;
public:
    CNaviScript();
    ~CNaviScript();

    virtual void Initialize();
    virtual void Update();
    virtual void LateUpdate();

    void SetGrid(Vector2 mapSize, UINT mapNum);
    void SetScene(CScene* scene) { mCurScene = scene; }
    // map position range (x : -3.1 ~ 3.1, y : -1.7 + 1.7) 
    void SetNodeList(Vector2 ObjColSize, UINT mapNum);
    void SetObjScaleforDongeonMap(Vector2 scale) { mObjScaleforDongeonMap = scale; }
    void SetMapNum(UINT num) { mMapNum = num; }
    void SetMapPos(Vector2 vec) { mMapPos = vec; };
    void SetOwnerScript(CScript* script) { OwnerScript = script; }
};

