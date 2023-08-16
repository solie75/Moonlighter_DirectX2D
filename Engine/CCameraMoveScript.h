#pragma once
#include "CScript.h"
#include "CTransform.h"
#include "CGameObject.h"

class CCameraMoveScript :
    public CScript
{
public:
    virtual void Update() override;
};

