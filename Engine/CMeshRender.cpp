#include "CMeshRender.h"
#include "CGameObject.h"
#include "CRenderMgr.h"
#include "CAnimator.h"

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
	mMaterial->Bind();
	
	{
		CDevice::GetInst()->GetContext()->
			RSSetState(CRenderMgr::GetInst()->GetRasterizerState(mMaterial->GetShader()->GetRSType()).Get());
		CDevice::GetInst()->GetContext()->
			OMSetDepthStencilState(CRenderMgr::GetInst()->GetDepthStencilState(mMaterial->GetShader()->GetDSType()).Get(), 0);
		CDevice::GetInst()->GetContext()->
			OMSetBlendState(CRenderMgr::GetInst()->GetBlendState(mMaterial->GetShader()->GetBSType()).Get(), nullptr, 0xffffffff);
	}

	CRenderMgr::GetInst()->BindConstantBuffer(eShaderStage::VS, tr->GetTransformCB());

	CAnimator* animator = GetOwner()->GetComponent<CAnimator>(eComponentType::Animator);
	if (animator)
	{
		animator->Binds();
	}

	mMesh->Render();
}
