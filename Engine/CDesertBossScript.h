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
		Rhombus,
		Square,
		Triangle,
		Parts,
		End
	};

private:
	std::vector<CFireBall*> projectiles;
	CState mState;
	CAimSight mAimSight; // AimAngle 에 따라서 상하좌우 로 나눈다.
	Vector2 mAimNormal; // 객체가 바라보는 방향 벡터
	Vector2 mExpectedAimNormal; // 벽에 충돌했을 때 설정되는 목표 방향 벡터.
	Vector2 mDiffAimNormal; // 목표 방향 벡터와 현재 방향 벡터의 차
	double mChangeAimTime;
	float speed;
	
	float mAimAngle; // 객체가 바라보는 방향을 360 로 나눈다.

	int CircleAttackNum;
	int RhombusAttackNum;
	int TriangleAttackNum;
	double FireAttackTime;
	double PartsAttackTime;
	
	eAttackState mAttackState;

	int CollideCount;
	int TurnCount;
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

