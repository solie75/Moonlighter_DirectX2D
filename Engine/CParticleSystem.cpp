#include "CParticleSystem.h"
#include <random>

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
		pos.x += 3 + rand() % 20;
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

		// 전방위
		/*float directionX = cosf((float)i * (XM_2PI / (float)1000));
		float directionY = sinf((float)i * (XM_2PI / 100.f));*/

		// 우측에서 왼쪽으로
		std::random_device rd; // 하드웨어 기반 난수 생성기를 초기화
		std::mt19937 genX(rd()); // 난수 생성기 초기화
		std::mt19937 genY(rd());
		std::mt19937 genSpeed(rd());

		std::uniform_real_distribution<float> realDistributionX(90, 270);
		std::uniform_real_distribution<float> realDistributionY(90, 270);
		std::uniform_real_distribution<float> realDistributionSpeed(2.0f, 3.0f);

		float directionX = cosf(realDistributionX(genX) * (XM_2PI / (float)360));
		float directionY = sinf(realDistributionY(genY) * (XM_2PI / (float)360));

		/*if (i > 75)
		{
			directionX = cosf((float)(i - 25) * (XM_2PI / (float)360));
			directionY = sinf((float)(i - 25) * (XM_2PI / 100.f));
		}
		else if (i < 25)
		{
			directionX = cosf((float)(i + 25) * (XM_2PI / (float)360));
			directionY = sinf((float)(i + 25) * (XM_2PI / 100.f));
		}
		else
		{
			directionX = cosf((float)i * (XM_2PI / (float)100));
			directionY = sinf((float)i * (XM_2PI / 100.f));
		}*/

		particles[i].direction =
			Vector4(directionX, directionY, 0.0f, 1.0f);

		particles[i].position = pos; 
		particles[i].speed = realDistributionSpeed(genSpeed);
		particles[i].state = (UINT)eParticleState::Active;
		particles[i].startSize = Vector4(0.1f, 0.1f, 0.1f, 0.0f);
		particles[i].endSize = Vector4::One;
		particles[i].startColor = Vector4(0.8f, 0.447f, 0.239f, 0.0f);
		particles[i].endColor = Vector4::One;
	}

	mBuffer = new CStructedBuffer();
	mBuffer->CreateStructedBuffer(sizeof(Particle), 1000, eViewType::UAV, particles);
	//mBuffer 는 제대로 생성된것 같은데...
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
