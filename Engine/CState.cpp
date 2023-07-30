#include "CState.h"

CState::CState()
	: mCurState(eState::Idle)
	, mPrevState(eState::Idle)
{
}

CState::~CState()
{
}
