#pragma once
#include "CScene.h"
class CPlayScene :
    public CScene
{
public:
	CPlayScene();
	virtual ~CPlayScene();
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
};

