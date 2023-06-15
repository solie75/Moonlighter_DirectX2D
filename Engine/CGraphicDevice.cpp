#include "CGraphicDevice.h"

CGraphicDevice::CGraphicDevice()
	: DeviceHeight(-1)
	, DeviceWidth(-1)
	, mViewPort{}
	, mHwnd(nullptr)
{
}

CGraphicDevice::~CGraphicDevice()
{
}

int CGraphicDevice::GraphicInit(HWND _hWnd, UINT _width, UINT _height)
{
	DeviceHeight = _height;
	DeviceWidth = _width;

	mHwnd = _hWnd;

	// create device, context
	D3D_FEATURE_LEVEL featureLevel = (D3D_FEATURE_LEVEL)0;

	D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, D3D11_CREATE_DEVICE_DEBUG,
		nullptr, 0, D3D11_SDK_VERSION, mDevice.GetAddressOf(),
		&featureLevel, mContext.GetAddressOf());

	// create swapchian
	DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
	swapChainDesc.OutputWindow = mHwnd;
	swapChainDesc.Windowed = true;
	swapChainDesc.BufferCount = 2;
	swapChainDesc.BufferDesc.Width = DeviceWidth;
	swapChainDesc.BufferDesc.Height = DeviceHeight;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER::DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT::DXGI_SWAP_EFFECT_DISCARD;

	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.Flags = 0;

	ComPtr<IDXGIDevice>  pDXGIDevice = nullptr;
	ComPtr<IDXGIAdapter> pAdapter = nullptr;
	ComPtr<IDXGIFactory> pFactory = nullptr;

	if (FAILED(mDevice->QueryInterface(__uuidof(IDXGIDevice), (void**)pDXGIDevice.GetAddressOf())))
	{
		return false;
	}
	if (FAILED(pDXGIDevice->GetParent(__uuidof(IDXGIAdapter), (void**)pAdapter.GetAddressOf())))
	{
		return false;
	}
	if (FAILED(pAdapter->GetParent(__uuidof(IDXGIFactory), (void**)pFactory.GetAddressOf())))
	{
		return false;
	}
	if (FAILED(pFactory->CreateSwapChain(mDevice.Get(), &swapChainDesc, mSwapChain.GetAddressOf())))
	{
		return false;
	}

	// RenderTarget Buffer 持失
	if (FAILED(mSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)mRenderTarget.GetAddressOf())))
	{
		return;
	}

	// rendertarget view 持失
	mDevice->CreateRenderTargetView((ID3D11Resource*)mRenderTarget.Get(), nullptr, mRenderTargetView.GetAddressOf());

	// Depthstencil Buffer 持失
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

	D3D11_SUBRESOURCE_DATA data;
	return true;
}

bool CGraphicDevice::CreateTexture(const D3D11_TEXTURE2D_DESC* desc, void* data)
{
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

	D3D11_SUBRESOURCE_DATA data;

	return false;
}
