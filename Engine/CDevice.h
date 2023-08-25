#pragma once

#include "Header.h"
#include "Graphic.h"
#include "CSingleton.h"
//#include "CTexture.h"
class CTexture;

class CDevice
	: public CSingleton<CDevice>
{
private:
	ComPtr<ID3D11Device> mDevice;
	ComPtr<ID3D11DeviceContext> mContext;
	ComPtr<IDXGISwapChain> mSwapChain;


	//ComPtr<ID3D11Texture2D> mRenderTarget;
	//ComPtr<ID3D11RenderTargetView> mRenderTargetView;
	//ComPtr<ID3D11Texture2D> mDepthStencilBuffer;
	//ComPtr<ID3D11DepthStencilView> mDepthStencilView;

	D3D11_VIEWPORT mViewPort;

	UINT DeviceHeight;
	UINT DeviceWidth;

	HWND mHwnd;

	// compute Shader 이후
	// 하나의 CTexture 가 view 와 Texture2D 모두를 가지고 있다.
	std::shared_ptr<CTexture> mRenderTarget;
	std::shared_ptr<CTexture> mDepthStencil;

public:
	CDevice();
	~CDevice();

	bool GraphicInit(HWND _hWnd, UINT _width, UINT _height);
	bool CreateSwapChain();
	bool CreateBufferAndView();
	bool CreateTexture2D(const D3D11_TEXTURE2D_DESC* desc, void* data, ID3D11Texture2D** ppTexture2D);
	bool CreateDepthStencilView(ID3D11Resource* pResource, const D3D11_DEPTH_STENCIL_VIEW_DESC* pDesc, ID3D11DepthStencilView** ppDepthStencilView);
	bool CreateShaderResourceView(ID3D11Resource* pResource, const D3D11_SHADER_RESOURCE_VIEW_DESC* pDesc, ID3D11ShaderResourceView** ppSRView);
	bool CreateRenderTargetView(ID3D11Resource* pResource, const D3D11_RENDER_TARGET_VIEW_DESC* pDesc, ID3D11RenderTargetView** ppRTView);
	bool CreateUnorderedAccessView(ID3D11Resource* pResource, const D3D11_UNORDERED_ACCESS_VIEW_DESC* pDesc, ID3D11UnorderedAccessView** ppUAView);
	bool CrateComputeShader(const void* pShaderBytecode, SIZE_T BytecodeLength, ID3D11ComputeShader** ppComputeShader);
	bool CompileFromfile(const std::wstring& fileName, const std::string& funcName, const std::string& version, ID3DBlob** ppCode);

	void ClearRenderTarget();

	ID3D11Device* GetDevice() { return mDevice.Get(); }
	ID3D11DeviceContext* GetContext() { return mContext.Get(); }
	IDXGISwapChain* GetSwapChain() { return mSwapChain.Get(); }

	UINT GetDeviceHeight() { return DeviceHeight; }
	UINT GetDeviceWidth() { return DeviceWidth; }

	void BindShaderResource(eShaderStage stage, UINT startSlot, ID3D11ShaderResourceView** ppSRV);

	void UpdateViewPort();
};


