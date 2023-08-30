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
	mFullHP = GetOwner()->GetParentObject()->GetHP(); // �θ� ��ü�� hp �ѷ�

	CTransform* tr = GetOwner()->GetComponent<CTransform>(eComponentType::Transform); // hp Bar �� tr
	mFullWidth = tr->GetScale().x;

	CScript::Initialize();
}

void CHPScript::Update()
{
	// full hp : full width = cur hp : cur width
	// cur width = full width * cur hp / full hp
	//CMeshRender* mr = GetOwner()->GetComponent<CMeshRender>(eComponentType::MeshRender);
	//std::shared_ptr<CMesh> mesh = mr->GetMesh();
	//tVertex vertex = mesh->GetVertex(0); // ó�� mesh �� ���� �ɶ� Vector3(-0.5, 0.5, 0) �̾��� ������ ���� ��ȯ �� ��ģ ������ ���� ���������� ��ǥ
	//Vector3 vertexPos = vertex.pos;
	//mLeftXPos = vertexPos.x;

	mCurHP = GetOwner()->GetParentObject()->GetHP(); // �θ� ��ü�� ���� hp ��

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
