#include "CKatamariScript.h"
#include "CGameObject.h"
#include "CTimeMgr.h"
#include <random>
#include "CColliderMgr.h"
#include "CHPScript.h"

CKatamariScript::CKatamariScript()
{
	
}

CKatamariScript::~CKatamariScript()
{
}

void CKatamariScript::Initialize()
{
	CMonsterScript::Initialize();
	GetOwner()->SetHP(100);
	SetOwnerOnMonsterScript(GetOwner());
}

void CKatamariScript::Update()
{
	CMonsterScript::Update();

	CAnimator* thisAt = this->GetOwner()->GetComponent<CAnimator>(eComponentType::Animator);
	CColliderMgr* thisCDList = this->GetOwner()->GetComponent<CColliderMgr>(eComponentType::ColliderList);
	CCollider2D* thisCDforBackground = thisCDList->GetCollider(eCollideType::Background);
	CCollider2D* thisCDforHit = thisCDList->GetCollider(eCollideType::Hit);
	CTransform* thisTr = this->GetOwner()->GetComponent<CTransform>(eComponentType::Transform);

	// animation Name
	std::wstring aniName = L"Monster_Katamari_Attack_";

	switch (GetMonsterAimSight()->GetCurSight())
	{
	case CAimSight::eSight::Down :
		aniName += L"Down_";
		break;
	case CAimSight::eSight::Right :
		aniName += L"Right_";
		break;
	case CAimSight::eSight::Left :
		aniName += L"Left_";
		break;
	case CAimSight::eSight::Up :
		aniName += L"Up_";
		break;
	}

	// 상태 변화
	eState curState = GetMonsterState()->GetCurState();
	eState prevState = GetMonsterState()->GetPrevState();
	if (curState == eState::Idle)
	{
		if (prevState == eState::Pause)
		{
			aniName += L"First";
			thisAt->PlayAnimation(aniName, false);
			GetMonsterState()->SetState(eState::Idle);
		}
		else if (thisAt->GetCurAnimation() != nullptr)
		{
			if (thisAt->GetCurAnimation()->IsComplete() == true)
			{
				GetMonsterState()->SetState(eState::Attack);
				aniName += L"Second";
				thisAt->PlayAnimation(aniName, true);
			}
			else if(thisAt->GetCurAnimation()->GetAnimationIndex() > 10)
			{ 
				if (thisCDforBackground->GetColliderData(eLayerType::Background).id != 0)
				{
					GetMonsterState()->SetState(eState::Pause);
				}
				else
				{
					Vector3 pos = thisTr->GetPosition();
					switch (GetMonsterAimSight()->GetCurSight())
					{
					case CAimSight::eSight::Down:
						pos.y -= (float)(2.0 * CTimeMgr::GetInst()->GetDeltaTime());
						thisTr->SetPosition(pos);
						break;
					case CAimSight::eSight::Right:
						pos.x += (float)(2.0 * CTimeMgr::GetInst()->GetDeltaTime());
						thisTr->SetPosition(pos);
						break;
					case CAimSight::eSight::Left:
						pos.x -= (float)(2.0 * CTimeMgr::GetInst()->GetDeltaTime());
						thisTr->SetPosition(pos);
						break;
					case CAimSight::eSight::Up:
						pos.y += (float)(2.0 * CTimeMgr::GetInst()->GetDeltaTime());
						thisTr->SetPosition(pos);
						break;
					}
				}
			}
		}
	}
	else if (curState == eState::Attack)
	{
		if (thisCDforBackground->GetColliderData(eLayerType::Background).id != 0)
		{
			GetMonsterState()->SetState(eState::Pause);
			aniName += L"Third";
			thisAt->PlayAnimation(aniName, false);
		}
		else
		{ 
			Vector3 pos = thisTr->GetPosition();
			switch (GetMonsterAimSight()->GetCurSight())
			{
			case CAimSight::eSight::Down:
				pos.y -= (float)(3.0 * CTimeMgr::GetInst()->GetDeltaTime());
				thisTr->SetPosition(pos);
				break;
			case CAimSight::eSight::Right:
				pos.x += (float)(3.0 * CTimeMgr::GetInst()->GetDeltaTime());
				thisTr->SetPosition(pos);
				break;
			case CAimSight::eSight::Left:
				pos.x -= (float)(3.0 * CTimeMgr::GetInst()->GetDeltaTime());
				thisTr->SetPosition(pos);
				break;
			case CAimSight::eSight::Up:
				pos.y += (float)(3.0 * CTimeMgr::GetInst()->GetDeltaTime());
				thisTr->SetPosition(pos);
				break;
			}
		}
	}
	else if (curState == eState::Pause)
	{
		if (thisAt->GetCurAnimation() != nullptr)
		{
			if (thisAt->GetCurAnimation()->IsComplete() == true)
			{
				ChangeSight();
				GetMonsterState()->SetState(eState::Idle);
			}
		}
	}
	else if (curState == eState::Hit)
	{
		if (prevState != eState::Hit)
		{
			// 입력된 데미지를 가지고 계산한다.

		}
	}

	
}

void CKatamariScript::LateUpdate()
{
	CColliderMgr* thisCDList = this->GetOwner()->GetComponent<CColliderMgr>(eComponentType::ColliderList);
	CCollider2D* thisCDforBackground = thisCDList->GetCollider(eCollideType::Background);
	CTransform* thisTr = this->GetOwner()->GetComponent<CTransform>(eComponentType::Transform);

	if (thisCDforBackground->GetColliderData(eLayerType::Background).id != 0)
	{
		// background Collider 로부터 떨어지기 위해 충돌 직전의 위치로 되돌린다.
		Vector3 pos = thisTr->GetPosition();
		switch (GetMonsterAimSight()->GetCurSight())
		{
		case CAimSight::eSight::Down:
			pos.y += (float)(4.0 * CTimeMgr::GetInst()->GetDeltaTime());
			thisTr->SetPosition(pos);
			break;
		case CAimSight::eSight::Right:
			pos.x -= (float)(4.0 * CTimeMgr::GetInst()->GetDeltaTime());
			thisTr->SetPosition(pos);
			break;
		case CAimSight::eSight::Left:
			pos.x += (float)(4.0 * CTimeMgr::GetInst()->GetDeltaTime());
			thisTr->SetPosition(pos);
			break;
		case CAimSight::eSight::Up:
			pos.y -= (float)(4.0 * CTimeMgr::GetInst()->GetDeltaTime());
			thisTr->SetPosition(pos);
			break;
		}
	}

	CMonsterScript::LateUpdate();
}

void CKatamariScript::ChangeSight()
{
	CTransform* thisTr = this->GetOwner()->GetComponent<CTransform>(eComponentType::Transform);
	//CCollider2D* thisCD = this->GetOwner()->GetComponent<CCollider2D>(eComponentType::Collider2D);

	std::random_device rd;
	std::mt19937 generator(rd());

	int min_value = 1;
	int max_value = 3;

	std::uniform_int_distribution<int> distribution(min_value, max_value);

	int randomInt = distribution(generator);

	// 첫번재 방향 전환
	UINT sightInt = (UINT)GetMonsterAimSight()->GetCurSight();
	if (randomInt > sightInt)
	{
		sightInt = randomInt - sightInt;
		sightInt = 4 - sightInt;
	}
	else
	{
		sightInt -= randomInt;
	}

	GetMonsterAimSight()->SetSight((CAimSight::eSight)sightInt);
}