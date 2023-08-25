#pragma once
#include "CComputeShader.h"
#include "CTexture.h"

class CPaintShader :
    public CComputeShader
{
private:
    std::shared_ptr<class CTexture> mTarget;

public:
    virtual void Binds() override;
    virtual void Clear() override;

    void SetTarget(std::shared_ptr<class CTexture> target) { mTarget = target; } // �� �ڷ����� class �� ����?
};

