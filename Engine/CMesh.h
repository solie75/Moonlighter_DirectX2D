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

    UINT mIndexCount;

public:
    CMesh();
    ~CMesh();

    void Render();

    void CreateSquareBuffer();
    void CreatePointBuffer();
    void BindBuffer();
    void RenderInstanced(UINT startIndexLocation);

    virtual HRESULT ResourceLoad(const std::wstring name, const std::wstring& path) { return S_OK; }

    tVertex GetVertex(UINT i) { return vertexes[i]; }
};

