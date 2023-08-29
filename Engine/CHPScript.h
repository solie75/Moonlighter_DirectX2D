#pragma once
#include "CScript.h"
class CHPScript :
    public CScript
{
public:
	CHPScript();
	~CHPScript();

	virtual void Initialize();
	virtual void Update();
	virtual void LateUpdate();
	virtual void Render();
};

