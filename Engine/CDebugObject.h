#pragma once
#include "CGameObject.h"
#include "CDebugObject.h"
class CDebugObject :
    public CGameObject
{


public:
    CDebugObject();
    ~CDebugObject();

    virtual void Initialize() override;
    virtual void Update() override;
    virtual void LateUpdate() override;
    virtual void Render() override;
};

