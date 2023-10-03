#include "CDesertBossRhombusScript.h"
#include "CGameObject.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CFireBall.h"
#include "CCollider2D.h"
#include "CColliderMgr.h"
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
	CColliderMgr* CDList = this->GetOwner()->GetComponent<CColliderMgr>(eComponentType::ColliderList);
	CCollider2D* CDforBackground = CDList->GetCollider(eCollideType::Background);


	CDesertBossScript* HeadScript = parentObj->GetParentObject()->GetComponent<CDesertBossScript>(eComponentType::Script);

	if (HeadScript->GetAttackState() == CDesertBossScript::eAttackState::Parts && mRhombusAttackState != eRhombusAttackState::Parts)
	{
		at->PlayAnimation(L"Boss3_Rhombus_Light_On", false);
		mRhombusAttackState = eRhombusAttackState::Parts;

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

	if (HeadScript->GetAttackState() == CDesertBossScript::eAttackState::End && mRhombusAttackState == eRhombusAttackState::Parts)
	{
		mRhombusAttackState = eRhombusAttackState::End;
		at->PlayAnimation(L"Boss3_Rhombus_Light_Off", false);
	}

	if (mRhombusAttackState == eRhombusAttackState::Parts)
	{
		CTransform* tr = GetOwner()->GetComponent<CTransform>(eComponentType::Transform);
		Vector3 v3 = tr->GetPosition();

		// ���� �浹���� �� mAimNormal ����
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
			if (CD.type == eLayerType::Monster) // �浹ü�� ��� 
			{
				mAimNormal.x = thisPos.x - CD.pos.x;
				mAimNormal.y = thisPos.y - CD.pos.y;
				CollideId = CD.id;
				mAimNormal.Normalize();
			}
			if (CD.type == eLayerType::Background) // �浹ü�� ��� ���� ��
			{
				if (otherPos.x == 0) // �浹�� �� �浹ü�� Up �� Down �� ��
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
		float moveDist = (float)(2.0 * CTimeMgr::GetInst()->GetDeltaTime());
		float dist = Vector3::Distance(Vector3(parentPos.x, parentPos.y, 0.0f), Vector3(thisPos.x, thisPos.y, 0.0f));
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
			//HeadScript->ResetAttackState();
		}

		if (mRhombusAttackState == eRhombusAttackState::Enter && at->GetCurAnimation()->IsComplete())
		{
			at->PlayAnimation(L"Boss3_Rhombus_Attack_Stay", true);
			ChangeRhombusAttackState(eRhombusAttackState::Stay);
		}

		if (mRhombusAttackState == eRhombusAttackState::Stay)
		{
			if (fireCount < 40 && fireballInterval > 0.1f) // fireballInterval �� �߻� ����
			{
				for (int i = 0; i < 3; i++)
				{
					// �ѹ� �߻� ���� �߻�ü 3���� �߻��ϴ� �ڵ��Դϴ�.

					// �߻�ü�� �߻� ���� ��ġ�� ���մϴ�.
					Vector3 FireBallPos = thisPos;
					double pi = 3.14159265358979323846;
					double angle = (120.f) * i + angleNum; // �� ���� �߻� ������ ���� �Դϴ�. angleNum �� �߻� ������ �޶����� ���� �Դϴ�.
					FireBallPos.x += diff * std::cos(angle * pi / 180.0); // diff �� �߻���� �߻�ü�� ������ ���� ���Դϴ�.
					FireBallPos.y += diff * std::sin(angle * pi / 180.0);
					FireBallPos.z = 0.000010001 * (i + 1);

					// ����ü ����
					CFireBall* fb = new CFireBall;
					fb->SetSpeed(1.0f);
					ownScene->AddGameObject(eLayerType::Projectile, fb, L"Fire_Ball", FireBallPos, Vector3(0.2f, 0.2f, 0.0f),
						true, L"Mesh", L"mt_atlas_Fire_Ball", true);
					//CCollider2D* cd = fb->AddComponent<CCollider2D>();
					//cd->SetSize(Vector2(0.5f, 0.5f));
					CAnimator* fireballAT = fb->GetComponent<CAnimator>(eComponentType::Animator);
					fireballAT->PlayAnimation(L"Fire_Ball", true);
					CTransform* fireballTr = fb->GetComponent<CTransform>(eComponentType::Transform);

					// ����ü�� ���� ������ ���� �̹��� ȸ�� ��ȭ
					fireballTr->SetRotation(Vector3(0.0f, 0.0f, (2.0f * i) + (0.0175 * angleNum)));

					// ����ü�� ���ư����� ����
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
