#pragma once
#include "CEntity.h"
#include "Enum.h"

class CGameObject;

class CComponent :
    public CEntity
{
private:
    eComponentType mType;
    CGameObject* mOwner;
public:
    CComponent(eComponentType type);
    ~CComponent();

    virtual void Initialize();
    virtual void Update();
    virtual void LateUpdate();
    virtual void Render();

    void SetOwner(CGameObject* owner) { mOwner = owner; }
    CGameObject* GetOwner() { return mOwner; }

    eComponentType GetType() { return mType; }
};

