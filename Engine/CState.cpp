#include "CState.h"

CState::CState()
	: mCurState(eState::Idle)
	, mPrevState(eState::Idle)
	, mbStateChange(true)
	, mStateTime(0.0f)
{
}

CState::~CState()
{
}
