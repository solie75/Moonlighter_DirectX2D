#pragma once
#include "CScript.h"
class CHPScript :
    public CScript
{
private:
	UINT mFullHP;
	UINT mCurHP;
	float mFullWidth;
	float mLeftXPos;

public:
	CHPScript();
	~CHPScript();

	virtual void Initialize();
	virtual void Update();
	virtual void LateUpdate();
	virtual void Render();

	//void SetLeftXPos(float xPos) { mLeftXPos = xPos; }
};

