#pragma once
#include "CComponent.h"
class CScript :
    public CComponent
{
public:
	CScript();
	~CScript();

	virtual void Initialize();
	virtual void Update();
	virtual void LateUpdate();
	virtual void Render();
};

