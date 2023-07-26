#include "CEditor.h"

std::vector<CDebugObject*> CEditor::mDebugObjects = {};

CEditor::CEditor()
{
}

CEditor::~CEditor()
{
}

void CEditor::Initialize()
{
	mDebugObjects.resize((UINT)eColliderType::End);

	std::shared_ptr<CMesh> mesh = CResourceMgr::Find<CMesh>(L"DebugRect");
	std::shared_ptr<CMaterial> material = CResourceMgr::Find<CMaterial>(L"DebugMaterial");

	mDebugObjects[(UINT)eColliderType::Rect] = new CDebugObject();
	mDebugObjects[(UINT)eColliderType::Rect]->AddComponent<CTransform>();
	CMeshRender* mr = mDebugObjects[(UINT)eColliderType::Rect]->AddComponent<CMeshRender>();
	mr->SetMaterial(material);
	mr->SetMesh(mesh);
}

void CEditor::Run()
{
	Update();
	LateUpdate();
	Render();
}

void CEditor::Update()
{
}

void CEditor::LateUpdate()
{
}

void CEditor::Render()
{
	vector<DebugMesh> meshs = CRenderMgr::GetInst()->GetDebugMesh();
	for (const DebugMesh& mesh : meshs)
	{
		DebugRender(mesh);
	}
	CRenderMgr::GetInst()->ClearDebugMesh();
}

void CEditor::Release()
{
	for (auto debugObj : mDebugObjects)
	{
		delete debugObj;
		debugObj = nullptr;
	}
}

void CEditor::DebugRender(const DebugMesh& mesh)
{
	CDebugObject* debugObj = mDebugObjects[(UINT)mesh.type];

	CTransform* tr = debugObj->GetComponent<CTransform>(eComponentType::Transform);
	Vector3 pos = mesh.position;
	pos.z -= 0.01f;

	tr->SetPosition(pos);
	tr->SetScale(mesh.scale);
	tr->SetRotation(mesh.rotation);

	tr->LateUpdate();

	// ���� ���� ���� ī�޶��� view �� projection �� �ٸ� �������� ����ϱ� ���� ���� ���� matrix �� �����Ѵ�.
	CCamera* mainCamera = CCameraMgr::GetInst()->GetMainCamera();
	CCamera::SetStaticViewMatrix(mainCamera->GetViewMatrix());
	CCamera::SetStaticProjectionMatrix(mainCamera->GetProjectionMatrix());

	debugObj->Render();
}