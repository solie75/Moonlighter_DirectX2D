#pragma once
#include "Header.h"

class CGpuBuffer
{
private:
	ComPtr<ID3D11Buffer> buffer;
	D3D11_BUFFER_DESC desc;

public:
	CGpuBuffer();
	virtual ~CGpuBuffer() = default;

	ComPtr<ID3D11Buffer> GetGpuBuffer() { return buffer; }
	D3D11_BUFFER_DESC* GetGpuBufferDesc() { return &desc; }

	void SetGpuBuffer(ComPtr<ID3D11Buffer> b) { buffer = b; }
	void SetGpuBufferDesc(D3D11_BUFFER_DESC d) { desc = d; }
};

