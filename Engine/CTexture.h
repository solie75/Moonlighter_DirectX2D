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

public:
	CTexture();
	~CTexture();

	virtual HRESULT ResourceLoad(const std::wstring name, const std::wstring& path) override;
	void BindShaderResource(eShaderStage stage, UINT startSlot);

	size_t GetWidth() { return mImage.GetMetadata().width; }
	size_t GetHeight() { return mImage.GetMetadata().height; }

	const Image* GetScratchImage() { return mImage.GetImages(); }
	void InitScratImage(size_t width, size_t hight) {	mImage.Initialize2D(DXGI_FORMAT_R8G8B8A8_UNORM, width, hight, 1, 1); }

	ComPtr<ID3D11ShaderResourceView> GetSRV() { return mSRV; }

	void CreateSRV() {
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
};

