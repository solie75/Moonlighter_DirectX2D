#pragma once
#include "CSingleton.h"
#include "Graphic.h"
#include "CDevice.h"

class CShader : public CSingleton<CShader>
{
private:
	ComPtr<ID3DBlob> mErrorBlob = nullptr;
	ComPtr<ID3D11VertexShader> mVSShader = nullptr;
	ComPtr<ID3D11PixelShader> mPSShader = nullptr;
	ComPtr<ID3DBlob> mVSBlob = nullptr;
	ComPtr<ID3DBlob> mPSBlob = nullptr;

	ComPtr<ID3D11InputLayout> mInputLayout = nullptr;
public:
	CShader();
	~CShader();

	void Init();

	bool CreateShader();
	bool CreateInputLayout();

	void BindsShader();
	void BindInputLayout();
};

