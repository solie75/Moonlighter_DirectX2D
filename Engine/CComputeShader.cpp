#include "CComputeShader.h"
#include "CDevice.h"

CComputeShader::CComputeShader()
    : CResource(eResourceType::ComputeShader)
{
}

CComputeShader::~CComputeShader()
{
}

bool CComputeShader::Create(const std::wstring& name, const std::string& methodName)
{
    std::filesystem::path shaderPath = std::filesystem::current_path().parent_path();
    shaderPath += L"\\Shader\\";

    std::filesystem::path fullPath(shaderPath.c_str());
    fullPath += name;

    ID3DBlob* errorBlob = nullptr;
    CDevice::GetInst()->CompileFromfile(fullPath, methodName, "cs_5_0", mCSBlob.GetAddressOf());
    CDevice::GetInst()->CrateComputeShader(mCSBlob->GetBufferPointer(), mCSBlob->GetBufferSize(), mCS.GetAddressOf());

    return false;
}
