#pragma once
#include "CScene.h"
class CTestScene :
    public CScene
{
public:
    CTestScene();
    ~CTestScene();

    void Initialize();
    void Update();
    void LateUpdate();
    void Render();
};

