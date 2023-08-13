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
	CState mCurState;
	CState mPrevState;
	CAimSight mAimSight; // AimAngle �� ���� �����¿� �� ������.
	Vector2 mAimNormal; // ��ü�� �ٶ󺸴� ���� ����
	float mAimAngle; // ��ü�� �ٶ󺸴� ������ 360 �� ������.

	
public:
	CDesertBossScript();
	~CDesertBossScript();

	virtual void Initialize();
	virtual void Update();
	virtual void LateUpdate();
	virtual void Render();
};

