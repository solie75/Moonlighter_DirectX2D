#pragma once
#include "CEntity.h"
#include "CComponent.h"
#include "CTransform.h"

class CGameObject :
    public CEntity
{
public:
    enum eState
    {
        Active,
        Paused,
        Dead,
    };

    enum eBehave
    {
        Idle,
        Walk,
        Roll,
    };

    enum eDirection
    {
        Down,
        Left,
        Right,
        Up,
    };

private:
    eState mState;
    eBehave mCurBehave;
    eBehave mPrevBehave;
    eDirection mDirection;
    std::vector<CComponent*> mComponent;

public:
    CGameObject();
    ~CGameObject();

    virtual void Initialize();
    virtual void Update();
    virtual void LateUpdate();
    virtual void Render();

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

    void Destroy() { mState = eState::Dead; }

    eState GetState() { return mState; }
    eBehave GetBehave() { return mCurBehave; }
    eBehave GetPrevBehave() { return mPrevBehave; }
    void SetBehave(eBehave behave) { mPrevBehave = mCurBehave; mCurBehave = behave; }
    eDirection GetDirection() { return mDirection; }
    void SetDirection(eDirection direction) { mDirection = direction; }
};

