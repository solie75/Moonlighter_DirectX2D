#pragma once
#include "CScene.h"
#include "CPlayer.h"

class CDesertDungeonScene :
    public CScene
{
private:
    CPlayer* player;
    CGameObject* mainCamera;

    float mXPosStandard = 8.202f;
    float mYPosStandard = 4.492f;

    bool mbTranslateMapPos;

    Vector2 NextMapPos;
public:
    CDesertDungeonScene();
    ~CDesertDungeonScene();

    void Initialize();
    void Update();
    void LateUpdate();
    void Render();

    void SetBoolTranslateMapPos(bool b) { mbTranslateMapPos = b; }
};

