#pragma once
#include "CEntity.h"
#include "Graphic.h"
#include "CDevice.h"
#include "CResource.h"

class CMesh :
    public CResource
{
private:
    tVertex vertexes[4] = {};

    ComPtr<ID3D11Buffer> mVB;
    ComPtr<ID3D11Buffer> mIB;

    D3D11_BUFFER_DESC mVBDesc;
    D3D11_BUFFER_DESC mIBDesc;

public:
    CMesh();
    ~CMesh();

    void Render();

    void CreateBuffer();
    void BindBuffer();

    virtual HRESULT ResourceLoad(const std::wstring name, const std::wstring& path) { return S_OK; }
};

