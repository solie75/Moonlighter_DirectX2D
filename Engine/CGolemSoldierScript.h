#pragma once
#include "CMonsterScript.h"
#include "CNaviScript.h"

class CGolemSoldierScript :
    public CMonsterScript
{
private:
    Vector2 mScaleforDongeonMap = Vector2(12.4, 4.85f);
    CNaviScript* mNaviScript;
    CGameObject* player;


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
        // ���⿡�� ObjScale �� �⺻ Scale �������� ȯ���Ͽ� Navi �� Set �Ѵ�.
        mNaviScript->SetObjScaleforDongeonMap(Vector2(objScale.x / (mScaleforDongeonMap.x / 6.2f), objScale.y / (mScaleforDongeonMap.y / 3.4f)));
    }
    //void SetOwnerToMonsterScript() { CMonsterScript::SetOwnerOnMonsterScript(GetOwner()); }
};

