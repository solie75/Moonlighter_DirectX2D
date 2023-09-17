#pragma once
#include "CScene.h"
class CDesertDungeonScene :
    public CScene
{
public:
    CDesertDungeonScene();
    ~CDesertDungeonScene();

    void Initialize();
    void Update();
    void LateUpdate();
    void Render();
};

