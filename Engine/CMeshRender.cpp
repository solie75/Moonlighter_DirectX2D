#include "CMeshRender.h"
#include "CGameObject.h"
#include "CRenderMgr.h"

CMeshRender::CMeshRender()
	: CComponent(eComponentType::MeshRender)
{
}

CMeshRender::~CMeshRender()
{
}

void CMeshRender::Initialize()
{
}

void CMeshRender::Update()
{
}

void CMeshRender::LateUpdate()
{
}

void CMeshRender::Render()
{
	CTransform* tr = GetOwner()->GetComponent<CTransform>(eComponentType::Transform);
	tr->CreateConstantBuffer();

	mMaterial->Clear();
	mMesh->Render();
	mMaterial->Bind();

	CRenderMgr::GetInst()->BindConstantBuffer(eShaderStage::VS, tr->GetTransformCB());
}
