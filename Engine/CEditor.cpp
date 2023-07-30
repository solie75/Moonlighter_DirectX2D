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

	std::shared_ptr<CMesh> mesh = CResourceMgr::Find<CMesh>(L"DebugMesh");
	std::shared_ptr<CMaterial> material = CResourceMgr::Find<CMaterial>(L"mt_Debug");

	mDebugObjects[(UINT)eColliderType::Rect] = new CDebugObject();
	//mDebugObjects[(UINT)eColliderType::Rect]->AddComponent<CTransform>();
	// DebugObject 는 CGameObject 를 상속 받았기 때문에 기본적으로 CTransform 컴포넌트를 갖고 있지 않나>
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
	// 이러면 mDebugObjects[ColliderType::Rect]의 Transform이 바뀌에 되지 않나?

	Vector3 pos = mesh.position;
	pos.z -= 0.0001f;// 1.0002f

	tr->SetPosition(pos);
	tr->SetScale(mesh.scale);
	tr->SetRotation(mesh.rotation);

	tr->LateUpdate(); // 월드 변환 완성

	// debugObj 가 렌더링 되기 전에 그에 대한 viewMatrix 와 projection matrix 의 기준은 maincamera 여야 한다.
	CCamera* mainCamera = CCameraMgr::GetInst()->GetMainCamera();
	CCamera::SetStaticViewMatrix(mainCamera->GetViewMatrix());
	CCamera::SetStaticProjectionMatrix(mainCamera->GetProjectionMatrix());

	debugObj->Render();
}