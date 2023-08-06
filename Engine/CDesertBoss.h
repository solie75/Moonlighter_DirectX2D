#pragma once
#include "CMonster.h"
class CDesertBoss :
    public CMonster
{
public:
    CDesertBoss();
    ~CDesertBoss();

    virtual void Initialize();
    virtual void Update();
    virtual void LateUpdate();
    virtual void Render();
};

