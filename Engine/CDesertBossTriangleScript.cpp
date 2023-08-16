#include "CDesertBossTriangleScript.h"
#include "CDesertBossScript.h"
#include "CGameObject.h"
#include "CPlayer.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CLavaBall.h"
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

	// Direction from this to parent Object
	Vector3 direct = Vector3(parentPos.x - thisPos.x, parentPos.y - thisPos.y, 0.0f);
	direct.Normalize();

	// moving distance in 1fps
	mtime += CTimeMgr::GetInst()->GetDeltaTime();
	float moveDist = (float)(2.0 * CTimeMgr::GetInst()->GetDeltaTime());
	float dist = Vector3::Distance(parentPos, thisPos);
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
		HeadScript->ResetAttackState();
	}

	if(at->GetCurAnimation() != nullptr && at->GetCurAnimation()->GetAnimationIndex() == 32)
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
