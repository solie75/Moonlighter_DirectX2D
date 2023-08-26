#include "CMesh.h"

CMesh::CMesh()
	: CResource(eResourceType::Mesh)
	, mVBDesc{}
	, mIBDesc{}
{
	//CreateBuffer();
	mIndexCount = 0;
}

CMesh::~CMesh()
{
}

void CMesh::Render()
{
	CDevice::GetInst()->GetContext()->DrawIndexed(6, 0, 0);
}

void CMesh::CreateSquareBuffer()
{
	// Rectangle Vertex array
	vertexes[0].pos = Vector3(-0.5f, 0.5f, 0.0f);
	vertexes[0].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
	vertexes[0].uv = Vector2(0.0f, 0.0f);

	vertexes[1].pos = Vector3(0.5f, 0.5f, 0.0f);
	vertexes[1].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
	vertexes[1].uv = Vector2(1.0f, 0.0f);

	vertexes[2].pos = Vector3(0.5f, -0.5f, 0.0f);
	vertexes[2].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
	vertexes[2].uv = Vector2(1.0f, 1.0f);

	vertexes[3].pos = Vector3(-0.5f, -0.5f, 0.0f);
	vertexes[3].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
	vertexes[3].uv = Vector2(0.0f, 1.0f);

	// Set VertexBuffer Description
	mVBDesc.ByteWidth = sizeof(tVertex) * 4;
	mVBDesc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;
	mVBDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER;
	mVBDesc.CPUAccessFlags = 0;

	// Set SubResourceData Desc
	D3D11_SUBRESOURCE_DATA subData = {};
	subData.pSysMem = vertexes;

	// Create VertexBuffer
	CDevice::GetInst()->GetDevice()->CreateBuffer(&mVBDesc, &subData, mVB.GetAddressOf());

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
	CDevice::GetInst()->GetDevice()->CreateBuffer(&mIBDesc, &subData, mIB.GetAddressOf());
}

void CMesh::CreatePointBuffer()
{
	vertexes[0].pos = Vector3(0.0f, 0.0f, 0.0f);
	vertexes[0].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);

	mVBDesc.ByteWidth = sizeof(tVertex) * 1;
	mVBDesc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;
	mVBDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER;
	mVBDesc.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA subData = {};
	subData.pSysMem = vertexes;

	CDevice::GetInst()->GetDevice()->CreateBuffer(&mVBDesc, &subData, mVB.GetAddressOf());

	std::vector<UINT> indexes = {};
	indexes.push_back(0);

	mIBDesc.ByteWidth = sizeof(UINT) * 1;
	mIBDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_INDEX_BUFFER;
	mIBDesc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;
	mIBDesc.CPUAccessFlags = 0;

	subData.pSysMem = indexes.data();
	
	CDevice::GetInst()->GetDevice()->CreateBuffer(&mIBDesc, &subData, mIB.GetAddressOf());

}

void CMesh::BindBuffer()
{
	// Bind Vertex & Index Buffer
	UINT stride = sizeof(tVertex);
	UINT offset = 0;

	CDevice::GetInst()->GetContext()->IASetVertexBuffers(0, 1, mVB.GetAddressOf(), &stride, &offset);
	CDevice::GetInst()->GetContext()->IASetIndexBuffer(mIB.Get(), DXGI_FORMAT_R32_UINT, 0);
}

void CMesh::RenderInstanced(UINT startIndexLocation)
{
	// 6 => mIndexCount
	CDevice::GetInst()->DrawIndexedInstanced(6, startIndexLocation, 0, 0, 0);
}

