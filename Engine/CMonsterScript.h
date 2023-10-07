#pragma once
#include "CScript.h"
#include "CState.h"
#include "CAimSight.h"
#include "CGameObject.h"


class CMonsterScript :
    public CScript
{
private:
    CState* mState;
    CAimSight* mAimSight;

    CGameObject* mOwner;

public:
    CMonsterScript();
    ~CMonsterScript();

    virtual void Initialize();
    virtual void Update();
    virtual void LateUpdate();

    CState* GetMonsterState() { return mState; }
    CAimSight* GetMonsterAimSight() { return mAimSight; }
    void SetOwnerOnMonsterScript(CGameObject* gameObj) { mOwner = gameObj; }
};

