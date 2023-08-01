#include "CPlayerMoveScript.h"
#include "CTimeMgr.h"
#include "CAnimator.h"
#include "CPlayer.h"


CPlayerMoveScript::CPlayerMoveScript()
	: mKey(KEY::END)
	, CurState(KEY_STATE::NONE)
	, PrevState(KEY_STATE::NONE)
	, bAni(true) // true 일때 애니메이션 작동 // false 일때 애니메이션 비작동
	, bAniTime(0.0f)
{
}

CPlayerMoveScript::~CPlayerMoveScript() {}

void CPlayerMoveScript::Initialize() {}

void CPlayerMoveScript::Update()
{
	CTransform* tr = GetOwner()->GetComponent<CTransform>(eComponentType::Transform);
	Vector3 pos = tr->GetPosition();
	CAnimator* at = GetOwner()->GetComponent<CAnimator>(eComponentType::Animator);
	CPlayer* player = dynamic_cast<CPlayer*>(GetOwner());
	CState* state = player->GetState();
	CAimSight* aimSight = player->GetAimSight();

	if (state->IsStateChange()) // 키 입력 가능 여부
	{
		// 방향전환
		if (CKeyMgr::GetInst()->GetKeyState(KEY::LEFT) == KEY_STATE::TAP)
		{
			aimSight->SetAimSight(eAimSight::Left);
		}
		if (CKeyMgr::GetInst()->GetKeyState(KEY::RIGHT) == KEY_STATE::TAP)
		{
			aimSight->SetAimSight(eAimSight::Right);
		}
		if (CKeyMgr::GetInst()->GetKeyState(KEY::UP) == KEY_STATE::TAP)
		{
			aimSight->SetAimSight(eAimSight::Up);
		}
		if (CKeyMgr::GetInst()->GetKeyState(KEY::DOWN) == KEY_STATE::TAP)
		{
			aimSight->SetAimSight(eAimSight::Down);
		}

		// 캐릭터 위치 변화
		if (CKeyMgr::GetInst()->GetKeyState(KEY::LEFT) == KEY_STATE::PRESSED)
		{
			pos.x -= (float)(2.0 * CTimeMgr::GetInst()->GetDeltaTime());
			tr->SetPosition(pos);
			state->SetState(eState::Walk);
		}
		if (CKeyMgr::GetInst()->GetKeyState(KEY::RIGHT) == KEY_STATE::PRESSED)
		{
			pos.x += (float)(2.0 * CTimeMgr::GetInst()->GetDeltaTime());
			tr->SetPosition(pos);
			state->SetState(eState::Walk);
		}
		if (CKeyMgr::GetInst()->GetKeyState(KEY::UP) == KEY_STATE::PRESSED)
		{
			pos.y += (float)(2.0 * CTimeMgr::GetInst()->GetDeltaTime());
			tr->SetPosition(pos);
			state->SetState(eState::Walk);
		}
		if (CKeyMgr::GetInst()->GetKeyState(KEY::DOWN) == KEY_STATE::PRESSED)
		{
			pos.y -= (float)(2.0 * CTimeMgr::GetInst()->GetDeltaTime());
			tr->SetPosition(pos);
			state->SetState(eState::Walk);
		}

		// 방향키에서 손을 떼면 Idle 상태로
		if (CKeyMgr::GetInst()->GetKeyState(KEY::LEFT) == KEY_STATE::RELEASE)
		{
			state->SetState(eState::Idle);
		}
		if (CKeyMgr::GetInst()->GetKeyState(KEY::RIGHT) == KEY_STATE::RELEASE)
		{
			state->SetState(eState::Idle);
		}
		if (CKeyMgr::GetInst()->GetKeyState(KEY::UP) == KEY_STATE::RELEASE)
		{
			state->SetState(eState::Idle);
		}
		if (CKeyMgr::GetInst()->GetKeyState(KEY::DOWN) == KEY_STATE::RELEASE)
		{
			state->SetState(eState::Idle);
		}

		// 구르기 상태로 변환
		if (CKeyMgr::GetInst()->GetKeyState(KEY::SPACE) == KEY_STATE::TAP)
		{
			state->SetBoolStateChange(false);
			state->SetState(eState::Roll);
		}

		// 공격 상태로 변환
		if (CKeyMgr::GetInst()->GetKeyState(KEY::G) == KEY_STATE::TAP)
		{
			state->SetBoolStateChange(false);
			state->SetState(eState::Attack);
		}
	}
}

void CPlayerMoveScript::LateUpdate()
{
}
