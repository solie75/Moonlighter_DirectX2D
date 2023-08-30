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
	mFullHP = GetOwner()->GetParentObject()->GetHP(); // 부모 객체의 hp 총량

	CTransform* tr = GetOwner()->GetComponent<CTransform>(eComponentType::Transform); // hp Bar 의 tr
	mFullWidth = tr->GetScale().x;

	CScript::Initialize();
}

void CHPScript::Update()
{
	// full hp : full width = cur hp : cur width
	// cur width = full width * cur hp / full hp
	//CMeshRender* mr = GetOwner()->GetComponent<CMeshRender>(eComponentType::MeshRender);
	//std::shared_ptr<CMesh> mesh = mr->GetMesh();
	//tVertex vertex = mesh->GetVertex(0); // 처음 mesh 가 선언 될때 Vector3(-0.5, 0.5, 0) 이었던 정점이 월드 변환 을 거친 이후의 월드 공간에서의 좌표
	//Vector3 vertexPos = vertex.pos;
	//mLeftXPos = vertexPos.x;

	mCurHP = GetOwner()->GetParentObject()->GetHP(); // 부모 객체의 현재 hp 량

	if (mCurHP <= 700)
	{
		int a = 0;
	}

	float curWidth = (mFullWidth * mCurHP) / mFullHP;

	CTransform* tr = GetOwner()->GetComponent<CTransform>(eComponentType::Transform);
	Vector3 scale = tr->GetScale();
	tr->SetScale(Vector3(curWidth, scale.y, scale.z));
	Vector3 pos = tr->GetPosition();
	tr->SetPosition(Vector3(pos.x - 1.0f, pos.y, pos.z));
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
