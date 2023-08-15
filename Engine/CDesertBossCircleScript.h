#pragma once
#include "CScript.h"
#include "CFireBall.h"

class CDesertBossCircleScript :
    public CScript
{
public:
    enum class eCircleAttackState
    {
        Enter,
        Stay,
        Exit,
        End,
    };

private:
    float diff;
    CScene* ownScene;
    int firedNum;
    eCircleAttackState mCircleAttackState;
    eCircleAttackState mPrevCircleAttackState;
    float mtime;

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

