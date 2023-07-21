#pragma once
#include "CComponent.h"
#include "CTransform.h"
#include "CDevice.h"
#include "CSceneMgr.h"
#include "CMeshRender.h"
#include "CRenderMgr.h"

class CGameObject;

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
	static Matrix staticView;
	static Matrix staticProjection;

	Matrix mView;
	Matrix mProjection;

	eProjectionType mType;
	float mAspectRatio;
	float mNear;
	float mFar;
	float mSize;

	std::bitset<(UINT)eLayerType::End> mLayerMask;
	std::vector<CGameObject*> mOpaqueGameObjects;
	std::vector<CGameObject*> mCutOutGameObjects;
	std::vector<CGameObject*> mTransparentGameObjects;

public:
	CCamera();
	~CCamera();

	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;

	bool CreateViewMatrix();
	bool CreateProjectionMatrix(eProjectionType type);

	static Matrix GetViewMatrix() { return staticView; }
	static Matrix GetProjectionMatrix() { return staticProjection; }

	void AlphaSortGameObjects();
	void RenderOpaque();
	void RenderCutOut();
	void RenderTransparent();
	void ZSortTransparencyGameObjects();
	void EnableDepthStencilState();
	void DisableDepthStencilState();

	void TurnLayerMask(eLayerType type, bool enable = true);
	void EnableLayerMasks() { mLayerMask.set(); }
	void DisableLayerMasks() { mLayerMask.reset(); }

	float GetSize() { return mSize; }
};

Matrix CCamera::staticView =  Matrix::Identity;
Matrix CCamera::staticProjection = Matrix::Identity;