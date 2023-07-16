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
	// Set Sampler
	SetUpState();

	// Create Mesh
	std::shared_ptr<CMesh> mesh = std::make_shared<CMesh>();
	mesh->BindBuffer();
	CResourceMgr::GetInst()->Insert(L"Mesh", mesh);

	// Create Shader
	std::shared_ptr<CShader> shader = std::make_shared<CShader>();
	CResourceMgr::GetInst()->Insert(L"Shader", shader);

	// Add Link
	// Create Texture
	std::shared_ptr<CTexture> tex_Link = std::make_shared<CTexture>();
	tex_Link->ResourceLoad(L"Link", L"..\\Resource\\Texture\\Link.png");
	CResourceMgr::GetInst()->Insert(L"Texture", tex_Link);

	// Create Material
	std::shared_ptr<CMaterial> mt_Link = std::make_shared<CMaterial>();
	mt_Link->SetShader(shader);
	mt_Link->SetTexture(tex_Link);
	CResourceMgr::GetInst()->Insert(L"mt_Link", mt_Link);

	// Add Smile
	std::shared_ptr<CTexture> tex_Smile = std::make_shared<CTexture>();
	tex_Smile->ResourceLoad(L"Smile", L"..\\Resource\\Texture\\Smile.png");
	CResourceMgr::GetInst()->Insert(L"Smile", tex_Smile);

	std::shared_ptr<CMaterial> mt_Smile = std::make_shared<CMaterial>();
	mt_Smile->SetShader(shader);
	mt_Smile->SetTexture(tex_Smile);
	CResourceMgr::GetInst()->Insert(L"mt_Smile", mt_Smile);

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
}

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
	// Set Up Sampler State
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



	// Set Up Rasterizer State
	D3D11_RASTERIZER_DESC rasterizerDesc = {};
	rasterizerDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
	rasterizerDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_BACK;
	CDevice::GetInst()->GetDevice()->CreateRasterizerState(&rasterizerDesc
		, rasterizerStates[(UINT)eRSType::SolidBack].GetAddressOf());

	rasterizerDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
	rasterizerDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_FRONT;
	CDevice::GetInst()->GetDevice()->CreateRasterizerState(&rasterizerDesc
		, rasterizerStates[(UINT)eRSType::SolidFront].GetAddressOf());

	rasterizerDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
	rasterizerDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;
	CDevice::GetInst()->GetDevice()->CreateRasterizerState(&rasterizerDesc
		, rasterizerStates[(UINT)eRSType::SolidNone].GetAddressOf());

	rasterizerDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_WIREFRAME;
	rasterizerDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;
	CDevice::GetInst()->GetDevice()->CreateRasterizerState(&rasterizerDesc
		, rasterizerStates[(UINT)eRSType::WireframeNone].GetAddressOf());



	// Set Up DepthStencil State
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc = {};

	//less
	depthStencilDesc.DepthEnable = true;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDesc.StencilEnable = false;

	CDevice::GetInst()->GetDevice()->CreateDepthStencilState(&depthStencilDesc
		, depthStencilStates[(UINT)eDSType::Less].GetAddressOf());

	//Greater
	depthStencilDesc.DepthEnable = true;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_GREATER;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDesc.StencilEnable = false;

	CDevice::GetInst()->GetDevice()->CreateDepthStencilState(&depthStencilDesc
		, depthStencilStates[(UINT)eDSType::Greater].GetAddressOf());

	//No Write
	depthStencilDesc.DepthEnable = true;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
	depthStencilDesc.StencilEnable = false;

	CDevice::GetInst()->GetDevice()->CreateDepthStencilState(&depthStencilDesc
		, depthStencilStates[(UINT)eDSType::NoWrite].GetAddressOf());

	//None
	depthStencilDesc.DepthEnable = false;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
	depthStencilDesc.StencilEnable = false;

	CDevice::GetInst()->GetDevice()->CreateDepthStencilState(&depthStencilDesc
		, depthStencilStates[(UINT)eDSType::None].GetAddressOf());



	// Set Up Blend State
	D3D11_BLEND_DESC blendDesc = {};

	//default
	blendStates[(UINT)eBSType::Default] = nullptr;

	// Alpha Blend
	blendDesc.AlphaToCoverageEnable = false;
	blendDesc.IndependentBlendEnable = false;
	blendDesc.RenderTarget[0].BlendEnable = true;
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	CDevice::GetInst()->GetDevice()->CreateBlendState(&blendDesc
		, blendStates[(UINT)eBSType::AlphaBlend].GetAddressOf());

	// one one
	blendDesc.AlphaToCoverageEnable = false;
	blendDesc.IndependentBlendEnable = false;

	blendDesc.RenderTarget[0].BlendEnable = true;
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	CDevice::GetInst()->GetDevice()->CreateBlendState(&blendDesc
		, blendStates[(UINT)eBSType::OneOne].GetAddressOf());
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