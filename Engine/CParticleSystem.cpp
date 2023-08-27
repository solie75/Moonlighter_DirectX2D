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

	mCS = CResourceMgr::Find<CParticleShader>(L"ParticleSystemShader");

	Particle particles[1000] = {};
	for (size_t i = 0; i < 1000; i++)
	{
		Vector4 pos = Vector4::Zero;
		pos.x += rand() % 20;
		pos.y += rand() % 10;

		// 50�ۼ�Ʈ�� Ȯ���� x �� y ���� ���� ���� ��� ���� ���Ѵ�.
		int sign = rand() % 2; // 50% Ȯ���� 0 �Ǵ� 1�̴�.
		if (sign == 0)
		{
			pos.x *= -1.0f;
		}
		sign = rand() % 2;
		if (sign == 0)
		{
			pos.y *= -1.0f;
		}

		particles[i].direction =
			Vector4(cosf((float)i * (XM_2PI / (float)1000))
				, sinf((float)i * (XM_2PI / 100.f))
				, 0.0f, 1.0f);

		particles[i].position = pos; 
		particles[i].speed = 1.0f;
		particles[i].active = 1;
	}

	mBuffer = new CStructedBuffer();
	mBuffer->CreateStructedBuffer(sizeof(Particle), 1000, eViewType::UAV, particles);
	//mBuffer �� ����� �����Ȱ� ������...
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
	mCS->SetParticleBuffer(mBuffer);
	mCS->OnExcute();
}

void CParticleSystem::Render()
{
	CTransform* tr = this->GetOwner()->GetComponent<CTransform>(eComponentType::Transform);
	tr->CreateConstantBuffer();

	mBuffer->BindSRV(eShaderStage::VS, 14);
	mBuffer->BindSRV(eShaderStage::GS, 14);
	mBuffer->BindSRV(eShaderStage::PS, 14);

	GetMaterial()->Bind();
	GetMesh()->RenderInstanced(1000);

	mBuffer->Clear();
}
