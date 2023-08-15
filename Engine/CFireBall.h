#pragma once
#include "CGameObject.h"
class CFireBall :
    public CGameObject
{
public:
    enum class ProjectileState
    {
        Idle,
        Collide,
        End,
    };
private:
    int DirectNum;
    Vector3 direction;
    Vector3 pos;
    float speed;
    float time;

public:
    CFireBall();
    //CFireBall(int num, Vector3 pos) : DirectNum(num) {};
    ~CFireBall();

    virtual void Initialize();
    virtual void Update();
    virtual void LateUpdate();
    virtual void Render();

    void SetDirection(Vector3 direct) { direction = direct; }
    void SetSpeed(float f) { speed = f; }
};

