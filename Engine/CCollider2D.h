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
        CCollider2D* otherCol;
    };

private:
    static UINT mColliderNumber;
    std::map<UINT, ColliderData> mColliderDataList; // UINT ���� id �� ColliderData ���� �浹�� �浹ü�� ������ �����Ѵ�.
    UINT mColliderID;
    eColliderType mColliderType;
    eCollideType mCollideType;

    CTransform* mTransform;

    //Vector3 mPosition;
    Vector2 OwnerObjectSize;

    Vector2 mColliderSize;
    Vector2 mOffset;
    float mRotationValue;

    Vector3 mColliderPosition;
    Vector3 mColliderScale;
    eLayerType mLayerType;

    CConstantBuffer* mColliderCB;
    
    UINT mDamage;

    Matrix mWorldMat;

    bool mIsCollider;
public:
    CCollider2D();
    ~CCollider2D();

    void Initialize();
    void Update();
    void LateUpdate(CTransform* tr);
    void Render();

    void SetWorldMat(Vector3 scale, Vector3 pos);

    void SetColliderType(eColliderType type) { mColliderType = type; }
    eColliderType GetColliderType() { return mColliderType; }
    void SetCollideType(eCollideType type) { mCollideType = type; }
    eCollideType GetCollideType() { return mCollideType; }

    eLayerType GetLayerType() { return mLayerType; }

    void SetOwnerObjectScale(Vector3 objScale)
    {
        
        OwnerObjectSize.x = objScale.x;
        OwnerObjectSize.y = objScale.y;

        // SetSize() �� ȣ������ �ʴ� ��� : �浹ü�� ��ü�� ũ�Ⱑ �Ȱ��� ���
        if (mColliderSize != Vector2::One)
        {
            mColliderSize.x *= objScale.x;
            mColliderSize.y *= objScale.y;
        }
        else
        {
            mColliderSize.x = objScale.x;
            mColliderSize.y = objScale.y;
        }
    }
    Vector2 GetSize() { return mColliderSize; }
    void SetSize(Vector2 size) { mColliderSize.x *= size.x; mColliderSize.y *= size.y; }
    void SetOffset(Vector2 offset) { mOffset = offset; }
    Vector2 GetOffset() { return mOffset; }
    UINT GetColliderID() { return mColliderID; }
    CConstantBuffer* GetColliderCB() { return mColliderCB; }
    bool GetIsCollider() { return mIsCollider; }
    void SetColliderDamage(UINT damage) { mDamage = damage; }
    UINT GetColliderDamage() { return mDamage; }
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
            data.otherCol = nullptr;

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
        data.otherCol = nullptr;

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
