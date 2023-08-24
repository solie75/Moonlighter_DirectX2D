#pragma once
#include "CScene.h"
class CDesertBossScene :
    public CScene
{
private:
	CAnimator* BossBornAt;
public:
	CDesertBossScene();
	virtual ~CDesertBossScene();
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
};

