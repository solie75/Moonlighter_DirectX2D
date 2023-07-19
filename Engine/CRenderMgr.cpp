#include "CRenderMgr.h"
#include "CTexture.h"
#include "CPlayScene.h"

CRenderMgr::CRenderMgr()
	: mCB{}
	, cameras{}
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


	// Load Texture and Mateiral
	{ // Test
		LoadTexture(L"Link", L"..\\Resource\\Texture\\Link.png");
		LoadMaterial(shader, L"Link", eRenderingMode::Opaque);

		LoadTexture(L"Smile", L"..\\Resource\\Texture\\Smile.png");
		LoadMaterial(shader, L"Smile", eRenderingMode::CutOut);
	}
	{ // will
		LoadTexture(L"Will", L"..\\Resource\\Texture\\Will.png");
		LoadMaterial(shader, L"Will", eRenderingMode::CutOut);
	}
	{ // UI
		LoadTexture(L"UI_Base_Circle", L"..\\Resource\\Texture\\UI_Base_Circle.png");
		LoadMaterial(shader, L"UI_Base_Circle", eRenderingMode::CutOut);

		LoadTexture(L"HealthBar_Circle", L"..\\Resource\\Texture\\HealthBar_Circle.png");
		LoadMaterial(shader, L"HealthBar_Circle", eRenderingMode::CutOut);

		LoadTexture(L"HealthBar_Base", L"..\\Resource\\Texture\\HealthBar_Base.png");
		LoadMaterial(shader, L"HealthBar_Base", eRenderingMode::CutOut);

		LoadTexture(L"Gold4", L"..\\Resource\\Texture\\Gold4.png");
		LoadMaterial(shader, L"Gold4", eRenderingMode::CutOut);

		LoadTexture(L"Health_Icon", L"..\\Resource\\Texture\\Health_Icon.png");
		LoadMaterial(shader, L"Health_Icon", eRenderingMode::CutOut);

		LoadTexture(L"HUD_Set1", L"..\\Resource\\Texture\\HUD_Set1.png");
		LoadMaterial(shader, L"HUD_Set1", eRenderingMode::CutOut);

		LoadTexture(L"HUD_Set2", L"..\\Resource\\Texture\\HUD_Set2.png");
		LoadMaterial(shader, L"HUD_Set2", eRenderingMode::CutOut);

		LoadTexture(L"YesNo_Circle", L"..\\Resource\\Texture\\YesNo_Circle.png");
		LoadMaterial(shader, L"YesNo_Circle", eRenderingMode::CutOut);
	}
	{ // Start Menu
		LoadTexture(L"Start_Intro_Door_Left", L"..\\Resource\\Texture\\Start_Intro_Door_Left.png");
		LoadMaterial(shader, L"Start_Intro_Door_Left", eRenderingMode::CutOut);

		LoadTexture(L"Start_Intro_Door_Right", L"..\\Resource\\Texture\\Start_Intro_Door_Right.png");
		LoadMaterial(shader, L"Start_Intro_Door_Right", eRenderingMode::CutOut);
	}
	{ // Village
		LoadTexture(L"Village_Background", L"..\\Resource\\Texture\\Village_Background.png");
		LoadMaterial(shader, L"Village_Background", eRenderingMode::CutOut);

		LoadTexture(L"WillsHome", L"..\\Resource\\Texture\\WillsHome.png");
		LoadMaterial(shader, L"WillsHome", eRenderingMode::CutOut);

		LoadTexture(L"Village_House_01", L"..\\Resource\\Texture\\Village_House_01.png");
		LoadMaterial(shader, L"Village_House_01", eRenderingMode::CutOut);

		LoadTexture(L"Village_Blacksmith_House_old", L"..\\Resource\\Texture\\Village_Blacksmith_House_old.png");
		LoadMaterial(shader, L"Village_Blacksmith_House_old", eRenderingMode::CutOut);

		LoadTexture(L"Village_Blacksmith_Roof_old", L"..\\Resource\\Texture\\Village_Blacksmith_Roof_old.png");
		LoadMaterial(shader, L"Village_Blacksmith_Roof_old", eRenderingMode::CutOut);

		LoadTexture(L"Village_Blacksmith_Stand1_old", L"..\\Resource\\Texture\\Village_Blacksmith_Stand1_old.png");
		LoadMaterial(shader, L"Village_Blacksmith_Stand1_old", eRenderingMode::CutOut);

		LoadTexture(L"Village_Blacksmith_Stand2_old", L"..\\Resource\\Texture\\Village_Blacksmith_Stand2_old.png");
		LoadMaterial(shader, L"Village_Blacksmith_Stand2_old", eRenderingMode::CutOut);

		LoadTexture(L"Village_Blacksmith_Fence", L"..\\Resource\\Texture\\Village_Blacksmith_Fence.png");
		LoadMaterial(shader, L"Village_Blacksmith_Fence", eRenderingMode::CutOut);

		LoadTexture(L"Village_House_06", L"..\\Resource\\Texture\\Village_House_06.png");
		LoadMaterial(shader, L"Village_House_06", eRenderingMode::CutOut);

		LoadTexture(L"Village_House_05", L"..\\Resource\\Texture\\Village_House_05.png");
		LoadMaterial(shader, L"Village_House_05", eRenderingMode::CutOut);

		LoadTexture(L"Village_House_02", L"..\\Resource\\Texture\\Village_House_02.png");
		LoadMaterial(shader, L"Village_House_02", eRenderingMode::CutOut);

		LoadTexture(L"Village_Awning", L"..\\Resource\\Texture\\Village_Awning.png");
		LoadMaterial(shader, L"Village_Awning", eRenderingMode::CutOut);

		LoadTexture(L"Village_Board", L"..\\Resource\\Texture\\Village_Board.png");
		LoadMaterial(shader, L"Village_Board", eRenderingMode::CutOut);

		LoadTexture(L"Village_Fence_Column", L"..\\Resource\\Texture\\Village_Fence_Column.png");
		LoadMaterial(shader, L"Village_Fence_Column", eRenderingMode::CutOut);

		LoadTexture(L"Village_Fence_Row", L"..\\Resource\\Texture\\Village_Fence_Row.png");
		LoadMaterial(shader, L"Village_Fence_Row", eRenderingMode::CutOut);

		LoadTexture(L"Village_Witch_House_old", L"..\\Resource\\Texture\\Village_Witch_House_old.png");
		LoadMaterial(shader, L"Village_Witch_House_old", eRenderingMode::CutOut);

		LoadTexture(L"Village_Witch_Roof_old", L"..\\Resource\\Texture\\Village_Witch_Roof_old.png");
		LoadMaterial(shader, L"Village_Witch_Roof_old", eRenderingMode::CutOut);

		LoadTexture(L"Village_Witch_Table_old", L"..\\Resource\\Texture\\Village_Witch_Table_old.png");
		LoadMaterial(shader, L"Village_Witch_Table_old", eRenderingMode::CutOut);

		LoadTexture(L"Village_Witch_Storage_old", L"..\\Resource\\Texture\\Village_Witch_Storage_old.png");
		LoadMaterial(shader, L"Village_Witch_Storage_old", eRenderingMode::CutOut);

		LoadTexture(L"Village_Rival_House_old", L"..\\Resource\\Texture\\Village_Rival_House_old.png");
		LoadMaterial(shader, L"Village_Rival_House_old", eRenderingMode::CutOut);

		LoadTexture(L"Village_Rival_Roof_old", L"..\\Resource\\Texture\\Village_Rival_Roof_old.png");
		LoadMaterial(shader, L"Village_Rival_Roof_old", eRenderingMode::CutOut);

		LoadTexture(L"Village_Rival_Fountain_old", L"..\\Resource\\Texture\\Village_Rival_Fountain_old.png");
		LoadMaterial(shader, L"Village_Rival_Fountain_old", eRenderingMode::CutOut);
	}
	{ // shop
		LoadTexture(L"Shop_Background", L"..\\Resource\\Texture\\Shop_Background.png");
		LoadMaterial(shader, L"Shop_Background", eRenderingMode::CutOut);
	}
	
	// Create Scene
	CSceneMgr::GetInst()->AddScene<CPlayScene>(L"PlayScene");
}

void CRenderMgr::LoadTexture(const std::wstring& textureName, const std::wstring& path)
{
	std::shared_ptr<CTexture> tex = std::make_shared<CTexture>();
	tex->ResourceLoad(textureName, path);
	CResourceMgr::GetInst()->Insert(textureName, tex);
}

void CRenderMgr::LoadMaterial(std::shared_ptr<CShader> shader,const std::wstring& textureName, eRenderingMode renderMode)
{
	std::shared_ptr<CTexture> tex = CResourceMgr::GetInst()->Find<CTexture>(textureName);

	std::shared_ptr<CMaterial> mt = std::make_shared<CMaterial>();
	mt->SetShader(shader);
	mt->SetTexture(tex);
	mt->SetRenderMode(renderMode);
	CResourceMgr::GetInst()->Insert(L"mt_" + textureName, mt);

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
	for (CCamera* cam : cameras)
	{
		if (cam == nullptr)
		{
			continue;
		}
		cam->Render();
	}
	cameras.clear();
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