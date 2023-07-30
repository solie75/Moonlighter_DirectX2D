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

private:

public:
    CCreatureObject();
    ~CCreatureObject();

    virtual void Initialize();
    virtual void Update();
    virtual void LateUpdate();
    virtual void Render();
};

