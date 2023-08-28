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

    Particle mParticles[75] = {};

public:
    CParticleSystem();
    ~CParticleSystem();

    Vector4 SetRendomPos();
    float SetRendomFloat(float leftValje, float rightValue);

    virtual void Initialize();
    virtual void Update();
    virtual void LateUpdate();
    virtual void Render();
};

