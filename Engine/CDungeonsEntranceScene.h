#pragma once
#include "CScene.h"
class CDungeonsEntranceScene :
    public CScene
{
public:
    CDungeonsEntranceScene();
    virtual ~CDungeonsEntranceScene();
    virtual void Initialize() override;
    virtual void Update() override;
    virtual void LateUpdate() override;
    virtual void Render() override;
};

