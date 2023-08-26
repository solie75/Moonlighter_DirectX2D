#include "CShader.h"

CShader::CShader()
	: CResource(eResourceType::Shader)
	, mRSType(eRSType::SolidBack)
	, mDSType(eDSType::Less)
	, mBSType(eBSType::AlphaBlend)
{
	//CreateInputLayout();
	//BindInputLayout();
	mTopology = D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
}

CShader::~CShader()
{
}
bool CShader::CreateShader(eShaderStage shaderStage, const std::wstring& shaderName, const std::string& entrypointName)
{
	std::filesystem::path shaderPath = std::filesystem::current_path().parent_path();
	shaderPath += L"\\Shader\\";

	if (shaderStage == eShaderStage::VS)
	{
		std::filesystem::path vsPath = shaderPath;
		vsPath += shaderName;

		HRESULT hr = D3DCompileFromFile(vsPath.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE,
			entrypointName.c_str(), "vs_5_0", 0, 0
			, mVSBlob.GetAddressOf(), mErrorBlob.GetAddressOf());

		if (mErrorBlob)
		{
			OutputDebugStringA((char*)mErrorBlob->GetBufferPointer());
			mErrorBlob->Release();
		}
		CDevice::GetInst()->GetDevice()->CreateVertexShader(mVSBlob->GetBufferPointer()
			, mVSBlob->GetBufferSize(), nullptr, mVS.GetAddressOf());
	}
	else if (shaderStage == eShaderStage::GS)
	{
		std::filesystem::path psPath = shaderPath;
		psPath += shaderName;

		HRESULT hr = D3DCompileFromFile(psPath.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE,
			entrypointName.c_str(), "gs_5_0", 0, 0
			, mGSBlob.GetAddressOf(), mErrorBlob.GetAddressOf());

		if (mErrorBlob)
		{
			OutputDebugStringA((char*)mErrorBlob->GetBufferPointer());
			mErrorBlob->Release();
		}

		CDevice::GetInst()->GetDevice()->CreateGeometryShader(mGSBlob->GetBufferPointer()
			, mGSBlob->GetBufferSize(), nullptr, mGS.GetAddressOf());
	}
	else if (shaderStage == eShaderStage::PS)
	{
		std::filesystem::path psPath = shaderPath;
		psPath += shaderName;

		HRESULT hr =  D3DCompileFromFile(psPath.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE,
			entrypointName.c_str(), "ps_5_0", 0, 0
			, mPSBlob.GetAddressOf(), mErrorBlob.GetAddressOf());

		if (mErrorBlob)
		{
			OutputDebugStringA((char*)mErrorBlob->GetBufferPointer());
			mErrorBlob->Release();
		}

		CDevice::GetInst()->GetDevice()->CreatePixelShader(mPSBlob->GetBufferPointer()
			, mPSBlob->GetBufferSize(), nullptr, mPS.GetAddressOf());
	}

	return true;
}

//bool CShader::CreateShader()
//{
//	// Shader Path
//	std::filesystem::path shaderPath = std::filesystem::current_path().parent_path();
//	shaderPath += L"\\Shader\\";
//
//	// VS shader Path
//	std::filesystem::path vsPath(shaderPath.c_str());
//	vsPath += L"VS.hlsl";
//
//	// VS Shader Compiling into Blob value
//	D3DCompileFromFile(vsPath.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE
//		, "main", "vs_5_0", 0, 0
//		, mVSBlob.GetAddressOf(), mErrorBlob.GetAddressOf());
//
//	// Shader 컴파일 과정의 오류를 문자열로 보여줌.
//	if (mErrorBlob)
//	{
//		OutputDebugStringA((char*)mErrorBlob->GetBufferPointer());
//		mErrorBlob->Release();
//	}
//
//	// VertexShader 생성
//	CDevice::GetInst()->GetDevice()->CreateVertexShader(mVSBlob->GetBufferPointer()
//		, mVSBlob->GetBufferSize(), nullptr, mVS.GetAddressOf());
//
//	// PS shader Path
//	std::filesystem::path psPath(shaderPath.c_str());
//	psPath += L"PS.hlsl";
//
//	// PS Shader Compiling into Blob value
//	D3DCompileFromFile(psPath.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE
//		, "main", "ps_5_0", 0, 0
//		, mPSBlob.GetAddressOf(), mErrorBlob.GetAddressOf());
//
//	CDevice::GetInst()->GetDevice()->CreatePixelShader(mPSBlob->GetBufferPointer()
//		, mPSBlob->GetBufferSize(), nullptr, mPS.GetAddressOf());
//
//	// Shader 컴파일 과정의 오류를 문자열로 보여줌.
//	if (mErrorBlob)
//	{
//		OutputDebugStringA((char*)mErrorBlob->GetBufferPointer());
//		mErrorBlob->Release();
//	}
//
//	return true;
//}

bool CShader::CreateInputLayout()
{
	D3D11_INPUT_ELEMENT_DESC arrLayout[3] = {};

	arrLayout[0].AlignedByteOffset = 0;
	arrLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	arrLayout[0].InputSlot = 0;
	arrLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	arrLayout[0].SemanticName = "POSITION";
	arrLayout[0].SemanticIndex = 0;

	arrLayout[1].AlignedByteOffset = 12;
	arrLayout[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	arrLayout[1].InputSlot = 0;
	arrLayout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	arrLayout[1].SemanticName = "COLOR";
	arrLayout[1].SemanticIndex = 0;

	arrLayout[2].AlignedByteOffset = 28;
	arrLayout[2].Format = DXGI_FORMAT_R32G32_FLOAT;
	arrLayout[2].InputSlot = 0;
	arrLayout[2].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	arrLayout[2].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	arrLayout[2].SemanticName = "TEXCOORD";
	arrLayout[2].SemanticIndex = 0;

	HRESULT hr = CDevice::GetInst()->GetDevice()->CreateInputLayout(arrLayout, 3
		, mVSBlob->GetBufferPointer(), mVSBlob->GetBufferSize()
		, mInputLayout.GetAddressOf());

	return true;
}

void CShader::BindsShader()
{
	BindInputLayout();
	CDevice::GetInst()->GetContext()->VSSetShader(mVS.Get(), 0, 0);
	CDevice::GetInst()->GetContext()->PSSetShader(mPS.Get(), 0, 0);
	CDevice::GetInst()->GetContext()->GSSetShader(mGS.Get(), 0, 0);
}

void CShader::BindInputLayout()
{
	CDevice::GetInst()->GetContext()->IASetInputLayout(mInputLayout.Get());
	//CDevice::GetInst()->GetContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	CDevice::GetInst()->GetContext()->IASetPrimitiveTopology(mTopology);
}