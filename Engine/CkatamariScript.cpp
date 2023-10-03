#include "CKatamariScript.h"
#include "CGameObject.h"
#include "CTimeMgr.h"
#include <random>
#include "CColliderMgr.h"
//#include "CCollider2D.h"

CKatamariScript::CKatamariScript()
{
	mAimSight = new CAimSight;
	mState = new CState;
	mState->SetState(eState::End);
	mState->SetState(eState::Pause);
	mAimSight->SetSight(CAimSight::eSight::Down);
}

CKatamariScript::~CKatamariScript()
{
}

void CKatamariScript::Initialize()
{
	CScript::Initialize();
}

void CKatamariScript::Update()
{
	CAnimator* thisAt = this->GetOwner()->GetComponent<CAnimator>(eComponentType::Animator);
	CColliderMgr* thisCDList = this->GetOwner()->GetComponent<CColliderMgr>(eComponentType::ColliderList);
	CCollider2D* thisCDforBackground = thisCDList->GetCollider(eCollideType::Background);
	CCollider2D* thisCDforHit = thisCDList->GetCollider(eCollideType::Hit);
	CTransform* thisTr = this->GetOwner()->GetComponent<CTransform>(eComponentType::Transform);

	mPosBeforeCollide = thisTr->GetPosition();

	if (thisCDforBackground->GetColliderData(eLayerType::Background).id != 0)
	{
		// background Collider �κ��� �������� ���� �浹 ������ ��ġ�� �ǵ�����.
		Vector3 pos = thisTr->GetPosition();
		switch (mAimSight->GetSight())
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

	// animation Name
	std::wstring aniName = L"Monster_Katamari_Attack_";

	switch (mAimSight->GetSight())
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

	// ���� ��ȭ
	if (mState->GetCurState() == eState::Idle)
	{
		if (mState->GetPrevState() == eState::Pause)
		{
			aniName += L"First";
			thisAt->PlayAnimation(aniName, false);
			mState->SetState(eState::Idle);
		}
		else if (thisAt->GetCurAnimation() != nullptr)
		{
			if (thisAt->GetCurAnimation()->IsComplete() == true)
			{
				mState->SetState(eState::Attack);
				aniName += L"Second";
				thisAt->PlayAnimation(aniName, true);
			}
			else if(thisAt->GetCurAnimation()->GetAnimationIndex() > 10)
			{ 
				if (thisCDforBackground->GetColliderData(eLayerType::Background).id != 0)
				{
					mState->SetState(eState::Pause);
				}
				else
				{
					Vector3 pos = thisTr->GetPosition();
					switch (mAimSight->GetSight())
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
	else if (mState->GetCurState() == eState::Attack)
	{
		if (thisCDforBackground->GetColliderData(eLayerType::Background).id != 0)
		{
			mState->SetState(eState::Pause);
			aniName += L"Third";
			thisAt->PlayAnimation(aniName, false);
		}
		else
		{ 
			Vector3 pos = thisTr->GetPosition();
			switch (mAimSight->GetSight())
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
	else if (mState->GetCurState() == eState::Pause)
	{
		if (thisAt->GetCurAnimation() != nullptr)
		{
			if (thisAt->GetCurAnimation()->IsComplete() == true)
			{
				ChangeSight();
				mState->SetState(eState::Idle);
			}
		}
	}
}

void CKatamariScript::LateUpdate()
{
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

	// ù���� ���� ��ȯ
	UINT sightInt = (UINT)mAimSight->GetSight();
	if (randomInt > sightInt)
	{
		sightInt = randomInt - sightInt;
		sightInt = 4 - sightInt;
	}
	else
	{
		sightInt -= randomInt;
	}

	mAimSight->SetSight((CAimSight::eSight)sightInt);
}