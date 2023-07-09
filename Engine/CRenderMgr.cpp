#include "CRenderMgr.h"

CRenderMgr::CRenderMgr()
	: mVBDesc{}
	, mIBDesc{}
{
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
	CGraphicDevice::GetInst()->GetContext()->DrawIndexed(6, 0, 0);
	HRESULT hr = CGraphicDevice::GetInst()->GetSwapChain()->Present(0, 0);
}

bool CRenderMgr::CreateBuffer()
{
	// Triangle Vertex array
	vertexes[0].pos = Vector3(0.0f, 0.5f, 0.0f);
	vertexes[0].color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);
	vertexes[1].pos = Vector3(1.0f, 1.0f, 0.0f);
	vertexes[1].color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);
	vertexes[2].pos = Vector3(-1.0f, 1.0f, 0.0f);
	vertexes[2].color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);

	// Set VertexBuffer Description
	mVBDesc.ByteWidth = sizeof(tVertex) * 3;
	mVBDesc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;
	mVBDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER;
	mVBDesc.CPUAccessFlags = 0;

	// Set SubResourceData Desc
	D3D11_SUBRESOURCE_DATA subData = {};
	subData.pSysMem = vertexes; // 이거 맞나...?

	// Create VertexBuffer
	CGraphicDevice::GetInst()->GetDevice()->CreateBuffer(&mVBDesc, &subData, mVertexBuffer.GetAddressOf());

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
	CGraphicDevice::GetInst()->GetDevice()->CreateBuffer(&mIBDesc, &subData, mIndexBuffer.GetAddressOf());
	
	return true;
}

void CRenderMgr::BindBuffers()
{
	UINT stride = sizeof(tVertex);
	UINT offset = 0;

	CGraphicDevice::GetInst()->GetContext()->IASetVertexBuffers(0, 1, mVertexBuffer.GetAddressOf(), &stride, &offset);
	CGraphicDevice::GetInst()->GetContext()->IASetIndexBuffer(mVertexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
}
