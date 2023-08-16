#pragma once
#include "CGameObject.h"
class CLavaBall :
    public CGameObject
{
public:
    enum class eLavaState
    {
        Ball,
        SplashEnter,
        SplashStay,
        End,
    };

private:
    Vector2 mAimNormal;
    Vector2 mGoalPos;
    float speed;
    float dropSpeed;
    eLavaState mLavaState;
    eLavaState mPrevLavaState;
    float splashTime;

public:
    CLavaBall();
    ~CLavaBall();

    virtual void Initialize();
    virtual void Update();
    virtual void LateUpdate();
    virtual void Render();

    void SetAimNormal(Vector2 aim) { mAimNormal = aim; }
    void SetGoalPos(Vector2 goal) { mGoalPos = goal; }
    void ChangeLavaState(eLavaState state) { mPrevLavaState = mLavaState; mLavaState = state; }
};

