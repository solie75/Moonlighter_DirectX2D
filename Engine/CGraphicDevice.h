#pragma once

#include "Header.h"
#include "CSingleton.h"

class CGraphicDevice
	: public CSingleton<CGraphicDevice>
{
private:
	ComPtr<ID3D11Device> mDevice;
	ComPtr<ID3D11DeviceContext> mContext;
	ComPtr<IDXGISwapChain> mSwapChain;


	ComPtr<ID3D11Texture2D> mRenderTarget;
	ComPtr<ID3D11RenderTargetView> mRenderTargetView;
	ComPtr<ID3D11Texture2D> mDepthStencilBuffer;
	ComPtr<ID3D11DepthStencilView> mDepthStencilView;

	D3D11_VIEWPORT mViewPort;

	UINT DeviceHeight;
	UINT DeviceWidth;

	HWND mHwnd;
public:
	CGraphicDevice();
	~CGraphicDevice();

	bool GraphicInit(HWND _hWnd, UINT _width, UINT _height);
	bool CreateSwapChain();
	bool CreateBuffer();
	bool CreateTexture(const D3D11_TEXTURE2D_DESC* desc, void* data);
	bool CreateVertexShader();
	bool CreatePixelShader();
	bool CreateInputLayout();

	void ClearRenderTarget();

	ID3D11Device* GetDevice() { return mDevice.Get(); }
	//ID3D11DeviceContext* GetDeviceContext() { return mContext.Get(); }
};

