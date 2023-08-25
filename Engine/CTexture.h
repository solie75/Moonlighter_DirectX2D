#pragma once
#include "CDevice.h"
#include "Graphic.h"
#include "CResource.h"

#include "../External/DirectXTex/Include/DirectXtex.h"
#include "../External/DirectXTex/Include/DirectXtex.inl"

#ifdef _DEBUG
#pragma comment(lib, "..\\External\\DirectXTex\\Lib\\Debug\\DirectXTex.lib")
#else
#pragma comment(lib, "..\\External\\DirectXTex\\Lib\\Release\\DirectXTex.lib")
#endif

class CTexture : public CResource
{
private:
	DirectX::ScratchImage mImage;
	ComPtr<ID3D11Texture2D> mTexture;
	ComPtr<ID3D11ShaderResourceView> mSRV;
	D3D11_TEXTURE2D_DESC mDesc;
	ID3D11DeviceContext* mGraphicContext;

	// Compute Shader 위한 텍스쳐 구조 변경
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> mRTV;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> mDSV;
	Microsoft::WRL::ComPtr<ID3D11UnorderedAccessView> mUAV;


public:
	CTexture();
	~CTexture();

	virtual HRESULT ResourceLoad(const std::wstring name, const std::wstring& path) override;
	void BindShaderResource(eShaderStage stage, UINT startSlot);

	size_t GetWidth() { return mImage.GetMetadata().width; }
	size_t GetHeight() { return mImage.GetMetadata().height; }

	const Image* GetScratchImage() { return mImage.GetImages(); }
	void InitScratImage(size_t width, size_t hight) {	mImage.Initialize2D(DXGI_FORMAT_R8G8B8A8_UNORM, width, hight, 1, 1); }

	//ComPtr<ID3D11ShaderResourceView> GetSRV() { return mSRV; }

	void CreateSRV() // CreateAtlas 의 atlasTex->CreateSRV() 로 사용되고 있음
	{ 
		CreateShaderResourceView
		(
			CDevice::GetInst()->GetDevice()
			, mImage.GetImages()
			, mImage.GetImageCount()
			, mImage.GetMetadata()
			, mSRV.GetAddressOf()
		);
		mSRV->GetResource((ID3D11Resource**)mTexture.GetAddressOf());
	}

	void Clear();

	// Compute Shader 위한 텍스쳐 구조 변경
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> GetRTV() { return mRTV; }
	void SetRTV(Microsoft::WRL::ComPtr<ID3D11RenderTargetView> rtv) { mRTV = rtv; }

	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> GetDSV() { return  mDSV; }
	void SetDSV(Microsoft::WRL::ComPtr<ID3D11DepthStencilView> dsv) { mDSV = dsv; }

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> GetSRV() { return  mSRV; }
	Microsoft::WRL::ComPtr<ID3D11UnorderedAccessView> GetUAV() { return  mUAV; }

	Microsoft::WRL::ComPtr<ID3D11Texture2D> GetTexture() { return mTexture; }
	void SetTexture(Microsoft::WRL::ComPtr<ID3D11Texture2D> texture) { mTexture = texture; }

	bool Create(UINT width, UINT height, DXGI_FORMAT format, UINT bindFlag);
};

