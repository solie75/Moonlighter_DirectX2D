#include "CHPScript.h"
#include "CGameObject.h"
#include "CKeyMgr.h"
#include "CCollider2D.h"
#include "CColliderMgr.h"

CHPScript::CHPScript()
{
	mOffset = Vector2::Zero;
	HpObj = nullptr;
}

CHPScript::~CHPScript()
{
}

void CHPScript::Initialize()
{
	mFullHP = GetOwner()->GetParentObject()->GetHP(); // 부모 객체의 hp 총량

	// Hp Backgound의 초기 위치 선정
	if (GetOwner()->GetParentObject()->GetLayerType() == eLayerType::Monster)
	{
		Vector3 parentObjPos = GetOwner()->GetParentObject()->GetComponent<CTransform>(eComponentType::Transform)->GetPosition();
		CTransform* thisTr = GetOwner()->GetComponent<CTransform>(eComponentType::Transform);
		//thisTr->SetPosition(parentObjPos.x + mOffset.x, parentObjPos.y + mOffset.x, parentObjPos.z - 0.00001f);
		thisTr->SetPosition(parentObjPos.x + mOffset.x, parentObjPos.y + mOffset.x, parentObjPos.z - 0.001f);
	}
	else if (GetOwner()->GetParentObject()->GetLayerType() == eLayerType::Player)
	{
		CTransform* thisTr = GetOwner()->GetComponent<CTransform>(eComponentType::Transform);
		thisTr->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
	}
	else if (GetOwner()->GetParentObject()->GetLayerType() == eLayerType::Monster_Boss)
	{
		CTransform* thisTr = GetOwner()->GetComponent<CTransform>(eComponentType::Transform);
		thisTr->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
	}

	CScript::Initialize();
}

void CHPScript::Update()
{
	if (CKeyMgr::GetInst()->GetKeyState(KEY::P) == KEY_STATE::TAP)
	{
		GetOwner()->GetParentObject()->SetHP(GetOwner()->GetParentObject()->GetHP()-25);
	}

	CTransform* ParentMonsterTr = GetOwner()->GetParentObject()->GetComponent<CTransform>(eComponentType::Transform);
	CTransform* thisTr = GetOwner()->GetComponent<CTransform>(eComponentType::Transform);
	Vector3 PMPos = ParentMonsterTr->GetPosition(); // parent monster position

	// this 가 Monster Hp 인 경우 실시간으로 부모 객체인 몬스터의 위치변화에 대응한다.
	if (GetOwner()->GetParentObject()->GetLayerType() == eLayerType::Monster)
	{
		
		thisTr->SetPosition(Vector3(PMPos.x + mOffset.x, PMPos.y + mOffset.y, thisTr->GetPosition().z));
	}
	if (HpObj != nullptr)
	{
		Vector3 thisPos = thisTr->GetPosition();
		mCurHP = GetOwner()->GetParentObject()->GetHP(); // Monster 의 현재 hp 량
		float curWidth = (thisTr->GetScale().x * mCurHP) / mFullHP;
		
		CTransform* hpObjTr = HpObj->GetComponent<CTransform>(eComponentType::Transform);
		Vector3 hpObjScale = hpObjTr->GetScale();
		hpObjTr->SetScale(curWidth, hpObjScale.y, hpObjScale.z);
		

		hpObjTr->SetPosition(Vector3(thisPos.x - (thisTr->GetScale().x / 2) + (curWidth / 2), thisPos.y, thisTr->GetPosition().z - 0.001f));
	}

	/*CTransform* tr = GetOwner()->GetComponent<CTransform>(eComponentType::Transform);
	Vector3 scale = tr->GetScale();
	tr->SetScale(Vector3(curWidth, scale.y, scale.z));
	Vector3 pos = tr->GetPosition();
	tr->SetPosition(Vector3(mLeftXPos + (curWidth/2) , pos.y, pos.z));*/
	CScript::Update();
}

void CHPScript::LateUpdate()
{
	CScript::LateUpdate();
}

void CHPScript::Render()
{
	CScript::Render();
}

void CHPScript::AddHpObject(CScene* scene)
{
	CGameObject* dHpObj = new CGameObject;
	CTransform* HpTr = this->GetOwner()->GetComponent<CTransform>(eComponentType::Transform);
	scene->AddGameObject(eLayerType::HP, dHpObj, GetOwner()->GetParentObject()->GetName() + L"_HP", HpTr->GetPosition(), HpTr->GetScale()
		, true, L"Mesh", L"mt_HealthBar_Monster", false);

	HpObj = dHpObj;
}