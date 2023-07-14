#pragma once
#include "CEntity.h"
#include "CGameObject.h"

class CLayer :
    public CEntity
{
private:
    std::vector<CGameObject*> mGameObjects;
public:
    CLayer();
    ~CLayer();

    virtual void Initialize();
    virtual void Update();
    virtual void LateUpdate();
    virtual void Render();

    void AddGameObject(CGameObject* gameObj);
};

