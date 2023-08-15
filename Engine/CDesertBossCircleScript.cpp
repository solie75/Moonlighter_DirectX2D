#include "CDesertBossCircleScript.h"
#include "CGameObject.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CCollider2D.h"

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
}

void CDesertBossCircleScript::Update()
{
	CGameObject* parentObj = this->GetOwner()->GetParentObject();
	CTransform* parentTr = parentObj->GetComponent<CTransform>(eComponentType::Transform);
	Vector3 parentPos = parentTr->GetPosition();
	CTransform* thisTr = this->GetOwner()->GetComponent<CTransform>(eComponentType::Transform);
	Vector3 thisPos = thisTr->GetPosition();

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
	if (CKeyMgr::GetInst()->GetKeyState(KEY::Z) == KEY_STATE::TAP)
	{
		for (int i = 0; i < 50; i++)
		{
			Vector3 FireBallPos = thisPos;
			double pi = 3.14159265358979323846;
			double angle = 7.2f * i;
			FireBallPos.x += diff * std::cos(angle * pi / 180.0);
			FireBallPos.y += diff * sin(angle * pi / 180.0);
			FireBallPos.z = 0.00001 * (i + 1);
			CFireBall* fb = new CFireBall; //(i, BossHeadPos) ���⿡�� ȸ����� �ҽ� ���� monster �� ȭ�鿡 ���´�.
			ownScene->AddGameObject(eLayerType::Projectile, fb, L"Fire_Ball", FireBallPos, Vector3(0.2f, 0.2f, 0.0f),
				true, L"Mesh", L"mt_atlas_Fire_Ball", true);
			CCollider2D* cd = fb->AddComponent<CCollider2D>();
			cd->SetSize(Vector2(0.5f, 0.5f));
			CAnimator* fireball = fb->GetComponent<CAnimator>(eComponentType::Animator);
			fireball->PlayAnimation(L"Fire_Ball", true);
			CTransform* fireballTr = fb->GetComponent<CTransform>(eComponentType::Transform);
			fireballTr->SetRotation(Vector3(0.0f, 0.0f, 0.125f * i));
			Vector3 FireBallDirection = FireBallPos - thisPos;
			FireBallDirection.Normalize();
			fb->SetDirection(FireBallDirection);
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
