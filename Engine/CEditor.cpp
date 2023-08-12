#include "CEditor.h"
#include "CCollider2D.h"

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

	std::shared_ptr<CMesh> mesh = CResourceMgr::Find<CMesh>(L"DebugMesh");
	std::shared_ptr<CMaterial> material = CResourceMgr::Find<CMaterial>(L"mt_Debug");

	mDebugObjects[(UINT)eColliderType::Rect] = new CDebugObject();
	//mDebugObjects[(UINT)eColliderType::Rect]->AddComponent<CTransform>();
	// DebugObject �� CGameObject �� ��� �޾ұ� ������ �⺻������ CTransform ������Ʈ�� ���� ���� �ʳ�>
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
	// �̷��� mDebugObjects[ColliderType::Rect]�� Transform�� �ٲ ���� �ʳ�?
	//CCollider2D* cd2D = debugObj->GetComponent<CCollider2D>(eComponentType::Collider2D);

	Vector3 pos = mesh.position;
	pos.z -= 0.0001f;// 1.0002f


	tr->SetPosition(pos);
	tr->SetScale(mesh.scale);
	tr->SetRotation(mesh.rotation);

	tr->LateUpdate(); // ���� ��ȯ �ϼ�

	if (mesh.IsCollider == true)
	{
		DebugColorCB cb;
		cb.DebugColor = Vector4(1.0f, 0.0f, 0.0f, 1.0f);
		CConstantBuffer* colliderCB = new CConstantBuffer;
		colliderCB->InitConstantBuffer(sizeof(DebugColorCB), eCBType::DebugColor, &cb);
		CRenderMgr::GetInst()->BindConstantBuffer(eShaderStage::VS, colliderCB);
		CRenderMgr::GetInst()->BindConstantBuffer(eShaderStage::PS, colliderCB);
	}
	else
	{
		DebugColorCB cb;
		cb.DebugColor = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
		CConstantBuffer* colliderCB = new CConstantBuffer;
		colliderCB->InitConstantBuffer(sizeof(DebugColorCB), eCBType::DebugColor, &cb);
		CRenderMgr::GetInst()->BindConstantBuffer(eShaderStage::VS, colliderCB);
		CRenderMgr::GetInst()->BindConstantBuffer(eShaderStage::PS, colliderCB);
	}

	// debugObj �� ������ �Ǳ� ���� �׿� ���� viewMatrix �� projection matrix �� ������ maincamera ���� �Ѵ�.
	CCamera* mainCamera = CCameraMgr::GetInst()->GetMainCamera();
	CCamera::SetStaticViewMatrix(mainCamera->GetViewMatrix());
	CCamera::SetStaticProjectionMatrix(mainCamera->GetProjectionMatrix());

	debugObj->Render();
}