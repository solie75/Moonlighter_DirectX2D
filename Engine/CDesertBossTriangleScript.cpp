#include "CDesertBossTriangleScript.h"
#include "CDesertBossScript.h"
#include "CGameObject.h"
#include "CPlayer.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CLavaBall.h"
#include "CCollider2D.h"
#include <random>

CDesertBossTriangleScript::CDesertBossTriangleScript()
{
}

CDesertBossTriangleScript::~CDesertBossTriangleScript()
{
}

void CDesertBossTriangleScript::Initialize()
{
	mtime = 0.0f;
	CScript::Initialize();
	isFired = false;
	mTriangleAttackState = eTriangleAttackState::End;
	mPartsAttackSpeed = 3.0f;
	CollideId = 0;
}

void CDesertBossTriangleScript::Update()
{
	CGameObject* parentObj = this->GetOwner()->GetParentObject(); // Square Object
	CDesertBossScript* HeadScript = parentObj->GetParentObject()->GetParentObject()->GetParentObject()->GetComponent<CDesertBossScript>(eComponentType::Script);
	CTransform* parentTr = parentObj->GetComponent<CTransform>(eComponentType::Transform);
	Vector3 parentPos = parentTr->GetPosition();
	CTransform* thisTr = this->GetOwner()->GetComponent<CTransform>(eComponentType::Transform);
	Vector3 thisPos = thisTr->GetPosition();
	CAnimator* at = this->GetOwner()->GetComponent<CAnimator>(eComponentType::Animator);
	CCollider2D* cd = this->GetOwner()->GetComponent<CCollider2D>(eComponentType::Collider2D);

	if (HeadScript->GetAttackState() == CDesertBossScript::eAttackState::Parts && mTriangleAttackState != eTriangleAttackState::Parts)
	{
		at->PlayAnimation(L"Boss3_Triangle_Light_On", false);
		mTriangleAttackState = eTriangleAttackState::Parts;

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

	if (HeadScript->GetAttackState() == CDesertBossScript::eAttackState::End && mTriangleAttackState == eTriangleAttackState::Parts)
	{
		mTriangleAttackState = eTriangleAttackState::End;
		at->PlayAnimation(L"Boss3_Triangle_Light_Off", false);
	}

	if (mTriangleAttackState == eTriangleAttackState::Parts)
	{
		Vector2 otherPos = cd->GetColliderData(eLayerType::Background).pos;
		CCollider2D::ColliderData CD;
		CD.id = 0;
		CD.type = eLayerType::End;
		CD.pos = Vector2(0.0f, 0.0f);
		if (cd->GetColliderData(eLayerType::Monster).id != 0)
		{
			CD = cd->GetColliderData(eLayerType::Monster);
		}
		if (cd->GetColliderData(eLayerType::Background).id != 0)
		{
			CD = cd->GetColliderData(eLayerType::Background);
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

		//if (CKeyMgr::GetInst()->GetKeyState(KEY::Z) == KEY_STATE::TAP)
		if (HeadScript->GetAttackState() == CDesertBossScript::eAttackState::Triangle)
		{
			at->PlayAnimation(L"Boss3_Triangle_Attack", false);
			isFired = false;
			//HeadScript->ResetAttackState();
		}

		if (at->GetCurAnimation() != nullptr && at->GetCurAnimation()->GetAnimationIndex() == 32)
		{
			std::random_device rd; // 하드웨어 기반 난수 생성기를 초기화
			std::mt19937 genX(rd()); // 난수 생성기 초기화
			std::mt19937 genY(rd());

			Vector3 WillPos = willTr->GetPosition();

			// 요소로 전달한 실수 범위 내의 랜덤한 값 생성
			std::uniform_real_distribution<float> realDistributionX(WillPos.x - 1.5f, WillPos.x + 1.5f);
			std::uniform_real_distribution<float> realDistributionY(1.0f, 1.5f);

			if (isFired == false)
			{
				for (int i = 1; i < 6; i++)
				{
					float goalPosX = realDistributionX(genX); // 랜덤으로 생성된 x 좌표
					float goalPosY = realDistributionY(genY);
					Vector2 mLavaBallAimNormal = Vector2(goalPosX - thisPos.x, WillPos.y + goalPosY - thisPos.y); // 최종 목적지는 (goalPosx, willPos.y + 1.0f)
					mLavaBallAimNormal.Normalize();
					CLavaBall* LavaBall = new CLavaBall;
					ownScene->AddGameObject(eLayerType::Projectile, LavaBall, L"Lava_Ball", Vector3(thisPos.x, thisPos.y, (0.001f * i)), Vector3(0.2f, 0.2f, 0.0f)
						, true, L"Mesh", L"mt_atlas_Lava_Ball", true);
					LavaBall->SetAimNormal(mLavaBallAimNormal);
					LavaBall->SetGoalPos(Vector2(goalPosX, WillPos.y + goalPosY));
					CAnimator* LavaBallAT = LavaBall->GetComponent<CAnimator>(eComponentType::Animator);
					LavaBallAT->PlayAnimation(L"Lava_Ball", true);
				}
				isFired = true;
			}
			// this->pos 에서 WillPos 의 y 의 1 위로 mAimNormal 계산
		}
	}
	
	CScript::Update();
}

void CDesertBossTriangleScript::LateUpdate()
{
	CScript::LateUpdate();
}

void CDesertBossTriangleScript::Render()
{
	CScript::Render();
}
