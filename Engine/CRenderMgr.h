#pragma once
#include "Header.h"
#include "CSingleton.h"
#include "CMaterial.h"
#include "CMesh.h" //#include "CDevice.h" #include "Graphic.h"
#include "CMeshRender.h" //#include "CShader.h" #include "CGameObject.h"
#include "CResourceMgr.h"
#include "CSceneMgr.h"

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

	//CMesh* mMesh;
	//CMaterial* mMaterial;
	//CGameObject* mGameObj;

	ComPtr<ID3D11SamplerState> samplerState[(UINT)eSamplerType::End];

public:
	CRenderMgr();
	~CRenderMgr();

	void Init();
	void Update();
	void Render();

	bool CreateConstantBuffer();
	void BindConstantBuffer(eShaderStage stage, tConstantBuffer tCB);
	void SetUpState();
	void BindSampler(eShaderStage stage, UINT StartSlot, ID3D11SamplerState** ppSamplerState);
};

