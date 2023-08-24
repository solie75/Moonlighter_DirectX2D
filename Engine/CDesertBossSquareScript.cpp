#include "CDesertBossSquareScript.h"
#include "CGameObject.h"
#include "CTimeMgr.h"
#include "CDesertBossScript.h"
#include "CAnimator.h"
#include "CCollider2D.h"
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
	CCollider2D* cd = this->GetOwner()->GetComponent<CCollider2D>(eComponentType::Collider2D);

	CDesertBossScript* HeadScript = parentObj->GetParentObject()->GetParentObject()->GetComponent<CDesertBossScript>(eComponentType::Script);

	if (HeadScript->GetAttackState() == CDesertBossScript::eAttackState::Parts && mSquareAttackState != eSquareAttackState::Parts)
	{
		at->PlayAnimation(L"Boss3_Square_Light_On", false);
		mSquareAttackState = eSquareAttackState::Parts;

		std::random_device rd; // �ϵ���� ��� ���� �����⸦ �ʱ�ȭ
		std::mt19937 genX(rd()); // ���� ������ �ʱ�ȭ
		std::mt19937 genY(rd());

		// ��ҷ� ������ �Ǽ� ���� ���� ������ �� ����
		std::uniform_real_distribution<float> realDistributionX(-1.0f, 1.0f);
		std::uniform_real_distribution<float> realDistributionY(-1.0f, 1.0f);

		float goalPosX = realDistributionX(genX); // �������� ������ x ��ǥ
		float goalPosY = realDistributionY(genY);

		mAimNormal.x = goalPosX;
		mAimNormal.y = goalPosY;

		mAimNormal.Normalize();
	}


	if (mSquareAttackState == eSquareAttackState::Parts)
	{
		Vector2 otherPos = cd->GetColliderData(eLayerType::Background).pos;
		UINT id = cd->GetColliderData(eLayerType::Background).id;

		if (id != CollideId && id != 0)
		{

			if (otherPos.x == 0) // �浹�� �� �浹ü�� Up �� Down �� ��
			{
				mAimNormal.y *= -1;
				CollideId = id;
			}
			else
			{
				mAimNormal.x *= -1;
				CollideId = id;
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
		mtime += CTimeMgr::GetInst()->GetDeltaTime();
		float moveDist = (float)(2.0 * CTimeMgr::GetInst()->GetDeltaTime());
		float dist = Vector3::Distance(parentPos, thisPos);
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
