#pragma once
//#include "CCreatureObject.h"
#include "CGameObject.h"
#include "CState.h"
#include "CAimSight.h"
//#include "CWeapon.h"

class CWeapon;

class CPlayer :
    public CGameObject
{
private:
    eCreatureType mCreatureType;
    CState* mState;
    CAimSight* mAimSight;
    UINT AttackComboNum;

    CWeapon* mWeapon; // 여기에 나중에는 다른 방어구와 아이템 물약을 포함한 모든 것들을 가진 싱글톤 인벤토리가 들어가게 된다.

public:
    CPlayer();
    ~CPlayer();

    virtual void Initialize();
    virtual void Update();
    virtual void LateUpdate();
    virtual void Render();

    eCreatureType GetCreatureType() { return mCreatureType; }
    CState* GetState() { return mState; }
    CAimSight* GetAimSight() { return mAimSight; }
    void SetWeapon(CWeapon* weapon) { mWeapon = weapon; }
    CWeapon* GetWeapon() { return mWeapon; }
};

