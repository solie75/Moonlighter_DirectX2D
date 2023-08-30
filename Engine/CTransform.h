#pragma once
#include "CComponent.h"
#include "Graphic.h"
#include "CCamera.h"
#include "CConstantBuffer.h"

class CGameObject;

class CTransform :
    public CComponent
{
private:
	Vector3 mPosition;
	Vector3 mColliderPosition;
	Vector3 mRotation;
	Vector3 mScale;

	Vector3 mUp;
	Vector3 mFoward;
	Vector3 mRight;

	Matrix mWorld;
	Matrix mCollisionWorldMatrix;

	CConstantBuffer* mTransformCB;

public:
	CTransform();
	~CTransform();

	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;

	void CreateConstantBuffer();

	void SetPosition(Vector3 position) { mPosition = position; }
	void SetRotation(Vector3 rotation) { mRotation = rotation; }
	void SetScale(Vector3 scale) { mScale = scale; }

	void SetPosition(float x, float y, float z) { mPosition = Vector3(x, y, z); }
	void SetRotation(float x, float y, float z) { mRotation = Vector3(x, y, z); }
	void SetScale(float x, float y, float z) { mScale = Vector3(x, y, z); }

	Vector3 GetPosition() {
		return mPosition;
	}
	Vector3 GetColliderPosition() { return mColliderPosition; }
	Vector3 GetRotation() { return mRotation; }
	Vector3 GetScale() { return mScale; }

	Vector3 Foward() { return mFoward; }
	Vector3 Right() { return mRight; }
	Vector3 Up() { return mUp; }

	CConstantBuffer* GetTransformCB() { return mTransformCB; }

	Matrix& GetWorldMatrix() { return mWorld; }
	Matrix& GetCollisionWorldMatrix() {	return mCollisionWorldMatrix;}
};

