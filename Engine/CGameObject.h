#pragma once
#include "CEntity.h"
#include "CComponent.h"
#include "CTransform.h"

class CGameObject :
    public CEntity
{
public:
    enum eObjectState
    {
        Active,
        Paused,
        Dead,
    };

private:
    eObjectState mState;
    std::vector<CComponent*> mComponent;
    CGameObject* mParentObject;

public:
    CGameObject();
    ~CGameObject();

    virtual void Initialize();
    virtual void Update();
    virtual void LateUpdate();
    virtual void Render();


    void Destroy() { mState = eObjectState::Dead; }
    eObjectState GetState() { return mState; }
    CGameObject* GetParentObject() { return mParentObject; }
    void SetParentObject(CGameObject* pObj) { mParentObject = pObj; }

    template <typename T>
    T* AddComponent()
    {
        T* comp = new T();
        mComponent.push_back(comp);
        comp->SetOwner(this);

        return comp;
    }

    template <typename T>
    T* GetComponent(eComponentType type)
    {
        //T* component;
        for (CComponent* comp : mComponent)
        {
            if (type == comp->GetType())
            {
                return dynamic_cast<T*>(comp);
            }
        }

        return nullptr;
    }

};

