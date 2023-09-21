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
    //bool OnFixedToPlayer; // 플레이어 중심으로 카메라 고정
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
    void MoveCameraForMap();
};