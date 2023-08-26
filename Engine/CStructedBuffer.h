#pragma once
#include "Header.h"
#include "Graphic.h"

class CStructedBuffer
{
private:
	ComPtr<ID3D11Buffer> mBuffer;
	D3D11_BUFFER_DESC mDesc;

	ComPtr<ID3D11ShaderResourceView> mSRV;
	ComPtr<ID3D11UnorderedAccessView> mUAV;
	eViewType mType;

	UINT mSize;
	UINT mStride;

	UINT mSRVSlot;
	UINT mUAVSlot;

public:
	CStructedBuffer();
	~CStructedBuffer();
	
	bool CreateStructedBuffer(UINT size, UINT stride, eViewType type, void* data);
	void SetData(void* data, UINT stride);
	void BindSRV(eShaderStage stage, UINT slot);
	void BindUAV(UINT slot);

	void Clear();

	UINT GetSize() { return mSize; }
	UINT GetStride() { return mStride; }
};

