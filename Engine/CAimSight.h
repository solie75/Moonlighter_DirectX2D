#pragma once



class CAimSight
{
public:
    enum class eSight
    {
        Left,
        Right,
        Up,
        Down,
        End,
    };

private:
    eSight mAimSight;

public:
    CAimSight();
    ~CAimSight();

    void SetSight(eSight sight) { mAimSight = sight; }
    eSight GetSight() { return mAimSight; }
};

