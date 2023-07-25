#pragma once
#include "CScript.h"
#include "CTransform.h"
#include "CGameObject.h"
#include "CKeyMgr.h"

class CPlayerMoveScript :
    public CScript
{
private:
    KEY mKey;
    KEY_STATE CurState;
    KEY_STATE PrevState;
    bool bAni;
    float bAniTime;
    bool bRoll;

public:
    CPlayerMoveScript();
    ~CPlayerMoveScript();

    virtual void Initialize();
    virtual void Update();
    virtual void LateUpdate();

    KEY GetKey() { return mKey; }
    void SetKey(KEY key) { mKey = key; }
    KEY_STATE GetKeyState() { return CurState; }
    void SetKeyState(KEY_STATE state) { PrevState = CurState; CurState = state; }

};

