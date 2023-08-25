#pragma once
#include "CResource.h"

class CComputeShader :
    public CResource
{
protected:
    Microsoft::WRL::ComPtr<ID3DBlob> mCSBlob;
    Microsoft::WRL::ComPtr<ID3D11ComputeShader> mCS;

    UINT mThreadGroupCountX;
    UINT mThreadGroupCountY;
    UINT mThreadGroupCountZ;

    UINT mGroupX;
    UINT mGroupY;
    UINT mGroupZ;

public:
    CComputeShader();
    virtual ~CComputeShader();

    bool Create(const std::wstring& name, const std::string& methodName);
    virtual HRESULT ResourceLoad(const std::wstring name, const std::wstring& path) { return S_FALSE; };

    void OnExcute();

    virtual void Binds();
    virtual void Clear();
};

