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
#include "CLight.h"
#include "CStructedBuffer.h"


class CRenderMgr : public CSingleton<CRenderMgr>
{
private:

	CConstantBuffer* mCB[(UINT)eCBType::End] = {};

	ID3D11DeviceContext* mGraphicContext;

	ComPtr<ID3D11SamplerState> samplerState[(UINT)eSamplerType::End];
	ComPtr<ID3D11RasterizerState> rasterizerStates[(UINT)eRSType::End] = {};
	ComPtr<ID3D11DepthStencilState> depthStencilStates[(UINT)eDSType::End] = {};
	ComPtr<ID3D11BlendState> blendStates[(UINT)eBSType::End] = {};

	std::vector<CLight*> lights;
	CStructedBuffer* lightsBuffer;
	static std::vector<DebugMesh> debugMeshs;

public:
	CRenderMgr();
	~CRenderMgr();

	void Init();
	void Update();
	void LateUpdate();
	void Render();
	void Release();

	void AddLight(CLight* light) { lights.push_back(light); }

	//bool CreateConstantBuffer();
	void BindConstantBuffer(eShaderStage stage, CConstantBuffer* tCB);
	void SetUpState();
	void BindSampler(eShaderStage stage, UINT StartSlot, ID3D11SamplerState** ppSamplerState);
	void LoadTexture(const std::wstring& textureName, const std::wstring& path);
	void LoadMaterial(std::shared_ptr<CShader> shader, const std::wstring& textureName, eRenderingMode renderMode);
	void CreateAtlas(const std::wstring& spriteName, int spriteNum);
	void AddDebugMesh(DebugMesh mesh)
	{
		debugMeshs.push_back(mesh);
	}
	vector<DebugMesh> GetDebugMesh() { return debugMeshs; }
	void ClearDebugMesh() { debugMeshs.clear(); }


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

	/*void AddCamera(CCamera* cam, const std::wstring& name)
	{ 
		cameras.push_back(cam);
		cam->SetName(name);
	}*/

	void BindLights();
};

std::vector<DebugMesh> CRenderMgr::debugMeshs = {};