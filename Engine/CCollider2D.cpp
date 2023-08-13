#include "CCollider2D.h"

CCollider2D::CCollider2D()
	: CComponent(eComponentType::Collider2D)
    , mTransform(nullptr)
    , mSize(Vector2::One)
    , mCenter(Vector2::Zero)
    , mIsCollider(false)
    //, mCollideCount(0)
{
    mColliderNumber++;
    mColliderID = mColliderNumber;
}


CCollider2D::~CCollider2D()
{
}

void CCollider2D::Initialize()
{
}

void CCollider2D::Update()
{
    /*if (mCollideCount == 0)
    {
        mIsCollider = false;
    }
    else if(mCollideCount > 0)
    {
        mIsCollider = true;
    }*/
    if (vCollisionIDs.size() == 0)
    {
        mIsCollider = false;
    }
    else if (vCollisionIDs.size() > 0)
    {
        mIsCollider = true;
    }
}

void CCollider2D::LateUpdate()
{
    CTransform* tr = GetOwner()->GetComponent<CTransform>(eComponentType::Transform);
    
    Vector3 scale = tr->GetScale();
    scale.x *= mSize.x;
    scale.y *= mSize.y;

    Vector3 pos = tr->GetPosition();
    pos.x += mCenter.x; // offset
    pos.y += mCenter.y;

    mPosition = pos;
    DebugMesh debugMesh = {};
    debugMesh.position = mPosition;
    debugMesh.scale = scale;
    debugMesh.rotation = tr->GetRotation();
    debugMesh.type = eColliderType::Rect;
    debugMesh.IsCollider = mIsCollider;
    
    CRenderMgr::GetInst()->AddDebugMesh(debugMesh);
}

void CCollider2D::Render()
{
}

void CCollider2D::SetColPositionOffset(Vector3 offset)
{
    mPosition.x += offset.x;
    mPosition.y += offset.y;
    mPosition.z += offset.z;
}

void CCollider2D::OnCollisionEnter(CCollider2D* other)
{
    //mCollideCount += 1;
    vCollisionIDs.push_back(other->GetColliderID()); // 이미 존재하는 경우 추가 하지 않는다. 이게 가능한가? 이미 존재하는 데 또 OnCollisionEnter 가 될 수 있나?
}

void CCollider2D::OnCollisionStay(CCollider2D* other)
{
}

void CCollider2D::OnCollisionExit(CCollider2D* other)
{
    std::vector<UINT>::iterator EraseIter = std::remove(vCollisionIDs.begin(), vCollisionIDs.end(), other->GetColliderID());
    vCollisionIDs.erase(EraseIter, vCollisionIDs.end());
}
