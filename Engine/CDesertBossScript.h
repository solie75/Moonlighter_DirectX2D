#pragma once
#include "CScript.h"
#include "CFireBall.h"
#include "CScene.h"
#include "CAimSight.h"
#include "CState.h"


class CDesertBossScript :
    public CScript
{
private:
	std::vector<CFireBall*> projectiles;
	Vector2 AimDirection;
	CState mState;
	CAimSight mAimSight; // AimAngle 에 따라서 상하좌우 로 나눈다.
	Vector2 mAimNormal; // 객체가 바라보는 방향 벡터
	float mAimAngle; // 객체가 바라보는 방향을 360 로 나눈다.

	
public:
	CDesertBossScript();
	~CDesertBossScript();

	virtual void Initialize();
	virtual void Update();
	virtual void LateUpdate();
	virtual void Render();
};

