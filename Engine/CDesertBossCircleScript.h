#pragma once
#include "CScript.h"
#include "CFireBall.h"

class CDesertBossCircleScript :
    public CScript
{
private:
    float diff;
    CScene* ownScene;
    bool fired;
public:
    CDesertBossCircleScript();
    ~CDesertBossCircleScript();          

    virtual void Initialize();
    virtual void Update();
    virtual void LateUpdate();
    virtual void Render();

    void SetScene(CScene* scene) { ownScene = scene; }
};

