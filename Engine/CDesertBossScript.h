#pragma once
#include "CScript.h"
class CDesertBossScript :
    public CScript
{
public:
	CDesertBossScript();
	~CDesertBossScript();

	virtual void Initialize();
	virtual void Update();
	virtual void LateUpdate();
	virtual void Render();
};

