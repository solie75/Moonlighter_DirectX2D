#include "CComputeShader.h"
#include "CDevice.h"

CComputeShader::CComputeShader()
    : CResource(eResourceType::ComputeShader)
{
    mThreadGroupCountX = 32;
    mThreadGroupCountY = 32;
    mThreadGroupCountZ = 1;
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

void CComputeShader::OnExcute()
{
    Binds();

    CDevice::GetInst()->BindComputeShader(mCS.Get());
    CDevice::GetInst()->Dispatch(mGroupX, mGroupY, mGroupZ);

    Clear();
}

void CComputeShader::Binds()
{
}

void CComputeShader::Clear()
{
}
