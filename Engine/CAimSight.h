#pragma once

enum class eAimSight
{
    Left,
    Right,
    Up,
    Down,
    End,
};

class CAimSight
{
private:
    eAimSight mAimSight;

public:
    CAimSight();
    ~CAimSight();

    void SetAimSight(eAimSight sight) { mAimSight = sight; }
    eAimSight GetAimSight() { return mAimSight; }
};

