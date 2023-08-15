#pragma once
#include "CScript.h"
#include "CFireBall.h"
#include "CScene.h"
#include "CAimSight.h"
#include "CState.h"


class CDesertBossScript :
    public CScript
{
public:
	enum class eAttackState
	{
		Circle,
		RhomBus,
		End
	};

private:
	std::vector<CFireBall*> projectiles;
	//Vector2 AimDirection;
	CState mState;
	CAimSight mAimSight; // AimAngle 에 따라서 상하좌우 로 나눈다.
	Vector2 mAimNormal; // 객체가 바라보는 방향 벡터
	float mAimAngle; // 객체가 바라보는 방향을 360 로 나눈다.

	int CircleAttackNum;
	int RhombusAttackNum;
	//int CircleAttackNum;
	//int CircleAttackNum;
	double time;

	eAttackState mAttackState;

	int CollideCount;
public:
	CDesertBossScript();
	~CDesertBossScript();

	virtual void Initialize();
	virtual void Update();
	virtual void LateUpdate();
	virtual void Render();

	eAttackState GetAttackState() { return mAttackState; }
	void ResetAttackState() { mAttackState = eAttackState::End; }

	int GetCollideCount() { return CollideCount; }
	void ResetCollideCount() { CollideCount = 0; }
};

