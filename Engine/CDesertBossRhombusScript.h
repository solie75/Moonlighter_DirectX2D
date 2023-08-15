#pragma once
#include "CScript.h"

class CDesertBossRhombusScript :
    public CScript
{
public:
    enum class eRhombusAttackState
    {
        Enter,
        Stay,
        Exit,
        End,
    };

private:
    static float angleNum; // �� �߻� ���� ������ ���ݾ� �޶����� ����
    float diff;
    CScene* ownScene;
    float fireballInterval;
    int fireCount;

    eRhombusAttackState mRhombusAttackState;
    eRhombusAttackState mPrevRhombusAttackState;

public:
    CDesertBossRhombusScript();
    ~CDesertBossRhombusScript();

    virtual void Initialize();
    virtual void Update();
    virtual void LateUpdate();
    virtual void Render();

    void SetScene(CScene* scene) { ownScene = scene; }

    void ChangeRhombusAttackState(eRhombusAttackState state)
    {
        mPrevRhombusAttackState = mRhombusAttackState;
        mRhombusAttackState = state;
    }
};

float CDesertBossRhombusScript::angleNum = 0.f;