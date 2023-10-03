#pragma once
//#include "CComponent.h"
#include "CEntity.h"
#include "CTransform.h"



class CCollider2D 
    // : public CComponent
    : public CEntity
{
public:
    struct ColliderData
    {
        UINT id;
        eLayerType type;
        Vector2 pos;
        UINT damage;
    };

private:
    static UINT mColliderNumber;
    std::map<UINT, ColliderData> mColliderDataList; // UINT ���� id �� ColliderData ���� �浹�� �浹ü�� ������ �����Ѵ�.
    UINT mColliderID;
    eColliderType mColliderType;
    eCollideType mCollideType;

    CTransform* mTransform;

    //Vector3 mPosition;
    Vector2 mSize;
    Vector2 mOffset;
    float mRotationValue;

    Vector3 mColliderPosition;
    Vector3 mColliderScale;
    eLayerType mLayerType;

    CConstantBuffer* mColliderCB;
    
    UINT mDamege;

    Matrix mWorldMat;

    bool mIsCollider;
public:
    CCollider2D();
    ~CCollider2D();

    void Initialize();
    void Update();
    void LateUpdate(CTransform* tr);
    void Render();

    void SetColliderType(eColliderType type) { mColliderType = type; }
    eColliderType GetColliderType() { return mColliderType; }
    void SetCollideType(eCollideType type) { mCollideType = type; }
    eCollideType GetCollideType() { return mCollideType; }

    eLayerType GetLayerType() { return mLayerType; }

    //Vector2 GetColliderPosition() { return Vector2(mPosition.x, mPosition.y); }
    Vector2 GetSize() { return mSize; }
    void SetSize(Vector2 size) { mSize = size; }
    void SetOffset(Vector2 offset) { mOffset = offset; }
    Vector2 GetOffset() { return mOffset; }
    UINT GetColliderID() { return mColliderID; }
    CConstantBuffer* GetColliderCB() { return mColliderCB; }
    bool GetIsCollider() { return mIsCollider; }
    UINT GetColliderDamege() { return mDamege; }
    Matrix& GetColliderWorldMatrix() { return mWorldMat; }
    Vector3 GetColliderPosition() { return mColliderPosition; }
    Vector3 GetColliderScale() { return mColliderScale; }

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
            data.id = 0;
            data.type = eLayerType::End;
            data.pos = Vector2(0.0f, 0.0f);
            data.damage = 0;

            return data;
        }
    }

    ColliderData GetColliderData(eLayerType type)
    {
        ColliderData data;
        data.id = 0;
        data.type = eLayerType::End;
        data.pos = Vector2(0.0f, 0.0f);
        data.damage = 0;

        if (mColliderDataList.size() == 0)
        {
            return data;
        }

        for (const auto& col : mColliderDataList)
        {
            if (col.second.type == type)
            {
                return col.second;
            }
            else
            {
                return data;
            }
        }
    }

    void OnCollisionEnter(CCollider2D* other);
    void OnCollisionStay(CCollider2D* other);
    void OnCollisionExit(CCollider2D* other);
};

UINT CCollider2D::mColliderNumber = 0;
