#pragma once
#include "CScript.h"
class CGridScript :
    public CScript
{
private:
    CConstantBuffer* mGridCB;
public:
    CGridScript();
    ~CGridScript();

    virtual void Initialize() override;
    virtual void Update() override;
    virtual void LateUpdate() override;
    virtual void Render() override;

    void CreateConstantBuffer();
};

