#pragma once
#include "CResource.h"
#include "CShader.h"
#include "CTexture.h"

class CMaterial :
    public CResource
{
private:
    std::shared_ptr<CShader> mShader;
    std::shared_ptr<CTexture> mTexture;

    eRenderingMode mRenderMode;

public:
    CMaterial();
    ~CMaterial();

    virtual HRESULT ResourceLoad(const std::wstring name, const std::wstring& path) override;

    void SetShader(std::shared_ptr<CShader> shader) { mShader = shader; }
    void SetTexture(std::shared_ptr<CTexture> texture) { mTexture = texture; }
    std::shared_ptr<CShader> GetShader() { return mShader; }

    void Bind();
    void Clear();

    void SetRenderMode(eRenderingMode mode) { mRenderMode = mode; }
    eRenderingMode GetRenderingMode() { return mRenderMode; }
};