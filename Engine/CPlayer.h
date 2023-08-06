#pragma once
//#include "CCreatureObject.h"
#include "CGameObject.h"
#include "CState.h"
#include "CAimSight.h"

class CPlayer :
    public CGameObject
{
private:
    eCreatureType mCreatureType;
    CState* mState;
    CAimSight* mAimSight;


public:
    CPlayer();
    ~CPlayer();

    virtual void Initialize();
    virtual void Update();
    virtual void LateUpdate();
    virtual void Render();

    eCreatureType GetCreatureType() { return mCreatureType; }
    CState* GetState() { return mState; }
    CAimSight* GetAimSight() { return mAimSight; }

};

