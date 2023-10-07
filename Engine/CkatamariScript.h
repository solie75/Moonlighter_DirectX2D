#pragma once

#include "CMonsterScript.h"

#include "CAimSight.h"
#include "CState.h"

#include "CAnimator.h"
#include "CCollider2D.h"

class CKatamariScript :
    public CMonsterScript
{
private:
    //CState* mState;
    //CAimSight* mAimSight;
    Vector3 mPosBeforeCollide;

    //CHPScript* mHpScript;
public:
    CKatamariScript();
    ~CKatamariScript();

    virtual void Initialize();
    virtual void Update();
    virtual void LateUpdate();

    void ChangeSight();
    void ChangeState(eState state) { GetMonsterState()->SetState(state); };
};

