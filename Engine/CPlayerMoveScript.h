#pragma once
#include "CScript.h"
#include "CTransform.h"
#include "CGameObject.h"
#include "CKeyMgr.h"

class CPlayerMoveScript :
    public CScript
{
private:
    //KEY mKey;
    //KEY_STATE mLeftKey;
    //KEY_STATE mRightKey;
    //KEY_STATE mUpKey;
    //KEY_STATE mDownKey;
    //bool bAni;
    //float mAniTime;
    //bool bRoll;
    UINT mComboAttackNum;

public:
    CPlayerMoveScript();
    ~CPlayerMoveScript();

    virtual void Initialize();
    virtual void Update();
    virtual void LateUpdate();

    UINT GetComboAttackNum() { return mComboAttackNum; }
    void ResetComboAttackNum() { mComboAttackNum = 0; }

    //KEY GetKey() { return mKey; }
    //void SetKey(KEY key) { mKey = key; }
    //KEY_STATE GetKeyState() { return CurState; }
    //void SetKeyState(KEY_STATE state) { PrevState = CurState; CurState = state; }

};

