#include "CGolemSoldierScript.h"
#include "CKeyMgr.h"

CGolemSoldierScript::CGolemSoldierScript()
{
	mNaviScript = new CNaviScript;
}

CGolemSoldierScript::~CGolemSoldierScript()
{
}

void CGolemSoldierScript::Initialize()
{
	SetOwnerOnMonsterScript(GetOwner());
	CMonsterScript::Initialize();
	GetOwner()->SetHP(100);
	
	GetMonsterState()->SetState(eState::Idle);
}

void CGolemSoldierScript::Update()
{
	eState curState = GetMonsterState()->GetCurState();
	eState prevState = GetMonsterState()->GetPrevState();

	std::wstring aniName = L"Monster_GolemSoldier_";

	CAnimator* thisAt = GetOwner()->GetComponent<CAnimator>(eComponentType::Animator);
	CTransform* thisTr = GetOwner()->GetComponent<CTransform>(eComponentType::Transform);
	Vector3 thisPos = thisTr->GetPosition();

	if (curState == eState::Idle)
	{
		if (prevState != eState::Idle)
		{
			thisTr->SetScale(Vector3(0.5f, 0.7f, 0.0f));
			aniName += L"Floating_";
			aniName += GetGolemSoldierSightStr(GetMonsterAimSight()->GetCurSight());

			thisAt->PlayAnimation(aniName, true);
			GetMonsterState()->SetState(eState::Idle);
		}

		// 우선 키 버튼으로 정상적으로 움직이는 지 확인한다.
		if (CKeyMgr::GetInst()->GetKeyState(KEY::F) == KEY_STATE::PRESSED)
		{
			GetMonsterAimSight()->SetSight(CAimSight::eSight::Left);
			thisPos.x -= (float)(2.0 * CTimeMgr::GetInst()->GetDeltaTime());
			thisTr->SetPosition(thisPos);
		}
		if (CKeyMgr::GetInst()->GetKeyState(KEY::H) == KEY_STATE::PRESSED)
		{
			GetMonsterAimSight()->SetSight(CAimSight::eSight::Right);
			thisPos.x += (float)(2.0 * CTimeMgr::GetInst()->GetDeltaTime());
			thisTr->SetPosition(thisPos);
		}
		if (CKeyMgr::GetInst()->GetKeyState(KEY::T) == KEY_STATE::PRESSED)
		{
			GetMonsterAimSight()->SetSight(CAimSight::eSight::Up);
			thisPos.y += (float)(2.0 * CTimeMgr::GetInst()->GetDeltaTime());
			thisTr->SetPosition(thisPos);
		}
		if (CKeyMgr::GetInst()->GetKeyState(KEY::G) == KEY_STATE::PRESSED)
		{
			GetMonsterAimSight()->SetSight(CAimSight::eSight::Down);
			thisPos.y -= (float)(2.0 * CTimeMgr::GetInst()->GetDeltaTime());
			thisTr->SetPosition(thisPos);
		}
		if (CKeyMgr::GetInst()->GetKeyState(KEY::Y) == KEY_STATE::PRESSED)
		{
			GetMonsterState()->SetState(eState::Attack);
		}
	}
	else if (curState == eState::Attack)
	{
		Vector3 sclae = thisTr->GetScale();
		if (prevState != eState::Attack)
		{
			
			switch (GetMonsterAimSight()->GetCurSight())
			{
			case CAimSight::eSight::Down :
				thisTr->SetPosition(Vector3(thisPos.x, thisPos.y - 0.05f, 0.0f));
				thisTr->SetScale(Vector3(sclae.x, 1.0f, 0.0f));
				break;
			case CAimSight::eSight::Left :
				thisTr->SetPosition(Vector3(thisPos.x - 0.17f, thisPos.y, 0.0f));
				thisTr->SetScale(Vector3(0.85f, 0.75f, 0.0f));
				break;
			case CAimSight::eSight::Right :
				thisTr->SetPosition(Vector3(thisPos.x + 0.17f, thisPos.y, 0.0f));
				thisTr->SetScale(Vector3(0.85f, 0.75f, 0.0f));
				break;
			case CAimSight::eSight::Up :
				thisTr->SetPosition(Vector3(thisPos.x, thisPos.y + 0.15f, 0.0f));
				thisTr->SetScale(Vector3(sclae.x, 1.0f, 0.0f));
				break;
			}
			aniName += L"Attack_";
			aniName += GetGolemSoldierSightStr(GetMonsterAimSight()->GetCurSight());
			thisAt->PlayAnimation(aniName, false);
			GetMonsterState()->SetState(eState::Attack);
		}
		else
		{
			if (thisAt->GetCurAnimation()->IsComplete() == true)
			{
				switch (GetMonsterAimSight()->GetCurSight())
				{
				case CAimSight::eSight::Down:
					thisTr->SetPosition(Vector3(thisPos.x, thisPos.y + 0.05f, 0.0f));
					break;
				case CAimSight::eSight::Left:
					thisTr->SetPosition(Vector3(thisPos.x + 0.17f, thisPos.y, 0.0f));
					break;
				case CAimSight::eSight::Right:
					thisTr->SetPosition(Vector3(thisPos.x - 0.17f, thisPos.y, 0.0f));
					break;
				case CAimSight::eSight::Up:
					thisTr->SetPosition(Vector3(thisPos.x, thisPos.y - 0.15f, 0.0f));
					break;
				}
				GetMonsterState()->SetState(eState::Idle);
			}
		}
	}
	

	if (GetMonsterAimSight()->GetCurSight() != GetMonsterAimSight()->GetPrevSight())
	{
		aniName += L"Floating_";
		aniName += GetGolemSoldierSightStr(GetMonsterAimSight()->GetCurSight());

		thisAt->PlayAnimation(aniName, true);
		GetMonsterAimSight()->SetSight(GetMonsterAimSight()->GetCurSight());
	}

	//if (curState == eState::Idle)
	//{
	//	// 어떤 원인으로 시야가 변경되면 변경된 시야에 맞게 애니메이션 재생
	//	if (GetMonsterAimSight()->GetCurSight() != GetMonsterAimSight()->GetPrevSight())
	//	{
	//		aniName += L"Floating_";
	//		aniName += GetGolemSoldierSightStr(GetMonsterAimSight()->GetCurSight());

	//		thisAt->PlayAnimation(aniName, true);
	//		GetMonsterAimSight()->SetSight(GetMonsterAimSight()->GetCurSight());
	//	}
	//	// 움직임 로직
	//	// 타겟팅할 대상이 존재 하지 않을 때의 몬스터의 움직임 로직
	//	// grid 로 갈수있는 곳을 지정하고 최단거리로 이동한다.
	//	// 중간에 플레이어를 만나 타겟팅 모드가 되면 최단거리의 대상이 플레이어로 고정된다.
	//	// 우선 키 버튼으로 정상적으로 움직이는 것을 확인해 보자
	//}
	//else if (curState == eState::Attack)
	//{
	//	if (prevState != eState::Attack)
	//	{
	//		GetMonsterState()->SetState(eState::Attack);
	//		aniName += L"Attack_";
	//		aniName += GetGolemSoldierSightStr(GetMonsterAimSight()->GetCurSight());
	//		thisAt->PlayAnimation(aniName, false);
	//	}
	//	else if (prevState == eState::Attack && thisAt->GetCurAnimation()->IsComplete() == true)
	//	{
	//		GetMonsterState()->SetState(eState::Idle);
	//	}
	//}

	CMonsterScript::Update();
}

void CGolemSoldierScript::LateUpdate()
{
	CMonsterScript::LateUpdate();
}

std::wstring CGolemSoldierScript::GetGolemSoldierSightStr(CAimSight::eSight sight)
{
	switch (sight)
	{
	case CAimSight::eSight::Down:
		return L"Down";
	case CAimSight::eSight::Right:
		return L"Right";
	case CAimSight::eSight::Left:
		return L"Left";
	case CAimSight::eSight::Up:
		return L"Up";
	}
}