#pragma once
#include "CScript.h"
class CDesertBossTriangleScript :
    public CScript
{
private:
    float mtime;
    //Vector2 mLavaBallAimNormal;

    CTransform* willTr;
    bool isFired;
    CScene* ownScene;
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

