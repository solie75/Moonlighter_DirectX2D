#pragma once

enum class eState
{
    Idle,
    Attack,
    Hit,
    Roll,
    Walk,
    End,
};

class CState
{
private:
	eState mCurState;
	eState mPrevState;

public:
	CState();
	~CState();

	void SetState(eState state) { mPrevState = mCurState;  mCurState = state; }
	eState GetCurState() { return mCurState; }
	eState GetPrevState() { return mPrevState; }
};

