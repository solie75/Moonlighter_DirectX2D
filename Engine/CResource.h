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

    const std::wstring& GetKey() { return mKey; }
    const std::wstring& GetPath() { return mPath; }
    void SetKey(const std::wstring& key) { mKey = key; }
    void SetPath(const std::wstring& path) { mPath = path; }

    virtual HRESULT ResourceLoad(const std::wstring name, const std::wstring& path) = 0;
};

