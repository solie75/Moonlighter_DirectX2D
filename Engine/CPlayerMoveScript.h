#pragma once
#include "CScript.h"
#include "CTransform.h"
#include "CGameObject.h"
#include "CKeyMgr.h"

class CPlayerMoveScript :
    public CScript
{
public:
    enum class eSubAttackState
    {
        Enter,
        Stay,
        Exit,
        End,
    };

private:
    UINT mComboAttackNum;
    bool mbNextCombo;
    //bool mbSubAttack;
    eSubAttackState mSubAttackState;
    bool mbplayerMove;

public:
    CPlayerMoveScript();
    ~CPlayerMoveScript();

    virtual void Initialize();
    virtual void Update();
    virtual void LateUpdate();

    UINT GetComboAttackNum() { return mComboAttackNum; }
    void ResetComboAttackNum() { mComboAttackNum = 0; }

    bool GetBoolNextCombo() { return mbNextCombo; }
    void SetBoolNextCombo(bool b) { mbNextCombo = b; }

    eSubAttackState GetSubAttackState() { return mSubAttackState; }
    void SetSubAttackState(eSubAttackState state) { mSubAttackState = state; }

};

