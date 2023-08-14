#include "CDesertBossScript.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CTransform.h"
#include "CCollider2D.h"
#include "CMonster.h"

CDesertBossScript::CDesertBossScript()

{
}

CDesertBossScript::~CDesertBossScript()
{
}

void CDesertBossScript::Initialize()
{
	CScript::Initialize();
	mAimAngle = 180.f;
}

void CDesertBossScript::Update()
{
	// Head 가 바라보는 뱡향
	Vector2 direction = Vector2(cos(mAimAngle), sin(mAimAngle));
	direction.Normalize();

	CTransform* tr = this->GetOwner()->GetComponent<CTransform>(eComponentType::Transform);
	Vector3 pos = tr->GetPosition();

	CCollider2D* cd = this->GetOwner()->GetComponent<CCollider2D>(eComponentType::Collider2D);
	//std::vector<UINT>CollisionIDList = cd->GetCollisionIDs();


	// boss3 의 상태가 Idle 및 Attack 일 때 움직인다.
	/*if (mState.GetCurState() == eState::Idle)
	{
		pos.x += (float)(direction.x * 2.0 * CTimeMgr::GetInst()->GetDeltaTime());
		pos.y += (float)(direction.y * 2.0 * CTimeMgr::GetInst()->GetDeltaTime());
		tr->SetPosition(pos);
	}*/

	if (mState.GetCurState() == eState::Collide)
	{

	}

	/*if (mState.GetCurState() == eState::Idle && mState.GetPrevState() != eState::Idle)
	{

	}*/

	CScript::Update();
}

void CDesertBossScript::LateUpdate()
{
	CScript::LateUpdate();
}

void CDesertBossScript::Render()
{
	CScript::Render();
}
