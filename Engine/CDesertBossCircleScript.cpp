#include "CDesertBossCircleScript.h"
#include "CGameObject.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CCollider2D.h"
#include "CColliderMgr.h"
#include "CDesertBossScript.h"
#include <random>

CDesertBossCircleScript::CDesertBossCircleScript()
	: diff(0.3f)
{
}

CDesertBossCircleScript::~CDesertBossCircleScript()
{
}

void CDesertBossCircleScript::Initialize()
{
	CScript::Initialize();
	firedNum = 0;
	mCircleAttackState = eCircleAttackState::End;
	mtime = 0.0f;
	mPartsAttackSpeed = 3.0f;
	mState.SetState(eState::End);
	CollideId = 0;
}

void CDesertBossCircleScript::Update()
{
	CGameObject* parentObj = this->GetOwner()->GetParentObject();
	CTransform* parentTr = parentObj->GetComponent<CTransform>(eComponentType::Transform);
	Vector3 parentPos = parentTr->GetPosition();
	CTransform* thisTr = this->GetOwner()->GetComponent<CTransform>(eComponentType::Transform);
	Vector3 thisPos = thisTr->GetPosition();
	CAnimator* at = this->GetOwner()->GetComponent<CAnimator>(eComponentType::Animator);
	CColliderMgr* CdList = this->GetOwner()->GetComponent<CColliderMgr>(eComponentType::ColliderList);
	CCollider2D * CDforBackground = CdList->GetCollider(eCollideType::Background);

	CDesertBossScript* HeadScript = parentObj->GetComponent<CDesertBossScript>(eComponentType::Script);

	// Parts Attack Enter
	if (HeadScript->GetAttackState() == CDesertBossScript::eAttackState::Parts && mCircleAttackState != eCircleAttackState::Parts)
	{
		at->PlayAnimation(L"Boss3_Circle_Light_On", false);
		mCircleAttackState = eCircleAttackState::Parts;

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

	if (HeadScript->GetAttackState() == CDesertBossScript::eAttackState::End && mCircleAttackState == eCircleAttackState::Parts)
	{
		mCircleAttackState = eCircleAttackState::End;
		at->PlayAnimation(L"Boss3_Circle_Light_Off", false);
	}

	// Parts Attack Stay
	if (mCircleAttackState == eCircleAttackState::Parts)
	{
		// 벽과 충돌했을 때 mAimNormal 변경
		Vector2 otherPos = CDforBackground->GetColliderData(eLayerType::Background).pos;
		CCollider2D::ColliderData CdData;
		CdData.id = 0;
		CdData.type = eLayerType::End;
		CdData.pos = Vector2(0.0f, 0.0f);

		if (CDforBackground->GetColliderData(eLayerType::Monster).id != 0)
		{
			CdData = CDforBackground->GetColliderData(eLayerType::Monster);
		}
		if (CDforBackground->GetColliderData(eLayerType::Background).id != 0)
		{
			CdData = CDforBackground->GetColliderData(eLayerType::Background);
		}
		
		if (CdData.type == eLayerType::Monster) // 충돌체가 배경 
		{
			if (CdData.id != CollideId)
			{
				mAimNormal.x = thisPos.x - CdData.pos.x;
				mAimNormal.y = thisPos.y - CdData.pos.y;
				CollideId = CdData.id;

				mAimNormal.Normalize();
			}
			
		}
		if (CdData.type == eLayerType::Background) // 충돌체가 배경 벽일 때
		{
			if (CdData.id != CollideId)
			{
				if (otherPos.x == 0) // 충돌한 벽 충돌체가 Up 과 Down 일 때
				{
					mAimNormal.y *= -1;
					CollideId = CdData.id;
					mAimNormal.Normalize();
				}
				if (otherPos.y == 0)
				{
					mAimNormal.x *= -1;
					CollideId = CdData.id;
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
	else // eCircleAttackState != Part
	{
		// Direction from this to parent Object
		Vector3 direct = Vector3(parentPos.x - thisPos.x, parentPos.y - thisPos.y, 0.0f);
		direct.Normalize();

		// moving distance in 1fps
		mtime += CTimeMgr::GetInst()->GetDeltaTime();
		float moveDist = (float)(2.0 * CTimeMgr::GetInst()->GetDeltaTime());
		float dist = Vector3::Distance(Vector3(parentPos.x, parentPos.y, 0.0f), Vector3(thisPos.x, thisPos.y, 0.0f)); // Parts 전에는 정상적으로 작동하다가 Parts 후에 이상하게 작동한다.
		if (dist > 0.9f)
		{
			Vector3 diff = Vector3(direct.x * moveDist, direct.y * moveDist, 0.0f);
			thisTr->SetPosition(Vector3(thisPos.x + diff.x, thisPos.y + diff.y, thisPos.z));
		}

		if (HeadScript->GetAttackState() == CDesertBossScript::eAttackState::Circle)
		{
			ChangeCirCleAttackState(eCircleAttackState::Enter);
			at->PlayAnimation(L"Boss3_Circle_Attack_Enter", false);
			//HeadScript->ResetAttackState();
		}

		if (mCircleAttackState == eCircleAttackState::Enter && at->GetCurAnimation()->IsComplete())
		{
			at->PlayAnimation(L"Boss3_Circle_Attack_Stay", true);
			ChangeCirCleAttackState(eCircleAttackState::Stay);
		}

		if (firedNum == 2)
		{
			ChangeCirCleAttackState(eCircleAttackState::Exit);
			at->PlayAnimation(L"Boss3_Circle_Attack_Exit", false);
			firedNum = 0;
		}

		if (mCircleAttackState == eCircleAttackState::Stay && mtime > 0.7f) // 처음에 한번
		{
			for (int i = 0; i < 50; i++)
			{
				Vector3 FireBallPos = thisPos;
				double pi = 3.14159265358979323846;
				double angle = 7.2f * i;
				FireBallPos.x += diff * std::cos(angle * pi / 180.0);
				FireBallPos.y += diff * sin(angle * pi / 180.0);
				FireBallPos.z = 0.00001 * (i + 1);
				CFireBall* fb = new CFireBall; //(i, BossHeadPos) 여기에서 회전행렬 소스 전달 monster 면 화면에 나온다.
				ownScene->AddGameObject(eLayerType::Projectile, fb, L"Fire_Ball", FireBallPos, Vector3(0.2f, 0.2f, 0.0f),
					true, L"Mesh", L"mt_atlas_Fire_Ball", true);
				/*CCollider2D* cd = fb->AddComponent<CCollider2D>(); 
				cd->SetSize(Vector2(0.5f, 0.5f));*/
				CAnimator* fireball = fb->GetComponent<CAnimator>(eComponentType::Animator);
				fireball->PlayAnimation(L"Fire_Ball", true);
				CTransform* fireballTr = fb->GetComponent<CTransform>(eComponentType::Transform);
				fireballTr->SetRotation(Vector3(0.0f, 0.0f, 0.125f * i));
				Vector3 FireBallDirection = FireBallPos - thisPos;
				FireBallDirection.Normalize();
				fb->SetDirection(FireBallDirection);
			}
			firedNum++;
			mtime = 0.0f;// 한번 쏘고 0으로 초기화 한 뒤 또 솔 수 있다.
		}
	}

	CScript::Update();
}

void CDesertBossCircleScript::LateUpdate()
{
	CScript::LateUpdate();
}

void CDesertBossCircleScript::Render()
{
	CScript::Render();
}
