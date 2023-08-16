#include "CDesertBossSquareScript.h"
#include "CGameObject.h"
#include "CTimeMgr.h"

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
}

void CDesertBossSquareScript::Update()
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
	mtime += CTimeMgr::GetInst()->GetDeltaTime();
	float moveDist = (float)(2.0 * CTimeMgr::GetInst()->GetDeltaTime());
	float dist = Vector3::Distance(parentPos, thisPos);
	if (dist > 0.9f)
	{
		Vector3 diff = Vector3(direct.x * moveDist, direct.y * moveDist, 0.0f);
		thisTr->SetPosition(Vector3(thisPos.x + diff.x, thisPos.y + diff.y, thisPos.z));
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
