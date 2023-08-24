#pragma once
#include "CScript.h"
class CDesertBossSquareScript :
    public CScript
{
public:
    enum class eSquareAttackState
    {
        FireEnter,
        FireStay,
        FireExit,
        Parts,
        End,
    };
private:
    CScene* ownScene;
    float mtime;
    eSquareAttackState mSquareAttackState;
    eSquareAttackState mPrevSquareAttackState;
    Vector2 mAimNormal;
    //float mtime;
    float mPartsAttackSpeed;
    UINT CollideId;

public:
    CDesertBossSquareScript();
    ~CDesertBossSquareScript();

    virtual void Initialize();
    virtual void Update();
    virtual void LateUpdate();
    virtual void Render();

    void SetScene(CScene* scene) { ownScene = scene; }
};

