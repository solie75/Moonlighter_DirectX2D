#include "CGridScript.h"
#include "CConstantBuffer.h"
#include "Graphic.h"
#include "CGameObject.h"

CGridScript::CGridScript()
{
}

CGridScript::~CGridScript()
{
}

void CGridScript::Initialize()
{
	mGridCB = new CConstantBuffer();
}

void CGridScript::Update()
{
	GridCB gridCB = {};
	gridCB.CameraPosition = Vector4(0.f, 0.f, 0.f, -10.f);
	gridCB.CameraScale = Vector2(0.5f, 0.5f);
	gridCB.Resolution = Vector2((float)(CDevice::GetInst()->GetDeviceHeight()), (float)(CDevice::GetInst()->GetDeviceWidth()));

	mGridCB->InitConstantBuffer(sizeof(GridCB), eCBType::Grid, &gridCB);

	CRenderMgr::GetInst()->BindConstantBuffer(eShaderStage::VS, mGridCB);
	CRenderMgr::GetInst()->BindConstantBuffer(eShaderStage::PS, mGridCB);
}

void CGridScript::LateUpdate()
{
}

void CGridScript::Render()
{
}

void CGridScript::CreateConstantBuffer()
{

}

