#pragma once
#include "CScript.h"
class CDesertBossSquareScript :
    public CScript
{
private:
    CScene* ownScene;
    float mtime;
public:
    CDesertBossSquareScript();
    ~CDesertBossSquareScript();

    virtual void Initialize();
    virtual void Update();
    virtual void LateUpdate();
    virtual void Render();

    void SetScene(CScene* scene) { ownScene = scene; }
};

