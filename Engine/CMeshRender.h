#pragma once
#include "CComponent.h"
#include "CMesh.h"
#include "CMaterial.h"

class CMeshRender :
    public CComponent
{
private:
    std::shared_ptr<CMesh> mMesh;
    std::shared_ptr<CMaterial> mMaterial;
public:
    CMeshRender();
    ~CMeshRender();

    virtual void Initialize();
    virtual void Update();
    virtual void LateUpdate();
    virtual void Render();

    void SetMesh(std::shared_ptr<CMesh> mesh) { mMesh = mesh; }
    void SetMaterial(std::shared_ptr<CMaterial> material) { mMaterial = material; }
};

