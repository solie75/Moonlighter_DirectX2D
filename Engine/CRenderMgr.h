#pragma once
#include "Header.h"
#include "CSingleton.h"

#include "CGraphicDevice.h"


class CRenderMgr : public CSingleton<CRenderMgr>
{
private:
	tVertex vertexes[3] = {};

	ComPtr<ID3D11Buffer> mVertexBuffer;
	ComPtr<ID3D11Buffer> mIndexBuffer;

	D3D11_BUFFER_DESC mVBDesc;
	D3D11_BUFFER_DESC mIBDesc;

public:
	CRenderMgr();
	~CRenderMgr();

	void Init();
	void Update();
	void Render();

	bool CreateBuffer();
	void BindBuffers();
};

