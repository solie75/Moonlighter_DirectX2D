#include "CCamera.h"
#include "CGameObject.h"

CCamera::CCamera()
	: CComponent(eComponentType::Camera)
	, mType(eProjectionType::OrthoGraphic)
	, mAspectRatio(1.0f)
	, mNear(1.0f)
	, mFar(1000.0f)
	, mSize(5.0f)
	, mLayerMask{}
	, mOpaqueGameObjects{}
	, mCutOutGameObjects{}
	, mTransparentGameObjects{}
	, mView(Matrix::Identity)
	, mProjection(Matrix::Identity)
{
	EnableLayerMasks();
}

CCamera::~CCamera()
{
}

void CCamera::Initialize()
{
	
}

void CCamera::Update()
{
	CRenderMgr::GetInst()->AddCamera(this, this->GetOwner()->GetName());
}

void CCamera::LateUpdate()
{
    CreateViewMatrix();
    CreateProjectionMatrix(mType);
	SortGameObjects();
}

void CCamera::Render()
{
	staticView = mView;
	staticProjection = mProjection;

	RenderOpaque();
	RenderCutOut();
	RenderTransparent();
}

bool CCamera::CreateViewMatrix()
{
	CTransform* tr = GetOwner()->GetComponent<CTransform>(eComponentType::Transform);
	Vector3 pos = tr->GetPosition();

	// View Translate Matrix
	mView = Matrix::Identity;
	mView *= Matrix::CreateTranslation(-pos);

	// View Rotation Matrix
	Vector3 up = tr->Up();
	Vector3 right = tr->Right();
	Vector3 foward = tr->Foward();

	Matrix viewRotate;
	viewRotate._11 = right.x;	viewRotate._12 = up.x;	viewRotate._13 = foward.x;
	viewRotate._21 = right.y;	viewRotate._22 = up.y;	viewRotate._23 = foward.y;
	viewRotate._31 = right.z;	viewRotate._32 = up.z;	viewRotate._33 = foward.z;
	mView *= viewRotate;

	return true;
}

bool CCamera::CreateProjectionMatrix(eProjectionType type)
{
	float width = (float)(CDevice::GetInst()->GetDeviceWidth());
	float height = (float)(CDevice::GetInst()->GetDeviceHeight());
	mAspectRatio = width / height;

	if (type == eProjectionType::OrthoGraphic)
	{
		float OrthorGraphicRatio = mSize / 1000.0f; 
		width *= OrthorGraphicRatio;
		height *= OrthorGraphicRatio;
		/*DirectX�� CreateOrthographicLH �Լ��� ������ ���ο� ���� ���� ������ ȭ�� ������ ũ�⸦ ��Ÿ���ϴ�.
		�� ���� ���� �������� ũ��ʹ� ������ ������, ȭ�鿡 ǥ���� 3D ��ü�� ũ�� �� ������ �����մϴ�.
		CreateOrthographicLH �Լ��� ������ ���ο� ���� ���� ���� ������ ũ��ʹ� ���������� �����Ǿ�� �մϴ�*/
		mProjection = Matrix::CreateOrthographicLH(width, height, mNear, mFar);
	}
	else
	{
		mProjection = Matrix::CreatePerspectiveFieldOfViewLH(XM_2PI / 6.0f, mAspectRatio, mNear, mFar);
	}

	return true;
}

void CCamera::SortGameObjects()
{
	mOpaqueGameObjects.clear();
	mCutOutGameObjects.clear();
	mTransparentGameObjects.clear();

	CScene* scene = CSceneMgr::GetInst()->GetActiveScene();
	for (size_t i = 0; i < (UINT)eLayerType::End; i++)
	{
		if (mLayerMask[i] == true)
		{
			// Mask �� true �� Layer �� ��� ���� ������Ʈ���� �����´�.
			CLayer& layer = scene->GetLayer((eLayerType)i);
			const std::vector<CGameObject*> gameObjs = layer.GetGameObjects();

			for (CGameObject* obj : gameObjs)
			{
				CMeshRender* mr = obj->GetComponent<CMeshRender>(eComponentType::MeshRender);
				if (mr == nullptr)
				{
					continue;
				}
				
				std::shared_ptr<CMaterial> mt = mr->GetMaterial();
				eRenderingMode renderMode = mt->GetRenderingMode();

				switch (renderMode)
				{
				case eRenderingMode::Opaque :
					mOpaqueGameObjects.push_back(obj);
					break;
				case eRenderingMode::CutOut :
					mCutOutGameObjects.push_back(obj);
					break;
				case eRenderingMode::Transparent :
					mTransparentGameObjects.push_back(obj);
					break;
				default :
					break;
				}
			}
		}
	}
}

void CCamera::RenderOpaque()
{
	for (CGameObject* gameObj : mOpaqueGameObjects)
	{
		if (gameObj == nullptr)
			continue;

		gameObj->Render();
	}
}

void CCamera::RenderCutOut()
{
	for (CGameObject* gameObj : mCutOutGameObjects)
	{
		if (gameObj == nullptr)
			continue;

		gameObj->Render();
	}
}

void CCamera::RenderTransparent()
{
	for (CGameObject* gameObj : mTransparentGameObjects)
	{
		if (gameObj == nullptr)
			continue;

		gameObj->Render();
	}
}

void CCamera::TurnLayerMask(eLayerType type, bool enable)
{
	mLayerMask.set((UINT)type, enable);
}


