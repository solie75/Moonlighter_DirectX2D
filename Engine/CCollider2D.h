#pragma once
#include "CComponent.h"
#include "CTransform.h"


class CCollider2D :
    public CComponent
{
public:
    struct ColliderData
    {
        UINT id;
        eLayerType type;
        Vector2 pos;
    };

private:
    static UINT mColliderNumber;
    std::map<UINT, ColliderData> mColliderDataList; // UINT 에는 id 를 ColliderData 에는 충돌한 충돌체의 정보를 저장한다.
    UINT mColliderID;
    eColliderType mType;

    CTransform* mTransform;

    Vector3 mPosition;
    Vector2 mSize;
    Vector2 mCenter;

    CConstantBuffer* mColliderCB;
    
    bool mIsCollider;
public:
    CCollider2D();
    ~CCollider2D();

    virtual void Initialize() override;
    virtual void Update() override;
    virtual void LateUpdate() override;
    virtual void Render() override;

    void SetType(eColliderType type) { mType = type; }
    eColliderType GetColliderType() { return mType; }
    Vector2 GetColliderPosition() { return Vector2(mPosition.x, mPosition.y); }
    Vector2 GetSize() { return mSize; }
    void SetSize(Vector2 size) { mSize = size; }
    void SetCenter(Vector2 size) { mCenter = size; }
    UINT GetColliderID() { return mColliderID; }
    void SetColPositionOffset(Vector3 offset);
    CConstantBuffer* GetColliderCB() { return mColliderCB; }
    bool GetIsCollider() { return mIsCollider; }
    bool FindColliderID(UINT id)
    {
        std::map<UINT, ColliderData>::iterator iter = mColliderDataList.find(id);
        if (iter == mColliderDataList.end())
        {
           return false;
        }
        else
        {
           return true;
        }
    }

    void OnCollisionEnter(CCollider2D* other);
    void OnCollisionStay(CCollider2D* other);
    void OnCollisionExit(CCollider2D* other);
};

UINT CCollider2D::mColliderNumber = 0;
