#pragma once
#include "CScene.h"
class CShopScene :
    public CScene
{
public:
    CShopScene();
    virtual ~CShopScene();
    virtual void Initialize() override;
    virtual void Update() override;
    virtual void LateUpdate() override;
    virtual void Render() override;
};

