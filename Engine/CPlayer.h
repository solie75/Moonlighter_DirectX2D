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

    CWeapon* mWeapon; // ���⿡ ���߿��� �ٸ� ���� ������ ������ ������ ��� �͵��� ���� �̱��� �κ��丮�� ���� �ȴ�.

    std::wstring mWeaponTypeStr;
    std::wstring mSightStr;

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

    void SetStrAboutState(std::wstring sight)
    {
        //mWeaponTypeStr = weaponType;
        mSightStr = sight;
    }

    std::wstring GetSightStr()
    {
        return mSightStr;
    }
};

