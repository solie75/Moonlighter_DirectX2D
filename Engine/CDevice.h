#pragma once

#include "Header.h"
#include "CSingleton.h"

class CDevice
	: public CSingleton<CDevice>
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
	CDevice();
	~CDevice();

	bool GraphicInit(HWND _hWnd, UINT _width, UINT _height);
	bool CreateSwapChain();
	bool CreateBufferAndView();

	void ClearRenderTarget();


	ID3D11Device* GetDevice() { return mDevice.Get(); }
	ID3D11DeviceContext* GetContext() { return mContext.Get(); }
	IDXGISwapChain* GetSwapChain() { return mSwapChain.Get(); }

	UINT GetDeviceHeight() { return DeviceHeight; }
	UINT GetDeviceWidth() { return DeviceWidth; }


	void UpdateViewPort();
};

