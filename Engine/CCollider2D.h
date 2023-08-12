#pragma once
#include "CComponent.h"
#include "CTransform.h"


class CCollider2D :
    public CComponent
{
private:
    static UINT mColliderNumber;
    UINT mColliderID;
    eColliderType mType;

    CTransform* mTransform;

    Vector3 mPosition;
    Vector2 mSize;
    Vector2 mCenter;

    CConstantBuffer* mColliderCB;
    
    bool mIsCollider;
    int mCollideCount; // Ãæµ¹ ÁßÃ¸ È½¼ö
public:
    CCollider2D();
    ~CCollider2D();

    virtual void Initialize() override;
    virtual void Update() override;
    virtual void LateUpdate() override;
    virtual void Render() override;

    void SetType(eColliderType type) { mType = type; }
    Vector2 GetSize() { return mSize; }
    void SetSize(Vector2 size) { mSize = size; }
    void SetCenter(Vector2 size) { mCenter = size; }
    UINT GetColliderID() { return mColliderID; }
    void SetColPositionOffset(Vector3 offset);
    CConstantBuffer* GetColliderCB() { return mColliderCB; }
    bool GetIsCollider() { return mIsCollider; }
    void MinusColliderNum() { mCollideCount--; }

    void OnCollisionEnter(CCollider2D* other);
    void OnCollisionStay(CCollider2D* other);
    void OnCollisionExit(CCollider2D* other);
};

UINT CCollider2D::mColliderNumber = 0;
