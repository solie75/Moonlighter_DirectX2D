#include "CRenderMgr.h"

CRenderMgr::CRenderMgr()
	: mCB{}
{
	mGraphicContext = CDevice::GetInst()->GetContext();
}

CRenderMgr::~CRenderMgr()
{
}

void CRenderMgr::Init()
{
	mMesh = new CMesh;
	mMesh->CreateBuffer();
	mMesh->BindBuffer();
	CreateConstantBuffer();
}

void CRenderMgr::Update()
{
}

void CRenderMgr::Render()
{
	mGraphicContext->DrawIndexed(6, 0, 0);
	HRESULT hr = CDevice::GetInst()->GetSwapChain()->Present(0, 0);
}

bool CRenderMgr::CreateConstantBuffer()
{
	// Set Constant Buffer Description
	mCB.mDesc.ByteWidth = sizeof(Vector4);
	mCB.mDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_CONSTANT_BUFFER;
	mCB.mDesc.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;
	mCB.mDesc.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
	mCB.eType = eCBType::Transform;

	// Create Constant Buffer
	CDevice::GetInst()->GetDevice()->CreateBuffer(&(mCB.mDesc), nullptr, mCB.mBuffer.GetAddressOf());
	
	// Set Constant Buffer
	Vector4 pos(0.3f, 0.0f, 0.0f, 1.0f);

	D3D11_MAPPED_SUBRESOURCE subRes = {};
	mGraphicContext->Map(mCB.mBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &subRes);
	memcpy(subRes.pData, &pos, mCB.mDesc.ByteWidth);
	mGraphicContext->Unmap(mCB.mBuffer.Get(), 0);

	// Bind Constant Buffer	
	BindConstantBuffer(eShaderStage::VS, mCB);

	return true;
}

void CRenderMgr::BindConstantBuffer(eShaderStage stage, tConstantBuffer tCB)
{
	switch (stage)
	{
	case eShaderStage::VS:
		mGraphicContext->VSSetConstantBuffers((UINT)tCB.eType, 1, (tCB.mBuffer).GetAddressOf());
		break;
	case eShaderStage::HS:
		mGraphicContext->HSSetConstantBuffers((UINT)tCB.eType, 1, (tCB.mBuffer).GetAddressOf());
		break;
	case eShaderStage::DS:
		mGraphicContext->DSSetConstantBuffers((UINT)tCB.eType, 1, (tCB.mBuffer).GetAddressOf());
		break;
	case eShaderStage::GS:
		mGraphicContext->GSSetConstantBuffers((UINT)tCB.eType, 1, (tCB.mBuffer).GetAddressOf());
		break;
	case eShaderStage::PS:
		mGraphicContext->PSSetConstantBuffers((UINT)tCB.eType, 1, (tCB.mBuffer).GetAddressOf());
		break;
	case eShaderStage::CS:
		mGraphicContext->CSSetConstantBuffers((UINT)tCB.eType, 1, (tCB.mBuffer).GetAddressOf());
		break;
	case eShaderStage::End:
		break;
	default:
		break;
	}
}


