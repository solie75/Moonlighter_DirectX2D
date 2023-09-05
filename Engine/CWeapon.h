#pragma once
#include "CSingleton.h"
#include "Header.h"
#include "CPlayer.h"


class CWeapon :
    public CSingleton<CWeapon>
{
public:
    enum class eWeaponType
    {
        Spear,
        Bow,
        BigSword,
        End,
    };

    enum class eBigSwordType
    {
        Vulcan,
        Blaze,
        Storm,
        Wild,
        End,
    };

    enum class eBowType
    {
        Hunter,
        Poison,
        Soldier,
        FlameThrower,
        End,
    };

    enum class eSpearType
    {
        Warrior,
        Venom, // poison
        Fighter,
        Hell, // flame
        End,
    };

private:
    // 현재 들고 있는 무기 종류
    eWeaponType mMainWeaponType; 

    // 현재 각 종류의 무기들의 버전
    eBigSwordType mBigSwordType; 
    eBowType mBowType;
    eSpearType mSpearType;
    CPlayer* mOwner;
    std::wstring mAniName;

public:
    CWeapon();
    ~CWeapon();

    virtual void Initialize();
    virtual void Update();
    virtual void LateUpdate();
    virtual void Render();

    eWeaponType GetWeaponType() { return mMainWeaponType; }

    // 각 무기를 업그레이드 할 때마다 해당 함수로 현재 무기의 type 을 변경한다. 
    void SetBigSwordType();
    void SetBowType();
    void SetSpearType();
    
    void ResetWeaponAniName() { mAniName = L"Weapon"; };

    // 해당 Weapon 을 기본으로 초기화 한다.
    void ResetUpgrade(eWeaponType type);
    void SetOwner(CPlayer* player) { mOwner = player; }
};

