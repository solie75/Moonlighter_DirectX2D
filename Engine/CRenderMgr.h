#pragma once
#include "Header.h"
#include "CSingleton.h"
#include "CMaterial.h"
#include "CMesh.h" //#include "CDevice.h" #include "Graphic.h"
#include "CMeshRender.h" //#include "CShader.h" #include "CGameObject.h"
#include "CResourceMgr.h"
#include "CSceneMgr.h"
#include "CCameraMgr.h"
#include "CConstantBuffer.h"

class CRenderMgr : public CSingleton<CRenderMgr>
{
private:

	CConstantBuffer* mCB;

	ID3D11DeviceContext* mGraphicContext;

	ComPtr<ID3D11SamplerState> samplerState[(UINT)eSamplerType::End];
	ComPtr<ID3D11RasterizerState> rasterizerStates[(UINT)eRSType::End] = {};
	ComPtr<ID3D11DepthStencilState> depthStencilStates[(UINT)eDSType::End] = {};
	ComPtr<ID3D11BlendState> blendStates[(UINT)eBSType::End] = {};

public:
	CRenderMgr();
	~CRenderMgr();

	void Init();
	void Update();
	void LateUpdate();
	void Render();

	//bool CreateConstantBuffer();
	void BindConstantBuffer(eShaderStage stage, CConstantBuffer* tCB);
	void SetUpState();
	void BindSampler(eShaderStage stage, UINT StartSlot, ID3D11SamplerState** ppSamplerState);

	ComPtr<ID3D11RasterizerState> GetRasterizerState(eRSType type)
	{
		return rasterizerStates[(UINT)type];
	}
	ComPtr<ID3D11DepthStencilState> GetDepthStencilState(eDSType type)
	{
		return depthStencilStates[(UINT)type];
	}
	ComPtr<ID3D11BlendState> GetBlendState(eBSType type)
	{
		return blendStates[(UINT)type];
	}
};

