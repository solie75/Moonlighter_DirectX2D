#pragma once
#include "CGameObject.h"
class CCreatureObject :
    public CGameObject
{
public:
    enum class eCreatureType
    {
        Player,
        Monster,
        NPC,
        End,
    };

    enum class eAimSight
    {
        Left,
        Right,
        Up,
        Down,
        End,
    };

    enum class eState
    {
        Idle,
        Attack,
        Hit, // ÇÇ°Ý
        Roll,
        Walk,
        End,
    };


private:
    eState mState;
    eAimSight mAimSight;
    eCreatureType mCreatureType;

public:
    CCreatureObject();
    ~CCreatureObject();

    virtual void Initialize();
    virtual void Update();
    virtual void LateUpdate();
    virtual void Render();

    void SetState(eState state) { mState = state; }
    void SetAimSight(eAimSight sight) { mAimSight = sight; }
    void SetCreatureType(eCreatureType type) { mCreatureType = type; }
    eState GetState() { return mState; }
    eAimSight GetAimSight() { return mAimSight; }
    eCreatureType GetCreatureType() { return mCreatureType; }
};

