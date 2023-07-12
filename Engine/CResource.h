#pragma once
#include "CEntity.h"
#include "Enum.h"

class CResource :
    public CEntity
{
private:
    std::wstring mKey;
    std::wstring mPath;
    const eResourceType eType;
public:
    CResource(const eResourceType type);
    ~CResource();

    virtual HRESULT ResourceLoad(const std::wstring name, const std::wstring& path) = 0;
};

