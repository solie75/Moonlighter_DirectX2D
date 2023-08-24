#pragma once
#include "CScript.h"
class CDesertBossTriangleScript :
    public CScript
{
public:
    enum class eTriangleAttackState
    {
        Parts,
        End,
    };
private:
    float mtime;
    //Vector2 mLavaBallAimNormal;
    eTriangleAttackState mTriangleAttackState;
    eTriangleAttackState mPrevTriangleAttackState;

    CTransform* willTr;
    bool isFired;
    CScene* ownScene;

    Vector2 mAimNormal;
    //float mtime;
    float mPartsAttackSpeed;
    UINT CollideId;
public:
    CDesertBossTriangleScript();
    ~CDesertBossTriangleScript();

    virtual void Initialize();
    virtual void Update();
    virtual void LateUpdate();
    virtual void Render();

    void SetScene(CScene* scene) { ownScene = scene; }
    void SetOtherPos(CTransform* tr) { willTr = tr; }
};

