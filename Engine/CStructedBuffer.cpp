#include "CStructedBuffer.h"
#include "CDevice.h"

CStructedBuffer::CStructedBuffer()
    : mBuffer(nullptr)
    , mDesc{}
    , mSRV(nullptr)
    , mType(eSRVType::None)
    , mSize(0)
    , mStride(0)
{
}

CStructedBuffer::~CStructedBuffer()
{
}

bool CStructedBuffer::CreateStructedBuffer(UINT size, UINT stride, eSRVType type)
{
    mSize = size;
    mStride = stride;

    mDesc.ByteWidth = mSize * stride;
    mDesc.StructureByteStride = mSize;

    mDesc.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;
    mDesc.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;
    mDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_SHADER_RESOURCE;
    mDesc.MiscFlags = D3D11_RESOURCE_MISC_FLAG::D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;

    HRESULT hr = CDevice::GetInst()->GetDevice()->CreateBuffer(&mDesc, nullptr, mBuffer.GetAddressOf());


    D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
    srvDesc.BufferEx.NumElements = mStride;
    srvDesc.ViewDimension = D3D_SRV_DIMENSION::D3D_SRV_DIMENSION_BUFFEREX;

    hr = CDevice::GetInst()->GetDevice()->CreateShaderResourceView(mBuffer.Get(), &srvDesc, mSRV.GetAddressOf());

    return true;
}

void CStructedBuffer::SetData(void* data, UINT stride)
{
    if (mStride < stride)
    {
        CreateStructedBuffer(mSize, stride, eSRVType::None);
    }
    else
    {
        D3D11_MAPPED_SUBRESOURCE subRes = {};
        CDevice::GetInst()->GetContext()->Map(mBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &subRes);
        memcpy(subRes.pData, data, mSize* stride);
        CDevice::GetInst()->GetContext()->Unmap(mBuffer.Get(), 0);
    }
}

void CStructedBuffer::Bind(eShaderStage stage, UINT slot)
{
    CDevice::GetInst()->BindShaderResource(stage, slot, mSRV.GetAddressOf());
}
