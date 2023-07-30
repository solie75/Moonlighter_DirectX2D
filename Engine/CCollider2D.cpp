#include "CCollider2D.h"

CCollider2D::CCollider2D()
	: CComponent(eComponentType::Collider2D)
    , mTransform(nullptr)
    , mSize(Vector2::One)
    , mCenter(Vector2::Zero)
{
    mColliderNumber++;
    mColliderID = mColliderNumber;
}


CCollider2D::~CCollider2D()
{
}

void CCollider2D::Initialize()
{
    mTransform = GetOwner()->GetComponent<CTransform>(eComponentType::Transform);
}

void CCollider2D::Update()
{
}

void CCollider2D::LateUpdate()
{
    CTransform* tr = GetOwner()->GetComponent<CTransform>(eComponentType::Transform);
    
    Vector3 scale = tr->GetScale();
    scale.x *= mSize.x;
    scale.y *= mSize.y;

    Vector3 pos = tr->GetPosition();
    pos.x += mCenter.x;
    pos.y += mCenter.y;

    mPosition = pos;
    DebugMesh debugMesh = {};
    debugMesh.position = mPosition;
    debugMesh.scale = scale;
    debugMesh.rotation = tr->GetRotation();
    debugMesh.type = eColliderType::Rect;
    
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
    //const std::vector<
}

void CCollider2D::OnCollisionStay(CCollider2D* other)
{
}

void CCollider2D::OnCollisionExit(CCollider2D* other)
{
}
