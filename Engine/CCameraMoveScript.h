#pragma once
#include "CScript.h"
//#include "CTransform.h"
#include "CGameObject.h"

class CTransform;

class CCameraMoveScript :
    public CScript
{
public:
    enum class eCameraFocusing
    {
        Player,
        Map,
        None,
        End,
    };

private:
    //bool OnFixedToPlayer; // �÷��̾� �߽����� ī�޶� ����
    //bool OnFinxedToMap;

    eCameraFocusing cameraFocused;
    CTransform* PlayerTr;
    Vector2 FocusedOnMapPos;

public:
    CCameraMoveScript();
    ~CCameraMoveScript();

    virtual void Initialize();
    virtual void Update();
    virtual void LateUpdate();
    virtual void Render();

    void SetPlayerTr(CTransform* tr) { PlayerTr = tr; }
    void ChangeCameraFocusing(eCameraFocusing cf)
    {
        cameraFocused = cf;
    }
    void SetMapPos(Vector2 v2)
    {
        FocusedOnMapPos = v2;
    }
    Vector2 GetFocusedMapPos() { return FocusedOnMapPos; }
};