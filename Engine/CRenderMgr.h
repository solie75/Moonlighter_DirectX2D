#pragma once
#include "Header.h"
#include "CSingleton.h"
//#include "CDevice.h"
//#include "Graphic.h"
#include "CMesh.h"


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
	tConstantBuffer mCB;

	ID3D11DeviceContext* mGraphicContext;

	CMesh* mMesh;

public:
	CRenderMgr();
	~CRenderMgr();

	void Init();
	void Update();
	void Render();

	bool CreateConstantBuffer();
	void BindConstantBuffer(eShaderStage stage, tConstantBuffer tCB);
};

