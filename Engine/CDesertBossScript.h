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
	CAimSight mAimSight; // AimAngle �� ���� �����¿� �� ������.
	Vector2 mAimNormal; // ��ü�� �ٶ󺸴� ���� ����
	Vector2 mExpectedAimNormal; // ���� �浹���� �� �����Ǵ� ��ǥ ���� ����.
	Vector2 mDiffAimNormal; // ��ǥ ���� ���Ϳ� ���� ���� ������ ��
	double mChangeAimTime;
	float speed;
	
	float mAimAngle; // ��ü�� �ٶ󺸴� ������ 360 �� ������.

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

