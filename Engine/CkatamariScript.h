#pragma once
#include "CScript.h"

#include "CAimSight.h"
#include "CState.h"

#include "CAnimator.h"
#include "CCollider2D.h"

class CkatamariScript :
    public CScript
{
private:
    CState* mState;
    CAimSight* mAimSight;

public:
    CkatamariScript();
    ~CkatamariScript();

    virtual void Initialize();
    virtual void Update();
    virtual void LateUpdate();
};

