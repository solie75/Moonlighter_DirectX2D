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
	CAimSight mAimSight; // AimAngle �� ���� �����¿� �� ������.
	Vector2 mAimNormal; // ��ü�� �ٶ󺸴� ���� ����
	float mAimAngle; // ��ü�� �ٶ󺸴� ������ 360 �� ������.

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

