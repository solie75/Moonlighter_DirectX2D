#pragma once
#include "CScript.h"
#include "CFireBall.h"
#include "CState.h"

class CDesertBossCircleScript :
    public CScript
{
public:
    enum class eCircleAttackState
    {
        Enter,
        Stay,
        Exit,
        Parts,
        End,
    };

private:
    float diff;
    CScene* ownScene;
    int firedNum;
    eCircleAttackState mCircleAttackState;
    eCircleAttackState mPrevCircleAttackState;
    float mtime;
    Vector2 mAimNormal;
    float mPartsAttackSpeed;
    CState mState;
    UINT CollideId;

public:
    CDesertBossCircleScript();
    ~CDesertBossCircleScript();          

    virtual void Initialize();
    virtual void Update();
    virtual void LateUpdate();
    virtual void Render();

    void SetScene(CScene* scene) { ownScene = scene; }

    void ChangeCirCleAttackState(eCircleAttackState state)
    { 
        mPrevCircleAttackState = mCircleAttackState;
        mCircleAttackState = state;
    }
};

