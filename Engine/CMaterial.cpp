#include "CMaterial.h"

CMaterial::CMaterial()
    : CResource(eResourceType::Material)
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
    mTexture->BindShaderResource(eShaderStage::PS, 0);
    mShader->BindsShader();
}

void CMaterial::Clear()
{
    mTexture->Clear();
}
