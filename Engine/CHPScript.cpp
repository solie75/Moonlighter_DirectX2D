#include "CHPScript.h"
#include "CGameObject.h"

CHPScript::CHPScript()
{

}

CHPScript::~CHPScript()
{
}

void CHPScript::Initialize()
{
	mFullHP = GetOwner()->GetParentObject()->GetHP(); // ºÎ¸ð °´Ã¼ÀÇ hp ÃÑ·®

	CTransform* tr = GetOwner()->GetComponent<CTransform>(eComponentType::Transform); // hp Bar ÀÇ tr
	mFullWidth = tr->GetScale().x;
	mLeftXPos = tr->GetPosition().x - (mFullWidth / 2);
	 
	CScript::Initialize(); 
}

void CHPScript::Update()
{
	mCurHP = GetOwner()->GetParentObject()->GetHP(); // ºÎ¸ð °´Ã¼ÀÇ ÇöÀç hp ·®

	float curWidth = (mFullWidth * mCurHP) / mFullHP;

	CTransform* tr = GetOwner()->GetComponent<CTransform>(eComponentType::Transform);
	Vector3 scale = tr->GetScale();
	tr->SetScale(Vector3(curWidth, scale.y, scale.z));
	Vector3 pos = tr->GetPosition();
	tr->SetPosition(Vector3(mLeftXPos + (curWidth/2) , pos.y, pos.z));
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
