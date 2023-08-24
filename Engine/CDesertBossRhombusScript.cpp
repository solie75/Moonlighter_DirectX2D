#include "CDesertBossRhombusScript.h"
#include "CGameObject.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CFireBall.h"
#include "CCollider2D.h"
#include "CDesertBossScript.h"
#include <random>

CDesertBossRhombusScript::CDesertBossRhombusScript()
	: diff(0.5f)
{
}

CDesertBossRhombusScript::~CDesertBossRhombusScript()
{
}

void CDesertBossRhombusScript::Initialize()
{
	CScript::Initialize();
	fireballInterval = 0.0f;
	fireCount = 0;
	CAnimator* at = this->GetOwner()->GetComponent<CAnimator>(eComponentType::Animator);
	mRhombusAttackState = eRhombusAttackState::End;
	mPartsAttackSpeed = 3.0f;
	CollideId = 0;
}

void CDesertBossRhombusScript::Update()
{
	fireballInterval += CTimeMgr::GetInst()->GetDeltaTime();

	CGameObject* parentObj = this->GetOwner()->GetParentObject();
	CTransform* parentTr = parentObj->GetComponent<CTransform>(eComponentType::Transform);
	Vector3 parentPos = parentTr->GetPosition();
	CTransform* thisTr = this->GetOwner()->GetComponent<CTransform>(eComponentType::Transform);
	Vector3 thisPos = thisTr->GetPosition();
	CAnimator* at = this->GetOwner()->GetComponent<CAnimator>(eComponentType::Animator);
	CCollider2D* cd = this->GetOwner()->GetComponent<CCollider2D>(eComponentType::Collider2D);

	CDesertBossScript* HeadScript = parentObj->GetParentObject()->GetComponent<CDesertBossScript>(eComponentType::Script);

	if (HeadScript->GetAttackState() == CDesertBossScript::eAttackState::Parts && mRhombusAttackState != eRhombusAttackState::Parts)
	{
		at->PlayAnimation(L"Boss3_Rhombus_Light_On", false);
		mRhombusAttackState = eRhombusAttackState::Parts;

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

	if (HeadScript->GetAttackState() == CDesertBossScript::eAttackState::End && mRhombusAttackState == eRhombusAttackState::Parts)
	{
		mRhombusAttackState = eRhombusAttackState::End;
	}

	if (mRhombusAttackState == eRhombusAttackState::Parts)
	{
		// 벽과 충돌했을 때 mAimNormal 변경
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
			thisTr->SetPosition(Vector3(thisPos.x + (mAimNormal.x * 0.05f), thisPos.y + (mAimNormal.y * 0.05f), 0.0f));
			mtime = 0.0f;
		}
	}
	else
	{
		// Direction from this to parent Object
		Vector3 direct = Vector3(parentPos.x - thisPos.x, parentPos.y - thisPos.y, 0.0f);
		direct.Normalize();

		// moving distance in 1fps
		float moveDist = (float)(2.0 * CTimeMgr::GetInst()->GetDeltaTime());
		float dist = Vector3::Distance(Vector3(parentPos.x, parentPos.y, 0.0f), Vector3(thisPos.x, thisPos.y, 0.0f));
		if (dist > 0.9f)
		{
			Vector3 diff = Vector3(direct.x * moveDist, direct.y * moveDist, 0.0f);
			thisTr->SetPosition(Vector3(thisPos.x + diff.x, thisPos.y + diff.y, thisPos.z));
		}


		CDesertBossScript* HeadScript = parentObj->GetParentObject()->GetComponent<CDesertBossScript>(eComponentType::Script); // 부모의 부모 오브젝트 == Head

		if (HeadScript->GetAttackState() == CDesertBossScript::eAttackState::Rhombus)
		{
			ChangeRhombusAttackState(eRhombusAttackState::Enter);
			at->PlayAnimation(L"Boss3_Rhombus_Attack_Enter", false);
			HeadScript->ResetAttackState();
		}

		if (mRhombusAttackState == eRhombusAttackState::Enter && at->GetCurAnimation()->IsComplete())
		{
			at->PlayAnimation(L"Boss3_Rhombus_Attack_Stay", true);
			ChangeRhombusAttackState(eRhombusAttackState::Stay);
		}

		if (mRhombusAttackState == eRhombusAttackState::Stay)
		{
			if (fireCount < 40 && fireballInterval > 0.1f)
			{
				for (int i = 0; i < 3; i++) // 이 사이클이 한번 발사이다. 이것을 50번 해야한다.
				{
					Vector3 FireBallPos = thisPos;
					double pi = 3.14159265358979323846;
					double angle = (120.f) * i + angleNum;
					FireBallPos.x += diff * std::cos(angle * pi / 180.0);
					FireBallPos.y += diff * sin(angle * pi / 180.0);
					FireBallPos.z = 0.000010001 * (i + 1);
					CFireBall* fb = new CFireBall; //(i, BossHeadPos) 여기에서 회전행렬 소스 전달 monster 면 화면에 나온다.
					fb->SetSpeed(10.0f);
					ownScene->AddGameObject(eLayerType::Projectile, fb, L"Fire_Ball", FireBallPos, Vector3(0.2f, 0.2f, 0.0f),
						true, L"Mesh", L"mt_atlas_Fire_Ball", true);
					CCollider2D* cd = fb->AddComponent<CCollider2D>();
					cd->SetSize(Vector2(0.5f, 0.5f));
					CAnimator* fireballAT = fb->GetComponent<CAnimator>(eComponentType::Animator);
					fireballAT->PlayAnimation(L"Fire_Ball", true);
					CTransform* fireballTr = fb->GetComponent<CTransform>(eComponentType::Transform);
					fireballTr->SetRotation(Vector3(0.0f, 0.0f, (2.0f * i) + (0.0175 * angleNum)));
					Vector3 FireBallDirection = FireBallPos - thisPos;
					FireBallDirection.Normalize();
					fb->SetDirection(FireBallDirection);
				}
				angleNum += 5.f;
				fireCount++;
				fireballInterval = 0.0f;
			}
			if (fireCount == 29)
			{
				ChangeRhombusAttackState(eRhombusAttackState::Exit);
				fireCount = 0;
			}
		}

		if (mRhombusAttackState == eRhombusAttackState::Exit)
		{
			at->PlayAnimation(L"Boss3_Rhombus_Attack_Exit", false);
			ChangeRhombusAttackState(eRhombusAttackState::End);
		}
	}
	
	CScript::Update();
}

void CDesertBossRhombusScript::LateUpdate()
{
	CScript::LateUpdate();
}

void CDesertBossRhombusScript::Render()
{
	CScript::Render();
}
