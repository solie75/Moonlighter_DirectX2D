#pragma once
#include "CScript.h"
class CDesertBossRhombusScript :
    public CScript
{
private:
    static float angleNum; // �� �߻� ���� ������ ���ݾ� �޶����� ����
    float diff;
    CScene* ownScene;
    float fireballInterval;
    int fireCount;

public:
    CDesertBossRhombusScript();
    ~CDesertBossRhombusScript();

    virtual void Initialize();
    virtual void Update();
    virtual void LateUpdate();
    virtual void Render();

    void SetScene(CScene* scene) { ownScene = scene; }
};

float CDesertBossRhombusScript::angleNum = 0.f;