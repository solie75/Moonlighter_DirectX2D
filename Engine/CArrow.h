#pragma once
#include "CGameObject.h"
#include "CPlayer.h"

class CArrow :
    public CGameObject
{
public:
    enum class eProjectileState
    {
        Idle,
        Collide,
        End,
    };

    enum class eBowType
    {
        Hunter,
        Poison,
        Soldier,
        FlameThrower,
        End,
    };

    enum class eArrowType
    {
        Main,
        SubAttack,
        End,
    };

private:
    int DirectNum;
    Vector3 direction;
    Vector3 pos;
    float speed;
    float time;

    eBowType mBowType;
    CAimSight::eSight mSight;
    eArrowType mArrowType;
public:
    CArrow(UINT type, UINT sight, UINT arrowType);
    ~CArrow();

    virtual void Initialize();
    virtual void Update();
    virtual void LateUpdate();
    virtual void Render();

    void SetDirection(Vector3 direct) { direction = direct; }
    void SetSpeed(float f) { speed = f; }
    void SetArrowType(eArrowType type) { mArrowType = type; }
};

