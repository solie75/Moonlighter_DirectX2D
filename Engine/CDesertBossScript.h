#pragma once
#include "CScript.h"
#include "CFireBall.h"
#include "CScene.h"

class CDesertBossScript :
    public CScript
{
private:
	std::vector<CFireBall*> projectiles;
	
public:
	CDesertBossScript();
	~CDesertBossScript();

	virtual void Initialize();
	virtual void Update();
	virtual void LateUpdate();
	virtual void Render();
};

