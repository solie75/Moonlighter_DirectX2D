#include "CRenderMgr.h"
#include "CTexture.h"

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
	// Create CShader
	mShader = new CShader;
	mShader->CreateShader();
	mShader->CreateInputLayout();
	mShader->BindsShader();
	mShader->BindInputLayout();

	// Create Mesh
	mMesh = new CMesh;
	mMesh->CreateBuffer();
	mMesh->BindBuffer();

	// Create & Bind CB
	CreateConstantBuffer();
	// Bind Constant Buffer	
	BindConstantBuffer(eShaderStage::VS, mCB);

	// Create Texture
	CTexture* texture = new CTexture;
	texture->ResourceLoad(L"Smile", L"..\\Resource\\Texture\\Smile.png");
	texture->BindShaderResource(eShaderStage::PS, 0);

	// Set Sampler
	SetUpState();
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

void CRenderMgr::SetUpState()
{
	D3D11_SAMPLER_DESC samplerDecs = {};
	samplerDecs.AddressU = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDecs.AddressV = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDecs.AddressW = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDecs.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
	HRESULT hr = CDevice::GetInst()->GetDevice()->CreateSamplerState(&samplerDecs, samplerState[(UINT)eSamplerType::Point].GetAddressOf());
	BindSampler(eShaderStage::PS, 0, samplerState[(UINT)eSamplerType::Point].GetAddressOf());

	samplerDecs.Filter = D3D11_FILTER_ANISOTROPIC;
	CDevice::GetInst()->GetDevice()->CreateSamplerState(&samplerDecs, samplerState[(UINT)eSamplerType::Anisotropic].GetAddressOf());
	BindSampler(eShaderStage::PS, 1, samplerState[(UINT)eSamplerType::Anisotropic].GetAddressOf());
}

void CRenderMgr::BindSampler(eShaderStage stage, UINT StartSlot, ID3D11SamplerState** ppSamplerState)
{
	switch (stage)
	{
	case eShaderStage::VS:
		mGraphicContext->VSSetSamplers(StartSlot, 1, ppSamplerState);
		break;
	case eShaderStage::HS:
		mGraphicContext->HSSetSamplers(StartSlot, 1, ppSamplerState);
		break;
	case eShaderStage::DS:
		mGraphicContext->DSSetSamplers(StartSlot, 1, ppSamplerState);
		break;
	case eShaderStage::GS:
		mGraphicContext->GSSetSamplers(StartSlot, 1, ppSamplerState);
		break;
	case eShaderStage::PS:
		mGraphicContext->PSSetSamplers(StartSlot, 1, ppSamplerState);
		break;
	case eShaderStage::CS:
		mGraphicContext->CSSetSamplers(StartSlot, 1, ppSamplerState);
		break;
	case eShaderStage::End:
		break;
	default:
		break;
	}
}