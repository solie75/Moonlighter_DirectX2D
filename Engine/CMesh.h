#pragma once
#include "CEntity.h"
class CMesh :
    public CEntity
{
private:
    ComPtr<ID3D11Buffer> m_VB;
public:
    CMesh();
    ~CMesh();
};

