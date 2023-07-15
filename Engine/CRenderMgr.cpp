#include "CRenderMgr.h"
#include "CTexture.h"
#include "CPlayScene.h"

CRenderMgr::CRenderMgr()
	: mCB{}
	//, mGameObj(nullptr)
{
	mGraphicContext = CDevice::GetInst()->GetContext();
}

CRenderMgr::~CRenderMgr()
{
}

void CRenderMgr::Init()
{
	//// Create & Bind CB
	//CreateConstantBuffer();
	//// Bind Constant Buffer	
	//BindConstantBuffer(eShaderStage::VS, mCB);

	// Set Sampler
	SetUpState();

	// Create Mesh
	std::shared_ptr<CMesh> mesh = std::make_shared<CMesh>();
	mesh->BindBuffer();
	CResourceMgr::GetInst()->Insert(L"Mesh", mesh);

	// Create Shader
	std::shared_ptr<CShader> shader = std::make_shared<CShader>();
	CResourceMgr::GetInst()->Insert(L"Shader", shader);


	// Create Texture
	std::shared_ptr<CTexture> texture = std::make_shared<CTexture>();
	texture->ResourceLoad(L"Smile", L"..\\Resource\\Texture\\Smile.png");
	CResourceMgr::GetInst()->Insert(L"Texture", texture);

	// Create Material
	std::shared_ptr<CMaterial> material = std::make_shared<CMaterial>();
	material->SetShader(shader);
	material->SetTexture(texture);
	CResourceMgr::GetInst()->Insert(L"Material", material);

	// Create Scene
	CSceneMgr::GetInst()->AddScene<CPlayScene>(L"PlayScene");
}

void CRenderMgr::Update()
{
	CSceneMgr::GetInst()->Update();
}

void CRenderMgr::LateUpdate()
{
	CSceneMgr::GetInst()->LateUpdate();
}

void CRenderMgr::Render()
{
	CSceneMgr::GetInst()->Render();

	//CCameraMgr::GetInst()->Render();
}

//bool CRenderMgr::CreateConstantBuffer()
//{
//	// Set Constant Buffer Description
//	mCB->SetConstantType(eCBType::Transform);
//
//	// Create Constant Buffer
//	CDevice::GetInst()->GetDevice()->CreateBuffer(mCB->GetConstantDesc(), nullptr, mCB->GetConstantBuffer().GetAddressOf());
//	
//	// Set Constant Buffer
//	Vector4 pos(0.3f, 0.0f, 0.0f, 1.0f);
//
//	D3D11_MAPPED_SUBRESOURCE subRes = {};
//	mGraphicContext->Map(mCB->GetConstantBuffer().Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &subRes);
//	memcpy(subRes.pData, &pos, mCB->GetConstantDesc()->ByteWidth);
//	mGraphicContext->Unmap(mCB->GetConstantBuffer().Get(), 0);
//
//	return true;
//}

void CRenderMgr::BindConstantBuffer(eShaderStage stage, CConstantBuffer* tCB)
{
	switch (stage)
	{
	case eShaderStage::VS:
		mGraphicContext->VSSetConstantBuffers((UINT)tCB->GetConstantType(), 1, (tCB->GetConstantBuffer().GetAddressOf()));
		break;
	case eShaderStage::HS:
		mGraphicContext->HSSetConstantBuffers((UINT)tCB->GetConstantType(), 1, (tCB->GetConstantBuffer().GetAddressOf()));
		break;
	case eShaderStage::DS:
		mGraphicContext->DSSetConstantBuffers((UINT)tCB->GetConstantType(), 1, (tCB->GetConstantBuffer().GetAddressOf()));
		break;
	case eShaderStage::GS:
		mGraphicContext->GSSetConstantBuffers((UINT)tCB->GetConstantType(), 1, (tCB->GetConstantBuffer().GetAddressOf()));
		break;
	case eShaderStage::PS:
		mGraphicContext->PSSetConstantBuffers((UINT)tCB->GetConstantType(), 1, (tCB->GetConstantBuffer().GetAddressOf()));
		break;
	case eShaderStage::CS:
		mGraphicContext->CSSetConstantBuffers((UINT)tCB->GetConstantType(), 1, (tCB->GetConstantBuffer().GetAddressOf()));
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