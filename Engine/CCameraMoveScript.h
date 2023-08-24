#pragma once
#include "CScript.h"
//#include "CTransform.h"
#include "CGameObject.h"

class CTransform;

class CCameraMoveScript :
    public CScript
{
private:
    bool OnFixed; // 플레이어 중심으로 카메라 고정

    CTransform* PlayerTr;

public:
    CCameraMoveScript();
    ~CCameraMoveScript();

    virtual void Initialize();
    virtual void Update();
    virtual void LateUpdate();
    virtual void Render();

    void SetPlayerTr(CTransform* tr) { PlayerTr = tr; }
    void ChangeCameraFixMode()
    {
        if (OnFixed == false)
        {
            OnFixed = true;
        }
        else
        {
            OnFixed = false;
        }
    }
};