#include "CState.h"

CState::CState()
	: mCurState(eState::Idle)
	, mPrevState(eState::End)
	, mbStateChange(true)
	, mStateTime(0.0f)
{
}

CState::~CState()
{
}
