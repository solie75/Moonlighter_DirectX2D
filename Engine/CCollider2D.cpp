#include "CCollider2D.h"

CCollider2D::CCollider2D()
	//: CComponent(eComponentType::Collider2D)
    : mTransform(nullptr)
    , mColliderSize(Vector2::One)
    , mOffset(Vector2::Zero)
    , mIsCollider(false)
    , mDamage(0)
{
    mColliderNumber++;
    mColliderID = mColliderNumber;
    mCollideType = eCollideType::Background;
    mRotationValue = 0.0f;
    mLayerType = eLayerType::End;
    OwnerObjectSize = Vector2::One;
}


CCollider2D::~CCollider2D()
{
}

void CCollider2D::Initialize()
{
}

void CCollider2D::Update()
{
    if (mColliderDataList.size() == 0)
    {
        mIsCollider = false;
    }
    else if(mColliderDataList.size() > 0)
    {
        mIsCollider = true;
    }
}

void CCollider2D::LateUpdate(CTransform* tr)
{
    mLayerType = tr->GetOwner()->GetLayerType();


    Vector3 CdPos = tr->GetPosition();
    CdPos.x += mOffset.x; // offset
    CdPos.y += mOffset.y;

    mColliderPosition = CdPos;

    DebugMesh debugMesh = {};
    debugMesh.position = CdPos;
    debugMesh.scale = Vector3(mColliderSize.x, mColliderSize.y, 0.f);
    debugMesh.rotation = tr->GetRotation();
    debugMesh.ColliderType = eColliderType::Rect;
    debugMesh.CollideType = mCollideType;
    debugMesh.IsCollider = mIsCollider;
    
    CRenderMgr::GetInst()->AddDebugMesh(debugMesh);

    // �浹ü�� Worldmatrix ��ȯ
    mWorldMat = Matrix::Identity;
    Matrix scale = Matrix::CreateScale(Vector3(mColliderSize.x, mColliderSize.y, 0.f));
    Matrix rotation;
    rotation = Matrix::CreateRotationX(tr->GetRotation().x);
    rotation *= Matrix::CreateRotationY(tr->GetRotation().y);
    rotation *= Matrix::CreateRotationZ(tr->GetRotation().z + mRotationValue);
    Matrix position;
    position.Translation(CdPos);

    mWorldMat = scale * rotation * position;
}

void CCollider2D::Render()
{
}

//void CCollider2D::SetWorldMat(Vector3 scale)
void CCollider2D::SetWorldMat(Vector3 size, Vector3 pos)
{
    mWorldMat = Matrix::Identity;
    Matrix scale = Matrix::CreateScale(Vector3(size.x, size.y, 0.f));
    Matrix rotation;
    rotation = Matrix::CreateRotationX(0.0f);
    rotation *= Matrix::CreateRotationY(0.0f);
    rotation *= Matrix::CreateRotationZ(0.0f);
    Matrix position;
    position.Translation(pos);

    mWorldMat = scale * rotation * position;
}

void CCollider2D::OnCollisionEnter(CCollider2D* other)
{
    ColliderData data = {};
    data.id = other->GetColliderID(); // 0���� �����ϴµ� 0�� ���� �������� �������� ����ϹǷ�
    data.type = other->GetLayerType();
    data.pos = Vector2(other->GetColliderPosition().x, other->GetColliderPosition().y);
    data.damage = other->GetColliderDamage();

    mColliderDataList.insert(std::make_pair(data.id, data));
    this;
}

void CCollider2D::OnCollisionStay(CCollider2D* other)
{
}

void CCollider2D::OnCollisionExit(CCollider2D* other)
{
    std::map<UINT, ColliderData>::iterator iter = mColliderDataList.find(other->GetColliderID());
    if (iter != mColliderDataList.end())
    {
        mColliderDataList.erase(other->GetColliderID());
    }
}
