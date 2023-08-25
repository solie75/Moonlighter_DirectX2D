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

	mWidth = mImage.GetMetadata().width;
	mHeight = mImage.GetMetadata().height;

	return S_OK;
}

void CTexture::BindShaderResource(eShaderStage stage, UINT startSlot)
{
	CDevice::GetInst()->BindShaderResource(stage, startSlot, mSRV.GetAddressOf());
}

void CTexture::BindUnorderedAccessViews(UINT slot)
{
	UINT i = -1;
	CDevice::GetInst()->BindUnorderedAccess(slot, mUAV.GetAddressOf(), &i);
}

void CTexture::ClearUnorderedAccessViews(UINT slot)
{
	ID3D11UnorderedAccessView* p = nullptr;
	UINT i = -1;
	CDevice::GetInst()->BindUnorderedAccess(slot, &p, &i);
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

bool CTexture::CreateTexture(UINT width, UINT height, DXGI_FORMAT format, UINT bindFlag)
{
	if (mTexture == nullptr)
	{
		mDesc.BindFlags = bindFlag;
		mDesc.Usage = D3D11_USAGE_DEFAULT;
		mDesc.CPUAccessFlags = 0;
		mDesc.Format = format;
		mDesc.Width = width;
		mDesc.Height = height;
		mDesc.ArraySize = 1;

		mDesc.SampleDesc.Count = 1;
		mDesc.SampleDesc.Quality = 0;

		mDesc.MipLevels = 0;
		mDesc.MiscFlags = 0;

		// mImage 의 크기 설정
		mWidth = width;
		mHeight = height;

		if (FAILED(CDevice::GetInst()->GetDevice()->CreateTexture2D(&mDesc, nullptr, mTexture.GetAddressOf())))
		{
			return false;
		}
	}

	if (bindFlag & (UINT)D3D11_BIND_FLAG::D3D11_BIND_DEPTH_STENCIL) // 비트 and 연산자
	{
		if (!CDevice::GetInst()->CreateDepthStencilView(mTexture.Get(), nullptr, mDSV.GetAddressOf()))
		{
			return false;
		}
	}

	if (bindFlag & (UINT)D3D11_BIND_FLAG::D3D11_BIND_SHADER_RESOURCE)
	{
		D3D11_SHADER_RESOURCE_VIEW_DESC tSRVDesc = {};
		tSRVDesc.Format = mDesc.Format;
		tSRVDesc.Texture2D.MipLevels = 1;
		tSRVDesc.Texture2D.MostDetailedMip = 0;
		tSRVDesc.ViewDimension = D3D11_SRV_DIMENSION::D3D11_SRV_DIMENSION_TEXTURE2D;

		if (!CDevice::GetInst()->CreateShaderResourceView(mTexture.Get(), &tSRVDesc, mSRV.GetAddressOf()))
		{
			return false;
		}
	}

	if (bindFlag & (UINT)D3D11_BIND_FLAG::D3D11_BIND_RENDER_TARGET)
	{
		D3D11_RENDER_TARGET_VIEW_DESC tSRVDesc = {};
		tSRVDesc.Format = mDesc.Format;
		tSRVDesc.Texture2D.MipSlice = 0;
		tSRVDesc.ViewDimension = D3D11_RTV_DIMENSION::D3D11_RTV_DIMENSION_TEXTURE2D;

		if (!CDevice::GetInst()->CreateRenderTargetView(mTexture.Get(), nullptr, mRTV.GetAddressOf()))
		{
			return false;
		}
	}

	if (bindFlag & (UINT)D3D11_BIND_FLAG::D3D11_BIND_UNORDERED_ACCESS)
	{
		D3D11_UNORDERED_ACCESS_VIEW_DESC tUAVDesc = {};
		tUAVDesc.Format = mDesc.Format;
		tUAVDesc.Texture2D.MipSlice = 0;
		tUAVDesc.ViewDimension = D3D11_UAV_DIMENSION::D3D11_UAV_DIMENSION_TEXTURE2D;
	
		if (!CDevice::GetInst()->CreateUnorderedAccessView(mTexture.Get(), &tUAVDesc, mUAV.GetAddressOf()))
		{
			return false;
		}
	}

	return true;
}
