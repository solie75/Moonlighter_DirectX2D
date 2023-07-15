#include "CCamera.h"
#include "CGameObject.h"

CCamera::CCamera()
	: CComponent(eComponentType::Camera)
	, mType(eProjectionType::OrthoGraphic)
	, mAspectRatio(1.0f)
	, mNear(1.0f)
	, mFar(1000.0f)
	, mSize(5.0f)
{
}

CCamera::~CCamera()
{
}

void CCamera::Initialize()
{
}

void CCamera::Update()
{
}

void CCamera::LateUpdate()
{
    CreateViewMatrix();
    CreateProjectionMatrix(mType);
}

void CCamera::Render()
{
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

