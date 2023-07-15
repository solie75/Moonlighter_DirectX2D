#pragma once
#include "Header.h"
#include "Graphic.h"
#include "CDevice.h"

class CConstantBuffer
{
private:
	ComPtr<ID3D11Buffer> mBuffer;
	D3D11_BUFFER_DESC mDesc;
	eCBType mType;

public:
	CConstantBuffer();
	~CConstantBuffer();

	ComPtr<ID3D11Buffer> GetConstantBuffer() { return mBuffer; }
	D3D11_BUFFER_DESC* GetConstantDesc() { return &mDesc; }
	eCBType GetConstantType() { return mType; }

	void SetConstantBuffer(ComPtr<ID3D11Buffer> buffer) { mBuffer = buffer; }
	void SetConstantDesc(D3D11_BUFFER_DESC desc) { mDesc = desc; }
	void SetConstantType(eCBType type) { mType = type; }

	bool InitConstantBuffer(size_t size, eCBType type, void* data);
};

