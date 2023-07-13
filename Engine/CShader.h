#pragma once
//#include "CSingleton.h"
#include "Graphic.h"
#include "CDevice.h"
#include "CResource.h"

class CShader : public CResource
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

	bool CreateShader();
	bool CreateInputLayout();

	void BindsShader();
	void BindInputLayout();

	virtual HRESULT ResourceLoad(const std::wstring name, const std::wstring& path) { return S_OK; }
};

