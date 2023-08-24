#include "CTexture.h"

CTexture::CTexture()
	: CResource(eResourceType::Texture)
	, mDesc{}
{
	mGraphicContext = CDevice::GetInst()->GetContext();
}

CTexture::~CTexture()
{
}

HRESULT CTexture::ResourceLoad(const std::wstring name, const std::wstring& path)
{
	this->SetName(name);

	wchar_t szExtension[50] = {};
	_wsplitpath_s(path.c_str(), nullptr, 0, nullptr, 0, nullptr, 0, szExtension, 50);

	std::wstring extension = szExtension;
	if (extension == L".dds" || extension == L".DDS")
	{
		if (FAILED(LoadFromDDSFile(path.c_str(), DDS_FLAGS::DDS_FLAGS_NONE, nullptr, mImage)))
			return S_FALSE;
	}
	else if (extension == L".tga" || extension == L".TGA")
	{
		if (FAILED(LoadFromTGAFile(path.c_str(), nullptr, mImage)))
			return S_FALSE;
	}
	else // WIC (png, jpg, jpeg, bmp )
	{
	/*	if (FAILED(LoadFromWICFile(path.c_str(), WIC_FLAGS::WIC_FLAGS_IGNORE_SRGB, nullptr, mImage)))
			return S_FALSE;*/

		HRESULT hr = LoadFromWICFile(path.c_str(), WIC_FLAGS::WIC_FLAGS_IGNORE_SRGB, nullptr, mImage);
		int a = 0;
	}

	CreateShaderResourceView
	(
		CDevice::GetInst()->GetDevice()
		, mImage.GetImages()
		, mImage.GetImageCount()
		, mImage.GetMetadata()
		, mSRV.GetAddressOf()
	);
	mSRV->GetResource((ID3D11Resource**)mTexture.GetAddressOf());

	return S_OK;
}

void CTexture::BindShaderResource(eShaderStage stage, UINT startSlot)
{
	CDevice::GetInst()->BindShaderResource(stage, startSlot, mSRV.GetAddressOf());
}

void CTexture::Clear()
{
	ID3D11ShaderResourceView* srv = nullptr;

	mGraphicContext->VSSetShaderResources((UINT)eShaderStage::VS, 1, &srv);
	mGraphicContext->HSSetShaderResources((UINT)eShaderStage::HS, 1, &srv);
	mGraphicContext->DSSetShaderResources((UINT)eShaderStage::DS, 1, &srv);
	mGraphicContext->GSSetShaderResources((UINT)eShaderStage::GS, 1, &srv);
	mGraphicContext->PSSetShaderResources((UINT)eShaderStage::PS, 1, &srv);
	mGraphicContext->CSSetShaderResources((UINT)eShaderStage::CS, 1, &srv);
}
