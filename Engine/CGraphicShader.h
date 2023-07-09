#pragma once
#include "CSingleton.h"
#include "Graphic.h"
#include "CGraphicDevice.h"

class CGraphicShader : public CSingleton<CGraphicShader>
{
private:
	ComPtr<ID3DBlob> mErrorBlob = nullptr;
	ComPtr<ID3D11VertexShader> mVSShader = nullptr;
	ComPtr<ID3D11PixelShader> mPSShader = nullptr;
	ComPtr<ID3DBlob> mVSBlob = nullptr;
	ComPtr<ID3DBlob> mPSBlob = nullptr;

	ComPtr<ID3D11InputLayout> mInputLayout = nullptr;
public:
	CGraphicShader();
	~CGraphicShader();

	void Init();

	bool CreateShader();
	bool CreateInputLayout();

	void BindsShader();
	void BindInputLayout();
};

