#pragma once
#include "CSingleton.h"
#include "Graphic.h"
#include "CDevice.h"

class CShader : public CSingleton<CShader>
{
private:
	ComPtr<ID3DBlob> mErrorBlob = nullptr;

	ComPtr<ID3DBlob> mVSBlob;
	ComPtr<ID3DBlob> mHSBlob;
	ComPtr<ID3DBlob> mDSBlob;
	ComPtr<ID3DBlob> mGSBlob;
	ComPtr<ID3DBlob> mPSBlob;

	ComPtr<ID3D11VertexShader> mVS;
	ComPtr<ID3D11HullShader> mHS;
	ComPtr<ID3D11DomainShader> mDS;
	ComPtr<ID3D11GeometryShader> mGS;
	ComPtr<ID3D11PixelShader> mPS;

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

