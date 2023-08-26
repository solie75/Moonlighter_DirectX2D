#pragma once
#include "CMeshRender.h"


class CParticleSystem :
    public CMeshRender
{
private:
    CStructedBuffer* mBuffer;

    UINT mCount;
    Vector4 mStartSize;
    Vector4 mEndSize;
    Vector4 mStartColor;
    Vector4 mEndColor;
    float mLifeTime;

public:
    CParticleSystem();
    ~CParticleSystem();

    virtual void Initialize() override;
    virtual void Update() override;
    virtual void LateUpdate() override;
    virtual void Render() override;
};

