#include "CConstantBuffer.h"

CConstantBuffer::CConstantBuffer()
	: mDesc{}
	, mType(eCBType::End)
{
}

CConstantBuffer::~CConstantBuffer()
{
}

bool CConstantBuffer::InitConstantBuffer(size_t size, eCBType type, void* data)
{
	mDesc.ByteWidth = (UINT)size;
	mDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_CONSTANT_BUFFER;
	mDesc.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;
	mDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	mType = type;

	CDevice::GetInst()->GetDevice()->CreateBuffer(&mDesc, nullptr, mBuffer.GetAddressOf());


	// SetData -> SetConstantBuffer ºÎºĞ
	D3D11_MAPPED_SUBRESOURCE subRes = {};
	CDevice::GetInst()->GetContext()->Map(mBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &subRes);
	memcpy(subRes.pData, data, mDesc.ByteWidth);
	CDevice::GetInst()->GetContext()->Unmap(mBuffer.Get(), 0);

	return true;
}
