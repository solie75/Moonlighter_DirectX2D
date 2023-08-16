#pragma once
#include "CScene.h"
class CPlayScene :
    public CScene
{
private:
	CAnimator* BossBornAt;
public:
	CPlayScene();
	virtual ~CPlayScene();
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
};

