#include "CDesertBossRhombusScript.h"
#include "CGameObject.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CFireBall.h"
#include "CCollider2D.h"
#include "CDesertBossScript.h"

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

	// Direction from this to parent Object
	Vector3 direct = Vector3(parentPos.x - thisPos.x, parentPos.y - thisPos.y, 0.0f);
	direct.Normalize();

	// moving distance in 1fps
	float moveDist = (float)(2.0 * CTimeMgr::GetInst()->GetDeltaTime());
	float dist = Vector3::Distance(parentPos, thisPos);
	if (dist > 0.9f)
	{
		Vector3 diff = Vector3(direct.x * moveDist, direct.y * moveDist, 0.0f);
		thisTr->SetPosition(Vector3(thisPos.x + diff.x, thisPos.y + diff.y, thisPos.z));
	}
	
	
	CDesertBossScript* HeadScript = parentObj->GetParentObject()->GetComponent<CDesertBossScript>(eComponentType::Script); // �θ��� �θ� ������Ʈ == Head

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
			for (int i = 0; i < 3; i++) // �� ����Ŭ�� �ѹ� �߻��̴�. �̰��� 50�� �ؾ��Ѵ�.
			{
				Vector3 FireBallPos = thisPos;
				double pi = 3.14159265358979323846;
				double angle = (120.f) * i + angleNum;
				FireBallPos.x += diff * std::cos(angle * pi / 180.0);
				FireBallPos.y += diff * sin(angle * pi / 180.0);
				FireBallPos.z = 0.000010001 * (i + 1);
				CFireBall* fb = new CFireBall; //(i, BossHeadPos) ���⿡�� ȸ����� �ҽ� ���� monster �� ȭ�鿡 ���´�.
				fb->SetSpeed(10.0f);
				ownScene->AddGameObject(eLayerType::Projectile, fb, L"Fire_Ball", FireBallPos, Vector3(0.2f, 0.2f, 0.0f),
					true, L"Mesh", L"mt_atlas_Fire_Ball", true);
				CCollider2D* cd = fb->AddComponent<CCollider2D>();
				cd->SetSize(Vector2(0.5f, 0.5f));
				CAnimator* fireball = fb->GetComponent<CAnimator>(eComponentType::Animator);
				fireball->PlayAnimation(L"Fire_Ball", true);
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
