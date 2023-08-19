#pragma once
#include "CScript.h"
#include "CTransform.h"
#include "CGameObject.h"

class CCameraMoveScript :
    public CScript
{
private:
    Vector3 playerPos;
    bool OnFixed; // �÷��̾� �߽����� ī�޶� ����
public:
    CCameraMoveScript();
    ~CCameraMoveScript();

    virtual void Initialize();
    virtual void Update();
    virtual void LateUpdate();
    virtual void Render();

    //void SetPlayerPos(CTransform* tr) { playerPos = tr->GetPosition(); }
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