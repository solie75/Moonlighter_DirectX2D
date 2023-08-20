#include "CTransform.h"
#include "CGameObject.h"
#include "CCollider2D.h"


CTransform::CTransform()
	: CComponent(eComponentType::Transform)
	, mPosition(Vector3::Zero)
	, mRotation(Vector3::Zero)
	, mScale(Vector3::One)
{
	mTransformCB = new CConstantBuffer();
}

CTransform::~CTransform()
{
}

void CTransform::Initialize()
{
}

void CTransform::Update()
{
}

void CTransform::LateUpdate()
{
	mWorld = Matrix::Identity;

	Matrix scale = Matrix::CreateScale(mScale);

	Matrix rotation;
	rotation = Matrix::CreateRotationX(mRotation.x);
	rotation *= Matrix::CreateRotationY(mRotation.y);
	rotation *= Matrix::CreateRotationZ(mRotation.z);

	Matrix position;
	position.Translation(mPosition);

	mWorld = scale * rotation * position;
	CCollider2D* cd = this->GetOwner()->GetComponent<CCollider2D>(eComponentType::Collider2D);
	if (nullptr != cd)
	{
		mColliderPosition = Vector3(mPosition.x + cd->GetOffset().x, mPosition.y + cd->GetOffset().y, 0.0f);
	}

	mUp = Vector3::TransformNormal(Vector3::Up, rotation);
	mFoward = Vector3::TransformNormal(Vector3::Forward, rotation);
	mRight = Vector3::TransformNormal(Vector3::Right, rotation);
}

void CTransform::Render()
{
}

void CTransform::CreateConstantBuffer()
{
	TransformCB trCB = {};
	trCB.mWorld = mWorld;
	trCB.mView = CCamera::GetStaticViewMatrix();
	trCB.mProjection = CCamera::GetStaticProjectionMatrix();

	mTransformCB->InitConstantBuffer(sizeof(TransformCB), eCBType::Transform, &trCB);

}
