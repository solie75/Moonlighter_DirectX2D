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
    Vector2 mOffset;

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
    void SetOffset(Vector2 offset) { mOffset = offset; }
    UINT GetColliderID() { return mColliderID; }
    //void SetColPositionOffset(Vector3 offset);
    CConstantBuffer* GetColliderCB() { return mColliderCB; }
    bool GetIsCollider() { return mIsCollider; }
    size_t GetColliderDataListSize()
    {
        return mColliderDataList.size();
    }
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

    ColliderData GetColliderData(UINT id)
    {
        std::map<UINT, ColliderData>::iterator iter = mColliderDataList.find(id);
        if (iter == mColliderDataList.end())
        {
            return iter->second;
        }
        else
        {
            ColliderData data;
            data.id = -1;
            data.type = eLayerType::End;
            data.pos = Vector2(0.0f, 0.0f);

            return data;
        }
    }

    ColliderData GetColliderData(eLayerType type)
    {
        for (const auto& col : mColliderDataList)
        {
            if (col.second.type == type)
            {
                return col.second;
            }
            else
            {
                ColliderData data;
                data.id = -1;
                data.type = eLayerType::End;
                data.pos = Vector2(0.0f, 0.0f);

                return data;
            }
        }

    }

    void OnCollisionEnter(CCollider2D* other);
    void OnCollisionStay(CCollider2D* other);
    void OnCollisionExit(CCollider2D* other);
};

UINT CCollider2D::mColliderNumber = 0;
