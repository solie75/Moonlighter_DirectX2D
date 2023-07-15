#pragma once
#include "CComponent.h"
#include "CTransform.h"
#include "CDevice.h"

class CCamera :
    public CComponent
{
public:
	enum class eProjectionType
	{
		Perpective,
		OrthoGraphic,
		None,
	};

private:
	static Matrix mView;
	static Matrix mProjection;

	eProjectionType mType;
	float mAspectRatio;
	float mNear;
	float mFar;
	float mSize;

public:
	CCamera();
	~CCamera();

	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;

	bool CreateViewMatrix();
	bool CreateProjectionMatrix(eProjectionType type);

	static Matrix GetViewMatrix() { return mView; }
	static Matrix GetmProjectionMatrix() { return mProjection; }
};

Matrix CCamera::mView =  Matrix::Identity;
Matrix CCamera::mProjection = Matrix::Identity;