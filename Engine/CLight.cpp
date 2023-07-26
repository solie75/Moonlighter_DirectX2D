#include "CLight.h"
#include "CTransform.h"

CLight::CLight()
	: CComponent(eComponentType::Light)
{
}

CLight::~CLight()
{
}

void CLight::Initialize()
{
}

void CLight::Update()
{
}

void CLight::LateUpdate()
{
	CRenderMgr::GetInst()->AddLight(this);

	CTransform* tr = GetOwner()->GetComponent<CTransform>(eComponentType::Transform);
	Vector3 pos = tr->GetPosition();
	mAttribute.position = Vector4(pos.x, pos.y, pos.z, 1.0f);
	mAttribute.direction = Vector4(tr->Foward().x, tr->Foward().y, tr->Foward().z, 1.0f);
}

void CLight::Render()
{
}
