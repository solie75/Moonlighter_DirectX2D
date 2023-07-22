#include "CMaterial.h"

CMaterial::CMaterial()
    : CResource(eResourceType::Material)
    , mRenderMode(eRenderingMode::End)
{
}

CMaterial::~CMaterial()
{
}

HRESULT CMaterial::ResourceLoad(const std::wstring name, const std::wstring& path)
{
    return S_OK;
}

void CMaterial::Bind()
{
    if (mTexture)
    {
        mTexture->BindShaderResource(eShaderStage::PS, 0);
    }
    if (mShader)
    {
        mShader->BindsShader();
    }

}

void CMaterial::Clear()
{
    if (mTexture)
    {
        mTexture->Clear();
    }
}
