#pragma once
#include "CScript.h"

#include "CAimSight.h"
#include "CState.h"

#include "CAnimator.h"
#include "CCollider2D.h"

class CKatamariScript :
    public CScript
{
private:
    CState* mState;
    CAimSight* mAimSight;
    Vector3 mPosBeforeCollide;

public:
    CKatamariScript();
    ~CKatamariScript();

    virtual void Initialize();
    virtual void Update();
    virtual void LateUpdate();

    void ChangeSight();
    void ChangeState(eState state) { mState->SetState(state); };
};

