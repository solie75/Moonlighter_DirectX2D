#include "CDesertBossSquareScript.h"
#include "CGameObject.h"
#include "CTimeMgr.h"
#include "CDesertBossScript.h"
#include "CAnimator.h"
#include "CCollider2D.h"
#include "CColliderMgr.h"
#include <random>

CDesertBossSquareScript::CDesertBossSquareScript()
{
}

CDesertBossSquareScript::~CDesertBossSquareScript()
{
}

void CDesertBossSquareScript::Initialize()
{
	mtime = 0.0f;
	CScript::Initialize();
	mSquareAttackState = eSquareAttackState::End;
	mPartsAttackSpeed = 3.0f;
	CollideId = 0;
}

void CDesertBossSquareScript::Update()
{
	CGameObject* parentObj = this->GetOwner()->GetParentObject();
	CTransform* parentTr = parentObj->GetComponent<CTransform>(eComponentType::Transform);
	Vector3 parentPos = parentTr->GetPosition();
	CTransform* thisTr = this->GetOwner()->GetComponent<CTransform>(eComponentType::Transform);
	Vector3 thisPos = thisTr->GetPosition();
	CAnimator* at = this->GetOwner()->GetComponent<CAnimator>(eComponentType::Animator);
	CColliderMgr* CdList = this->GetOwner()->GetComponent<CColliderMgr>(eComponentType::ColliderList);
	CCollider2D* CDforBackground = CdList->GetCollider(eCollideType::Background);

	//CCollider2D* cd = this->GetOwner()->GetComponent<CCollider2D>(eComponentType::Collider2D);

	CDesertBossScript* HeadScript = parentObj->GetParentObject()->GetParentObject()->GetComponent<CDesertBossScript>(eComponentType::Script);

	if (HeadScript->GetAttackState() == CDesertBossScript::eAttackState::Parts && mSquareAttackState != eSquareAttackState::Parts)
	{
		CTransform* tr = GetOwner()->GetComponent<CTransform>(eComponentType::Transform);
		Vector3 v3 = tr->GetPosition();

		at->PlayAnimation(L"Boss3_Square_Light_On", false);
		mSquareAttackState = eSquareAttackState::Parts;

		std::random_device rd; // 하드웨어 기반 난수 생성기를 초기화
		std::mt19937 genX(rd()); // 난수 생성기 초기화
		std::mt19937 genY(rd());

		// 요소로 전달한 실수 범위 내의 랜덤한 값 생성
		std::uniform_real_distribution<float> realDistributionX(-1.0f, 1.0f);
		std::uniform_real_distribution<float> realDistributionY(-1.0f, 1.0f);

		float goalPosX = realDistributionX(genX); // 랜덤으로 생성된 x 좌표
		float goalPosY = realDistributionY(genY);

		mAimNormal.x = goalPosX;
		mAimNormal.y = goalPosY;

		mAimNormal.Normalize();
	}

	if (HeadScript->GetAttackState() == CDesertBossScript::eAttackState::End && mSquareAttackState == eSquareAttackState::Parts)
	{
		mSquareAttackState = eSquareAttackState::End;
		at->PlayAnimation(L"Boss3_Square_Light_Off", false);
	}

	if (mSquareAttackState == eSquareAttackState::Parts)
	{
		Vector2 otherPos = CDforBackground->GetColliderData(eLayerType::Background).pos;
		CCollider2D::ColliderData CD;
		CD.id = 0;
		CD.type = eLayerType::End;
		CD.pos = Vector2(0.0f, 0.0f);
		if (CDforBackground->GetColliderData(eLayerType::Monster).id != 0)
		{
			CD = CDforBackground->GetColliderData(eLayerType::Monster);
		}
		if (CDforBackground->GetColliderData(eLayerType::Background).id != 0)
		{
			CD = CDforBackground->GetColliderData(eLayerType::Background);
		}


		if (CD.id != CollideId && CD.id != 0)
		{
			if (CD.type == eLayerType::Monster) // 충돌체가 배경 
			{
				mAimNormal.x = thisPos.x - CD.pos.x;
				mAimNormal.y = thisPos.y - CD.pos.y;
				CollideId = CD.id;
				mAimNormal.Normalize();
			}
			if (CD.type == eLayerType::Background) // 충돌체가 배경 벽일 때
			{
				if (otherPos.x == 0) // 충돌한 벽 충돌체가 Up 과 Down 일 때
				{
					mAimNormal.y *= -1;
					CollideId = CD.id;
					mAimNormal.Normalize();
				}
				if (otherPos.y == 0)
				{
					mAimNormal.x *= -1;
					CollideId = CD.id;
					mAimNormal.Normalize();
				}
			}
		}

		mtime += CTimeMgr::GetInst()->GetDeltaTime();
		if (mtime > 0.01f)
		{
			thisTr->SetPosition(Vector3(thisPos.x + (mAimNormal.x * 0.05f), thisPos.y + (mAimNormal.y * 0.05f), thisPos.z));
			mtime = 0.0f;
		}
	}
	else
	{
		// Direction from this to parent Object
		Vector3 direct = Vector3(parentPos.x - thisPos.x, parentPos.y - thisPos.y, 0.0f);
		direct.Normalize();

		// moving distance in 1fps
		mtime += CTimeMgr::GetInst()->GetDeltaTime();
		float moveDist = (float)(2.0 * CTimeMgr::GetInst()->GetDeltaTime());
		float dist = Vector3::Distance(Vector3(parentPos.x, parentPos.y, 0.0f), Vector3(thisPos.x, thisPos.y, 0.0f));
		if (dist > 0.9f)
		{
			Vector3 diff = Vector3(direct.x * moveDist, direct.y * moveDist, 0.0f);
			thisTr->SetPosition(Vector3(thisPos.x + diff.x, thisPos.y + diff.y, thisPos.z));
		}
	}

	CScript::Update();
}

void CDesertBossSquareScript::LateUpdate()
{
	CScript::LateUpdate();
}

void CDesertBossSquareScript::Render()
{
	CScript::Render();
}
