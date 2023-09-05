#pragma once
#include "CScript.h"
#include "CTransform.h"
#include "CGameObject.h"
#include "CKeyMgr.h"

class CPlayerMoveScript :
    public CScript
{
private:
    UINT mComboAttackNum;
    bool mbNextCombo;

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

};

