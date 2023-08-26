#include "CStructedBuffer.h"
#include "CDevice.h"

CStructedBuffer::CStructedBuffer()
    : mBuffer(nullptr)
    , mDesc{}
    , mSRV(nullptr)
    , mType(eViewType::None)
    , mSize(0)
    , mStride(0)
    , mSRVSlot(0)
    , mUAVSlot(0)
{
}

CStructedBuffer::~CStructedBuffer()
{
}

bool CStructedBuffer::CreateStructedBuffer(UINT size, UINT stride, eViewType type, void* data)
{
    mType = type;

    mSize = size;
    mStride = stride;

    mDesc.ByteWidth = mSize * mStride;
    mDesc.StructureByteStride = mSize;

    mDesc.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;
    mDesc.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;
    mDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_SHADER_RESOURCE; // Texture Register Binding
    mDesc.MiscFlags = D3D11_RESOURCE_MISC_FLAG::D3D11_RESOURCE_MISC_BUFFER_STRUCTURED; // 구조화 버퍼 추가 플래그 설정

    if (mType == eViewType::UAV)
    {
        mDesc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;
        mDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_SHADER_RESOURCE
            | D3D11_BIND_FLAG::D3D11_BIND_UNORDERED_ACCESS; // Texture Register Binding
        mDesc.CPUAccessFlags = 0;
    }

    if (data)
    {
        D3D11_SUBRESOURCE_DATA tSub = {};
        tSub.pSysMem = data;

        if (FAILED(CDevice::GetInst()->GetDevice()->CreateBuffer(&mDesc, &tSub, mBuffer.GetAddressOf())))
        {
            return false;
        }
    }
    else
    {
        if (FAILED(CDevice::GetInst()->GetDevice()->CreateBuffer(&mDesc, nullptr, mBuffer.GetAddressOf())))
        {
            return false;
        }
    }

    //HRESULT hr = CDevice::GetInst()->GetDevice()->CreateBuffer(&mDesc, nullptr, mBuffer.GetAddressOf());
    D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
    srvDesc.BufferEx.NumElements = mStride;
    srvDesc.ViewDimension = D3D_SRV_DIMENSION::D3D_SRV_DIMENSION_BUFFEREX;

    //HRESULT hr = CDevice::GetInst()->GetDevice()->CreateShaderResourceView(mBuffer.Get(), &srvDesc, mSRV.GetAddressOf());
    if (FAILED(CDevice::GetInst()->GetDevice()->CreateShaderResourceView(mBuffer.Get(), &srvDesc, mSRV.GetAddressOf())))
    {
        return false;
    }

    if (mType == eViewType::UAV)
    {
        D3D11_UNORDERED_ACCESS_VIEW_DESC uavDesc = {};
        uavDesc.Buffer.NumElements = mStride;
        uavDesc.ViewDimension = D3D11_UAV_DIMENSION_BUFFER;

        if (!(CDevice::GetInst()->CreateUnorderedAccessView(mBuffer.Get(), &uavDesc, mUAV.GetAddressOf())))
        {
            return false;
        }
    }

    return true;
}

void CStructedBuffer::SetData(void* data, UINT stride)
{
    if (mStride < stride)
    {
        CreateStructedBuffer(mSize, stride, eViewType::None, nullptr);
    }
    else
    {
        D3D11_MAPPED_SUBRESOURCE subRes = {};
        CDevice::GetInst()->GetContext()->Map(mBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &subRes);
        memcpy(subRes.pData, data, mSize* stride);
        CDevice::GetInst()->GetContext()->Unmap(mBuffer.Get(), 0);
    }
}

void CStructedBuffer::BindSRV(eShaderStage stage, UINT slot)
{
    mSRVSlot = slot;
    CDevice::GetInst()->BindShaderResource(stage, slot, mSRV.GetAddressOf());
}

void CStructedBuffer::BindUAV(UINT slot)
{
    mUAVSlot = slot;
    UINT i = - 1;
    CDevice::GetInst()->BindUnorderedAccess(slot, mUAV.GetAddressOf(), &i);
}

void CStructedBuffer::Clear()
{
    ID3D11ShaderResourceView* srv = nullptr;
    CDevice::GetInst()->BindShaderResource(eShaderStage::VS, mSRVSlot, &srv);
    CDevice::GetInst()->BindShaderResource(eShaderStage::HS, mSRVSlot, &srv);
    CDevice::GetInst()->BindShaderResource(eShaderStage::DS, mSRVSlot, &srv);
    CDevice::GetInst()->BindShaderResource(eShaderStage::GS, mSRVSlot, &srv);
    CDevice::GetInst()->BindShaderResource(eShaderStage::PS, mSRVSlot, &srv);
    CDevice::GetInst()->BindShaderResource(eShaderStage::CS, mSRVSlot, &srv);

    ID3D11UnorderedAccessView* uav = nullptr;
    UINT i = -1;
    CDevice::GetInst()->BindUnorderedAccess(mUAVSlot, &uav, &i);
}

//void CStructedBuffer::BindSRV(eShaderStage stage, UINT slot)
//{
//    CDevice::GetInst()->BindShaderResource(stage, slot, mSRV.GetAddressOf());
//}
