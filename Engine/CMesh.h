#pragma once
#include "CEntity.h"
#include "Graphic.h"
#include "CDevice.h"
class CMesh :
    public CEntity
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

    void CreateBuffer();
    void BindBuffer();
};

