#pragma once
#include "Header.h"
#include "Graphic.h"

class CStructedBuffer
{
private:
	ComPtr<ID3D11Buffer> mBuffer;
	D3D11_BUFFER_DESC mDesc;

	ComPtr<ID3D11ShaderResourceView> mSRV;
	eSRVType mType;

	UINT mSize;
	UINT mStride;

public:
	CStructedBuffer();
	~CStructedBuffer();
	
	bool CreateStructedBuffer(UINT size, UINT stride, eSRVType type);
	void SetData(void* data, UINT stride);
	void Bind(eShaderStage stage, UINT slot);

	UINT GetSize() { return mSize; }
	UINT GetStride() { return mStride; }
};

