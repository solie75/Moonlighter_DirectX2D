#pragma once
#include "CComponent.h"
class CScript :
    public CComponent
{
public:
	CScript();
	~CScript();

	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
};

