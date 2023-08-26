#pragma once
#include "CComputeShader.h"
#include "CStructedBuffer.h"
#include "CConstantBuffer.h"

class CParticleShader :
    public CComputeShader
{
private:
    CStructedBuffer* mParticleBuffer;
    CConstantBuffer* mParticleCB;

public:
    CParticleShader();
    ~CParticleShader();

    virtual void Binds() override;
    virtual void Clear() override;

    void SetParticleBuffer(CStructedBuffer* particleBuffer);
};

