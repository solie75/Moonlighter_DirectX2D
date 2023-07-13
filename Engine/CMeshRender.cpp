#include "CMeshRender.h"

CMeshRender::CMeshRender()
	: CComponent(eComponentType::MeshRender)
{
}

CMeshRender::~CMeshRender()
{
}

void CMeshRender::Initialize()
{
}

void CMeshRender::Update()
{
}

void CMeshRender::LateUpdate()
{
}

void CMeshRender::Render()
{
	mMaterial->Clear();
	mMesh->Render();
	mMaterial->Bind();
}
