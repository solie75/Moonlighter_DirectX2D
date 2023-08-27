#pragma once
#include "CMeshRender.h"
#include "CParticleShader.h"

class CParticleSystem :
    public CMeshRender
{
private:
    CStructedBuffer* mBuffer;
    std::shared_ptr<CParticleShader> mCS;

    UINT mParticleNum;
    Vector4 mStartSize;
    Vector4 mEndSize;
    Vector4 mStartColor;
    Vector4 mEndColor;
    float mLifeTime;
    float mFrequency;

    Particle mParticles[100] = {};

public:
    CParticleSystem();
    ~CParticleSystem();

    virtual void Initialize() override;
    virtual void Update() override;
    virtual void LateUpdate() override;
    virtual void Render() override;
};

