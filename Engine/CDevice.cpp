#include "CDevice.h"
#include "CTexture.h"


CDevice::CDevice()
	: DeviceHeight(-1)
	, DeviceWidth(-1)
	, mViewPort{}
	, mHwnd(nullptr)
{
}

CDevice::~CDevice()
{
}

bool CDevice::GraphicInit(HWND _hWnd, UINT _width, UINT _height)
{
	DeviceHeight = _height;
	DeviceWidth = _width;

	mHwnd = _hWnd;

	// Create device, context
	D3D_FEATURE_LEVEL featureLevel = (D3D_FEATURE_LEVEL)0;

	D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE
		, nullptr, D3D11_CREATE_DEVICE_DEBUG
		,nullptr, 0
		, D3D11_SDK_VERSION, mDevice.GetAddressOf()
		,&featureLevel, mContext.GetAddressOf());

	
	CreateSwapChain();

	CreateBufferAndView();

	return true;
}


bool CDevice::CreateSwapChain()
{
	// Create IDXGI
	ComPtr<IDXGIDevice>  pDXGIDevice = nullptr;
	ComPtr<IDXGIAdapter> pDXGIAdapter = nullptr;
	ComPtr<IDXGIFactory> pDXGIFactory = nullptr;

	if (FAILED(mDevice->QueryInterface(__uuidof(IDXGIDevice), (void**)pDXGIDevice.GetAddressOf())))
	{
		return false;
	}
	if (FAILED(pDXGIDevice->GetParent(__uuidof(IDXGIAdapter), (void**)pDXGIAdapter.GetAddressOf())))
	{
		return false;
	}
	if (FAILED(pDXGIAdapter->GetParent(__uuidof(IDXGIFactory), (void**)pDXGIFactory.GetAddressOf())))
	{
		return false;
	}

	// Create SwapChain
	DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
	swapChainDesc.OutputWindow = mHwnd;
	swapChainDesc.Windowed = true;
	swapChainDesc.BufferCount = 2;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.BufferDesc.Width = DeviceWidth;
	swapChainDesc.BufferDesc.Height = DeviceHeight;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 240;
	swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER::DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT::DXGI_SWAP_EFFECT_FLIP_DISCARD;

	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;

	if (FAILED(pDXGIFactory->CreateSwapChain(pDXGIDevice.Get(), &swapChainDesc, mSwapChain.GetAddressOf())))
	{
		return false;
	}

	return true;
}

// 기존에 RenderTarget 과 DepthStencil 을 만들던 함수이다.
bool CDevice::CreateBufferAndView() // 이 함수 대신 CreateTexture2D 를 사용한다.
{
	// Create RenderTarget Buffer (Get rendertarget by swapchain)
	/*if (FAILED(mSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)mRenderTarget.GetAddressOf())))
	{
		return false;
	}*/

	// Create Rendertarget view
	/*HRESULT hr = mDevice->CreateRenderTargetView(mRenderTarget.Get(), nullptr, mRenderTargetView.GetAddressOf());*/

	// Compute Shader 이후
	mRenderTarget = std::make_shared<CTexture>();
	mDepthStencil = std::make_shared<CTexture>();

	Microsoft::WRL::ComPtr<ID3D11Texture2D> renderTarget = nullptr;

	if (FAILED(mSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)renderTarget.GetAddressOf())))
	{
		return false;
	}

	mRenderTarget->SetTexture(renderTarget);

	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> renderTargetView = nullptr;
	HRESULT hr = mDevice->CreateRenderTargetView((ID3D11Resource*)mRenderTarget->GetTexture().Get(), nullptr, renderTargetView.GetAddressOf());

	mRenderTarget->SetRTV(renderTargetView);


	// Create DepthStencil Buffer
	D3D11_TEXTURE2D_DESC depthStencilDesc = {};
	depthStencilDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_DEPTH_STENCIL;
	depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
	depthStencilDesc.CPUAccessFlags = 0;

	depthStencilDesc.Format = DXGI_FORMAT::DXGI_FORMAT_D24_UNORM_S8_UINT;

	depthStencilDesc.Width = DeviceWidth;
	depthStencilDesc.Height = DeviceHeight;
	depthStencilDesc.ArraySize = 1;

	depthStencilDesc.SampleDesc.Count = 1;
	depthStencilDesc.SampleDesc.Quality = 0;

	depthStencilDesc.MiscFlags = 0;
	depthStencilDesc.MipLevels = 0;

	// ComputeShader 이후
	Microsoft::WRL::ComPtr<ID3D11Texture2D> depthStencilBuffer = nullptr;
	if (!CreateTexture2D(&depthStencilDesc, nullptr, depthStencilBuffer.GetAddressOf()))
	{
		return 0;
	}

	mDepthStencil->SetTexture(depthStencilBuffer);

	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> mDepthStencilView = nullptr;
	if (!CreateDepthStencilView(depthStencilBuffer.Get(), nullptr, mDepthStencilView.GetAddressOf()))
	{
		return 0;
	}

	mDepthStencil->SetDSV(mDepthStencilView);


	//if (FAILED(mDevice->CreateTexture2D(&depthStencilDesc, nullptr, mDepthStencilBuffer.ReleaseAndGetAddressOf())))
	//{
	//	return false;
	//}

	//// Create DepthStencil View
	//if (FAILED(mDevice->CreateDepthStencilView(mDepthStencilBuffer.Get(), nullptr, mDepthStencilView.GetAddressOf())))
	//{
	//	return false;
	//}

	return true;
}

bool CDevice::CreateTexture2D(const D3D11_TEXTURE2D_DESC* desc, void* data, ID3D11Texture2D** ppTexture2D)
{
	if (FAILED(mDevice->CreateTexture2D(desc, nullptr, ppTexture2D)))
	{
		return false;
	}
	return true;
}

bool CDevice::CreateDepthStencilView(ID3D11Resource* pResource, const D3D11_DEPTH_STENCIL_VIEW_DESC* pDesc, ID3D11DepthStencilView** ppDepthStencilView)
{
	if (FAILED(mDevice->CreateDepthStencilView(pResource, pDesc, ppDepthStencilView)))
	{
		return false;
	}

	return true;
}

bool CDevice::CreateShaderResourceView(ID3D11Resource* pResource, const D3D11_SHADER_RESOURCE_VIEW_DESC* pDesc, ID3D11ShaderResourceView** ppSRView)
{
	if (FAILED(mDevice->CreateShaderResourceView(pResource, pDesc, ppSRView)))
	{
		return false;
	}

	return true;
}

bool CDevice::CreateRenderTargetView(ID3D11Resource* pResource, const D3D11_RENDER_TARGET_VIEW_DESC* pDesc, ID3D11RenderTargetView** ppRTView)
{
	if (FAILED(mDevice->CreateRenderTargetView(pResource, pDesc, ppRTView)))
	{
		return false;
	}
	return true;
}

bool CDevice::CreateUnorderedAccessView(ID3D11Resource* pResource, const D3D11_UNORDERED_ACCESS_VIEW_DESC* pDesc, ID3D11UnorderedAccessView** ppUAView)
{
	if (FAILED(mDevice->CreateUnorderedAccessView(pResource, pDesc, ppUAView)))
	{
		return false;
	}

	return true;
}

bool CDevice::CrateComputeShader(const void* pShaderBytecode, SIZE_T BytecodeLength, ID3D11ComputeShader** ppComputeShader)
{
	if (FAILED(mDevice->CreateComputeShader(pShaderBytecode, BytecodeLength, nullptr, ppComputeShader)))
	{
		return false;
	}

	return true;
}

bool CDevice::CreateGeometryShader(const void* pShaderBytecode, SIZE_T BytecodeLength, ID3D11GeometryShader** ppGeometryShader)
{
	if (FAILED(mDevice->CreateGeometryShader(pShaderBytecode, BytecodeLength, nullptr, ppGeometryShader)))
	{
		return false;
	}

	return true;
}

bool CDevice::CompileFromfile(const std::wstring& fileName, const std::string& funcName, const std::string& version, ID3DBlob** ppCode)
{
	ID3DBlob* errorBlob = nullptr;
	D3DCompileFromFile(fileName.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE
		, funcName.c_str(), version.c_str(), 0, 0, ppCode, &errorBlob);

	if (errorBlob)
	{
		OutputDebugStringA((char*)(errorBlob->GetBufferPointer()));
		errorBlob->Release();
		errorBlob = nullptr;
	}
	return false;
}


void CDevice::ClearRenderTarget()
{
	// rendertarget clear
	/*FLOAT bgColor[4] = { 0.2f, 0.2f, 0.2f, 1.0f };
	mContext->ClearRenderTargetView(mRenderTargetView.Get(), bgColor);
	mContext->ClearDepthStencilView(mDepthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, (UINT8)0.0f);
	mContext->OMSetRenderTargets(1, mRenderTargetView.GetAddressOf(), mDepthStencilView.Get());*/\

	// Compute 이후
	FLOAT bgColor[4] = { 0.2f, 0.2f, 0.2f, 1.0f };
	mContext->ClearRenderTargetView(mRenderTarget->GetRTV().Get(), bgColor);
	mContext->ClearDepthStencilView(mDepthStencil->GetDSV().Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, (UINT8)0.0f);
	mContext->OMSetRenderTargets(1, mRenderTarget->GetRTV().GetAddressOf(), mDepthStencil->GetDSV().Get());
}

void CDevice::BindShaderResource(eShaderStage stage, UINT startSlot, ID3D11ShaderResourceView** ppSRV)
{
	switch (stage)
	{
	case eShaderStage::VS:
		mContext->VSSetShaderResources(startSlot, 1, ppSRV);
		break;
	case eShaderStage::HS:
		mContext->HSSetShaderResources(startSlot, 1, ppSRV);
		break;
	case eShaderStage::DS:
		mContext->DSSetShaderResources(startSlot, 1, ppSRV);
		break;
	case eShaderStage::GS:
		mContext->GSSetShaderResources(startSlot, 1, ppSRV);
		break;
	case eShaderStage::PS:
		mContext->PSSetShaderResources(startSlot, 1, ppSRV);
		break;
	case eShaderStage::CS:
		mContext->CSSetShaderResources(startSlot, 1, ppSRV);
		break;
	case eShaderStage::End:
		break;
	default:
		break;
	}
}

void CDevice::BindUnorderedAccess(UINT slot, ID3D11UnorderedAccessView** ppUnorrderedAccessViews, const UINT* pUAVInitialCounts)
{
	mContext->CSSetUnorderedAccessViews(slot, 1, ppUnorrderedAccessViews, pUAVInitialCounts);
}

void CDevice::BindComputeShader(ID3D11ComputeShader* pComputeShader)
{
	mContext->CSSetShader(pComputeShader, 0, 0);
}

void CDevice::BindHullShader(ID3D11HullShader* pHullShader)
{
	mContext->HSSetShader(pHullShader, 0, 0);
}

void CDevice::BindDomainShader(ID3D11DomainShader* pDomainShader)
{
	mContext->DSSetShader(pDomainShader, 0, 0);
}

void CDevice::BindGeometryShader(ID3D11GeometryShader* pGeometryShader)
{
	mContext->GSSetShader(pGeometryShader, 0, 0);
}

void CDevice::Dispatch(UINT ThreadGroupCountX, UINT ThreadGroupCountY, UINT ThreadGroupCountZ)
{
	mContext->Dispatch(ThreadGroupCountX, ThreadGroupCountY, ThreadGroupCountZ);
}

void CDevice::UpdateViewPort()
{
	RECT winRect = {};
	GetClientRect(mHwnd, &winRect);
	mViewPort = {
			0.0f, 0.0f
			, (float)(winRect.right - winRect.left)
			, (float)(winRect.bottom - winRect.top)
			, 0.0f, 1.0f
	};

	mContext->RSSetViewports(1, &mViewPort);
}

void CDevice::DrawIndexedInstanced(UINT IndexCountPerInstance, UINT InstanceCount, UINT StartIndexLocation, INT BaseVertexLocation, UINT StartInstanceLocation)
{
	mContext->DrawIndexedInstanced(IndexCountPerInstance, InstanceCount, StartIndexLocation, BaseVertexLocation, StartInstanceLocation);
}




//bool CDevice::CreateTexture(const D3D11_TEXTURE2D_DESC* desc, void* data)
//{
//	return false;
//}
//
//
//bool CDevice::CreateVertexShader()
//{
//	return false;
//}
//
//bool CDevice::CreatePixelShader()
//{
//	return false;
//}
//
//bool CDevice::CreateInputLayout()
//{
//	return false;
//}
