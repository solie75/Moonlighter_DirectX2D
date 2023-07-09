#include "CGraphicShader.h"

CGraphicShader::CGraphicShader()
{
}

CGraphicShader::~CGraphicShader()
{
}

void CGraphicShader::Init()
{
	CreateShader();
	CreateInputLayout();
}

bool CGraphicShader::CreateShader()
{
	// Shader Path
	std::filesystem::path shaderPath = std::filesystem::current_path().parent_path();
	shaderPath += L"\\Shader\\";

	// VS shader Path
	std::filesystem::path vsPath(shaderPath.c_str());
	vsPath += L"VS.hlsl";

	// VS Shader Compiling into Blob value
	D3DCompileFromFile(vsPath.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE
		, "main", "vs_5_0", 0, 0
		, mVSBlob.GetAddressOf(), mErrorBlob.GetAddressOf());

	// Shader 컴파일 과정의 오류를 문자열로 보여줌.
	if (mErrorBlob)
	{
		OutputDebugStringA((char*)mErrorBlob->GetBufferPointer());
		mErrorBlob->Release();
	}

	// VertexShader 생성
	CGraphicDevice::GetInst()->GetDevice()->CreateVertexShader(mVSBlob->GetBufferPointer()
		, mVSBlob->GetBufferSize(), nullptr, mVSShader.GetAddressOf());

	// PS shader Path
	std::filesystem::path psPath(shaderPath.c_str());
	psPath += L"PS.hlsl";

	// PS Shader Compiling into Blob value
	D3DCompileFromFile(psPath.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE
		, "main", "ps_5_0", 0, 0
		, mPSBlob.GetAddressOf(), mErrorBlob.GetAddressOf());

	CGraphicDevice::GetInst()->GetDevice()->CreatePixelShader(mPSBlob->GetBufferPointer()
		, mPSBlob->GetBufferSize(), nullptr, mPSShader.GetAddressOf());

	// Shader 컴파일 과정의 오류를 문자열로 보여줌.
	if (mErrorBlob)
	{
		OutputDebugStringA((char*)mErrorBlob->GetBufferPointer());
		mErrorBlob->Release();
	}

	return true;
}

bool CGraphicShader::CreateInputLayout()
{
	D3D11_INPUT_ELEMENT_DESC arrLayout[2] = {};
	//D3D11_INPUT_ELEMENT_DESC arrLayout[3] = {};

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

	//arrLayout[2].AlignedByteOffset = 28;
	//arrLayout[2].Format = DXGI_FORMAT_R32G32_FLOAT;
	//arrLayout[2].InputSlot = 0;
	//arrLayout[2].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	//arrLayout[2].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	//arrLayout[2].SemanticName = "TEXCOORD";
	//arrLayout[2].SemanticIndex = 0;

	CGraphicDevice::GetInst()->GetDevice()->CreateInputLayout(arrLayout, 2
		, mVSBlob->GetBufferPointer(), mVSBlob->GetBufferSize()
		, mInputLayout.GetAddressOf());

	return true;
}

void CGraphicShader::BindsShader()
{
	CGraphicDevice::GetInst()->GetContext()->VSSetShader(mVSShader.Get(), 0, 0);
	CGraphicDevice::GetInst()->GetContext()->PSSetShader(mPSShader.Get(), 0, 0);
}

void CGraphicShader::BindInputLayout()
{
	CGraphicDevice::GetInst()->GetContext()->IASetInputLayout(mInputLayout.Get());
	CGraphicDevice::GetInst()->GetContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}