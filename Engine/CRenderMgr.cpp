#include "CRenderMgr.h"

CRenderMgr::CRenderMgr()
	: mVBDesc{}
	, mIBDesc{}
	, mCB{}
{
	mGraphicContext = CDevice::GetInst()->GetContext();
}

CRenderMgr::~CRenderMgr()
{
}

void CRenderMgr::Init()
{
	CreateBuffer();
}

void CRenderMgr::Update()
{
}

void CRenderMgr::Render()
{
	mGraphicContext->DrawIndexed(6, 0, 0);
	//CDevice::GetInst()->GetContext()->Draw(4, 0);
	HRESULT hr = CDevice::GetInst()->GetSwapChain()->Present(0, 0);
}

bool CRenderMgr::CreateBuffer()
{
	// Triangle Vertex array
	/*vertexes[0].pos = Vector3(0.0f, 0.5f, 0.0f);
	vertexes[0].color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);
	vertexes[1].pos = Vector3(0.5f, -0.5f, 0.0f);
	vertexes[1].color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);
	vertexes[2].pos = Vector3(-0.5f, -0.5f, 0.0f);
	vertexes[2].color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);*/

	// Rectangle Vertex array
	vertexes[0].pos = Vector3(-0.5f, 0.5f, 0.0f);
	vertexes[0].color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);
	vertexes[1].pos = Vector3(0.5f, 0.5f, 0.0f);
	vertexes[1].color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);
	vertexes[2].pos = Vector3(0.5f, -0.5f, 0.0f);
	vertexes[2].color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);
	vertexes[3].pos = Vector3(-0.5f, -0.5f, 0.0f);
	vertexes[3].color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);

	// Set VertexBuffer Description
	mVBDesc.ByteWidth = sizeof(tVertex) * 4;
	mVBDesc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;
	mVBDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER;
	mVBDesc.CPUAccessFlags = 0;

	// Set SubResourceData Desc
	D3D11_SUBRESOURCE_DATA subData = {};
	subData.pSysMem = vertexes;

	// Create VertexBuffer
	CDevice::GetInst()->GetDevice()->CreateBuffer(&mVBDesc, &subData, mVertexBuffer.GetAddressOf());

	// Init Index array
	std::vector<UINT> indexes = {};
	indexes.push_back(0);
	indexes.push_back(1);
	indexes.push_back(2);

	indexes.push_back(0);
	indexes.push_back(2);
	indexes.push_back(3);

	// Set IndexBuffer Description
	mIBDesc.ByteWidth = sizeof(UINT) * 6;
	mIBDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_INDEX_BUFFER;
	mIBDesc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;
	mIBDesc.CPUAccessFlags = 0;

	// Set SubResourceData desc
	subData.pSysMem = indexes.data();

	// Create IndexBuffer
	CDevice::GetInst()->GetDevice()->CreateBuffer(&mIBDesc, &subData, mIndexBuffer.GetAddressOf());
	

	// Set Constant Buffer Description
	mCB.mDesc.ByteWidth = sizeof(Vector4);
	mCB.mDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_CONSTANT_BUFFER;
	mCB.mDesc.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;
	mCB.mDesc.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
	mCB.eType = eCBType::Transform;

	// Create Constant Buffer
	CDevice::GetInst()->GetDevice()->CreateBuffer(&(mCB.mDesc), nullptr, mCB.mBuffer.GetAddressOf());
	
	// Set Constant Buffer
	Vector4 pos(0.3f, 0.0f, 0.0f, 1.0f);

	D3D11_MAPPED_SUBRESOURCE subRes = {};
	mGraphicContext->Map(mCB.mBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &subRes);
	memcpy(subRes.pData, &pos, mCB.mDesc.ByteWidth);
	mGraphicContext->Unmap(mCB.mBuffer.Get(), 0);

	return true;
}

void CRenderMgr::BindBuffers()
{

	// Bind Vertex & Index Buffer
	UINT stride = sizeof(tVertex);
	UINT offset = 0;

	mGraphicContext->IASetVertexBuffers(0, 1, mVertexBuffer.GetAddressOf(), &stride, &offset);
	mGraphicContext->IASetIndexBuffer(mIndexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
	
	// Bind Constant Buffer	
	BindConstantBuffer(eShaderStage::VS, mCB);
}

void CRenderMgr::BindConstantBuffer(eShaderStage stage, tConstantBuffer tCB)
{
	switch (stage)
	{
	case eShaderStage::VS:
		mGraphicContext->VSSetConstantBuffers((UINT)tCB.eType, 1, (tCB.mBuffer).GetAddressOf());
		break;
	case eShaderStage::HS:
		mGraphicContext->HSSetConstantBuffers((UINT)tCB.eType, 1, (tCB.mBuffer).GetAddressOf());
		break;
	case eShaderStage::DS:
		mGraphicContext->DSSetConstantBuffers((UINT)tCB.eType, 1, (tCB.mBuffer).GetAddressOf());
		break;
	case eShaderStage::GS:
		mGraphicContext->GSSetConstantBuffers((UINT)tCB.eType, 1, (tCB.mBuffer).GetAddressOf());
		break;
	case eShaderStage::PS:
		mGraphicContext->PSSetConstantBuffers((UINT)tCB.eType, 1, (tCB.mBuffer).GetAddressOf());
		break;
	case eShaderStage::CS:
		mGraphicContext->CSSetConstantBuffers((UINT)tCB.eType, 1, (tCB.mBuffer).GetAddressOf());
		break;
	case eShaderStage::End:
		break;
	default:
		break;
	}
}


