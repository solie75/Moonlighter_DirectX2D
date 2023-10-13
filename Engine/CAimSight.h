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
    eSight mCurAimSight;
    eSight mPrevAimSight;
public:
    CAimSight();
    ~CAimSight();

    void SetSight(eSight sight) { mPrevAimSight = mCurAimSight;  mCurAimSight = sight; }
    eSight GetCurSight() { return mCurAimSight; }
    eSight GetPrevSight() { return mPrevAimSight; }
};

