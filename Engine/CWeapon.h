#pragma once
#include "CSingleton.h"

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

public:
    CWeapon();
    ~CWeapon();

    virtual void Initialize();
    virtual void Update();
    virtual void LateUpdate();
    virtual void Render();

    eWeaponType GetWeaponType() { return mMainWeaponType; }
    std::wstring AddWeaponName();
};

