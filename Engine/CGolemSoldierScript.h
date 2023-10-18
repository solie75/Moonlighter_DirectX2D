#pragma once
#include "CMonsterScript.h"
#include "CNaviScript.h"

class CGolemSoldierScript :
    public CMonsterScript
{
private:
    Vector2 mScaleforDongeonMap = Vector2(12.4, 4.85f);
    CNaviScript* mNaviScript;
    CCollider2D* playerCol;
    bool mbLockOn;
    Vector2 mTargetPos;


public:
    CGolemSoldierScript();
    ~CGolemSoldierScript();

    virtual void Initialize();
    virtual void Update();
    virtual void LateUpdate();

    std::wstring GetGolemSoldierSightStr(CAimSight::eSight sight);
    Vector2 GetScaleforDongeonMap() { return mScaleforDongeonMap; }
    CNaviScript* GetNaviScript() { return mNaviScript; }
    void SetNaviData(Vector2 pos, UINT mapNum, Vector2 objScale) { 
        mNaviScript->SetMapNum(mapNum); 
        mNaviScript->SetMapPos(pos); 
        // 여기에서 ObjScale 을 기본 Scale 기준으로 환산하여 Navi 에 Set 한다.
        mNaviScript->SetObjScaleforDongeonMap(Vector2(objScale.x / (mScaleforDongeonMap.x / 6.2f), objScale.y / (mScaleforDongeonMap.y / 3.4f)));
    }
    //void SetOwnerToMonsterScript() { CMonsterScript::SetOwnerOnMonsterScript(GetOwner()); }
};

