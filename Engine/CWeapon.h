#pragma once
#include "CGameObject.h"
#include "Header.h"
#include "CPlayer.h"
#include "CArrow.h"


class CWeapon :
    public CGameObject
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
    // ���� ��� �ִ� ���� ����
    eWeaponType mMainWeaponType; 

    // ���� �� ������ ������� ����
    eBigSwordType mBigSwordType; 
    eBowType mBowType;
    eSpearType mSpearType;
    std::wstring mAniName;
    UINT mComboNum;
    bool mbArrow;

    //CPlayer* mPlayer;
    CScene* ownScene;
public:
    CWeapon();
    ~CWeapon();

    virtual void Initialize();
    virtual void Update();
    virtual void LateUpdate();
    virtual void Render();

    eWeaponType GetWeaponType() { return mMainWeaponType; }
    eBowType GetBowType() { return mBowType; }

    // �� ���⸦ ���׷��̵� �� ������ �ش� �Լ��� ���� ������ type �� �����Ѵ�. 
    void SetBigSwordType();
    void SetBowType();
    void SetSpearType();
    
    void ResetWeaponAniName() { mAniName = L"Weapon"; };

    // �ش� Weapon �� �⺻���� �ʱ�ȭ �Ѵ�.
    void ResetUpgrade(eWeaponType type);
    void SetScene(CScene* scene) { ownScene = scene; }
    void SetComboNum(UINT num) { mComboNum = num; }
    //void SetPlayerToWeapon(CPlayer* player) { mPlayer = player; }
    void SetWeaponType(eWeaponType type) { mMainWeaponType = type; }
};

