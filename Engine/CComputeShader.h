#pragma once
#include "CResource.h"
class CComputeShader :
    public CResource
{
private:
    Microsoft::WRL::ComPtr<ID3DBlob> mCSBlob;
    Microsoft::WRL::ComPtr<ID3D11ComputeShader> mCS;

public:
    CComputeShader();
    virtual ~CComputeShader();

    bool Create(const std::wstring& name, const std::string& methodName);
    virtual HRESULT ResourceLoad(const std::wstring name, const std::wstring& path) { return S_FALSE; };
};

