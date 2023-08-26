#include "CParticleSystem.h"

CParticleSystem::CParticleSystem()
	: mCount(0)
	, mStartSize(Vector4::One)
	, mEndSize(Vector4::One)
	, mStartColor(Vector4::Zero)
	, mEndColor(Vector4::Zero)
	, mLifeTime(0.0f)
{
	std::shared_ptr<CMesh> mesh = CResourceMgr::GetInst()->Find<CMesh>(L"PointMesh");
	SetMesh(mesh);

	std::shared_ptr<CMaterial> material = CResourceMgr::GetInst()->Find<CMaterial>(L"mt_Particle");
	SetMaterial(material);

	Particle particles[1000] = {};
	for (size_t i = 0; i < 1000; i++)
	{
		Vector4 pos = Vector4::Zero;
		pos.x += rand() % 20;
		pos.y += rand() % 10;

		// 50퍼센트의 확률로 x 와 y 값을 음수 일지 양수 일지 정한다.
		int sign = rand() % 2; // 50% 확률로 0 또는 1이다.
		if (sign == 0)
		{
			pos.x *= -1.0f;
		}
		sign = rand() % 2;
		if (sign == 0)
		{
			pos.y *= -1.0f;
		}

		particles[i].position = pos; 
		particles[i].active = 1;
	}

	mBuffer = new CStructedBuffer();
	mBuffer->CreateStructedBuffer(sizeof(Particle), 1000, eSRVType::None);
	mBuffer->SetData(particles, 1000);
}

CParticleSystem::~CParticleSystem()
{
}

void CParticleSystem::Initialize()
{
}

void CParticleSystem::Update()
{
}

void CParticleSystem::LateUpdate()
{
}

void CParticleSystem::Render()
{
	CTransform* tr = this->GetOwner()->GetComponent<CTransform>(eComponentType::Transform);
	tr->CreateConstantBuffer();
	CRenderMgr::GetInst()->BindConstantBuffer(eShaderStage::VS, tr->GetTransformCB());

	mBuffer->Bind(eShaderStage::VS, 14);
	mBuffer->Bind(eShaderStage::GS, 14);
	mBuffer->Bind(eShaderStage::PS, 14);

	GetMaterial()->Bind();
	GetMesh()->RenderInstanced(1000);
}
