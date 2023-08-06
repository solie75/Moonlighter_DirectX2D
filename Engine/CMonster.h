#pragma once
#include "CGameObject.h"
#include "CState.h"
#include "CAimSight.h"

class CMonster :
    public CGameObject
{
private:
    eCreatureType mCreatureType;
    eState mState;
    eAimSight mAimSight;
    int HP;

public:
    CMonster();
    ~CMonster();

    virtual void Initialize();
    virtual void Update();
    virtual void LateUpdate();
    virtual void Render();
};

