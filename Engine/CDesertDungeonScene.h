#pragma once
#include "CScene.h"
#include "CPlayer.h"
#include "CNaviScript.h"

class CDesertDungeonScene :
    public CScene
{
private:
    CPlayer* player;
    CGameObject* mainCamera;

    float mXPosStandard = 8.202f;
    float mYPosStandard = 4.492f;

    bool mbTranslateMapPos;

    Vector2 NextMapPos;
    UINT CurMapNum;

    std::vector<CGameObject*> mTempGameObjects;
    CNaviScript* golemNaviScript;
public:
    CDesertDungeonScene();
    ~CDesertDungeonScene();

    void Initialize();
    void Update();
    void LateUpdate();
    void Render();

    void SetBoolTranslateMapPos(bool b) { mbTranslateMapPos = b; }
    UINT GetCurMapNum() { return CurMapNum; }
};

