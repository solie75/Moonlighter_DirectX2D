#pragma once
#include "Header.h"
#include "CSingleton.h"
#include "CDevice.h"
#include "Graphic.h"


class CRenderMgr : public CSingleton<CRenderMgr>
{
public:
	struct tConstantBuffer
	{
		ComPtr<ID3D11Buffer> mBuffer;
		D3D11_BUFFER_DESC mDesc;
		eCBType eType;
	};

private:
	tVertex vertexes[4] = {};

	ComPtr<ID3D11Buffer> mVertexBuffer;
	ComPtr<ID3D11Buffer> mIndexBuffer;

	D3D11_BUFFER_DESC mVBDesc;
	D3D11_BUFFER_DESC mIBDesc;

	tConstantBuffer mCB;

	ID3D11DeviceContext* mGraphicContext;

public:
	CRenderMgr();
	~CRenderMgr();

	void Init();
	void Update();
	void Render();

	bool CreateBuffer();
	void BindBuffers();
	void BindConstantBuffer(eShaderStage stage, tConstantBuffer tCB);
};

