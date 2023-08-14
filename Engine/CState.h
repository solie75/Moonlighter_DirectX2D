#pragma once

enum class eState
{
    Idle,
    Attack,
    Hit,
	Collide,
    Roll,
    Walk,
    End,
};

class CState
{
private:
	eState mCurState;
	eState mPrevState;
	bool mbStateChange;
	float mStateTime;

public:
	CState();
	~CState();

	void SetState(eState state) { mPrevState = mCurState;  mCurState = state; }
	eState GetCurState() { return mCurState; }
	eState GetPrevState() { return mPrevState; }
	bool IsStateChange() { return mbStateChange; }
	void SetBoolStateChange(bool b) { mbStateChange = b; }
	float GetStateTime() { return mStateTime; }
	void StateTimeReset() { mStateTime = 0.0f; }
	void SetStateTime(float time) { mStateTime = time; }
};

