#include "CParticleSystem.h"
#include "CTimeMgr.h"
#include <random>

CParticleSystem::CParticleSystem()
	: mParticleNum(100)
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

	//Particle particles[100] = {};
	for (size_t i = 0; i < mParticleNum; i++)
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

		// 우측에서 왼쪽으로
		std::random_device rd; // 하드웨어 기반 난수 생성기를 초기화
		std::mt19937 genX(rd()); // 난수 생성기 초기화
		std::mt19937 genY(rd());
		std::mt19937 genSpeed(rd());
		std::mt19937 genTime(rd());

		std::uniform_real_distribution<float> realDistributionX(90, 270);
		std::uniform_real_distribution<float> realDistributionY(90, 270);
		std::uniform_real_distribution<float> realDistributionSpeed(2.0f, 3.0f);
		std::uniform_real_distribution<float> realDistributionTime(2.0f, 3.0f);

		float directionX = cosf(realDistributionX(genX) * (XM_2PI / (float)360));
		float directionY = sinf(realDistributionY(genY) * (XM_2PI / (float)360));


		mParticles[i].direction =
			Vector4(directionX, directionY, 0.0f, 1.0f);

		mParticles[i].position = pos;
		mParticles[i].speed = realDistributionSpeed(genSpeed);
		mParticles[i].state = (UINT)eParticleState::Active;
		mParticles[i].startSize = Vector4(0.1f, 0.1f, 0.1f, 0.0f);
		mParticles[i].endSize = Vector4::One;
		mParticles[i].startColor = Vector4(0.8f, 0.447f, 0.239f, 0.0f);
		mParticles[i].endColor = Vector4::One;
		mParticles[i].endTime = realDistributionTime(genTime);
		mParticles[i].curTime = 0.0f;
		
	}

	mBuffer = new CStructedBuffer();
	mBuffer->CreateStructedBuffer(sizeof(Particle), mParticleNum, eViewType::UAV, mParticles);
}

CParticleSystem::~CParticleSystem()
{
}

void CParticleSystem::Initialize()
{
}

void CParticleSystem::Update()
{
	for (int i = 0; i < 100; i++)
	{
		mParticles[i].curTime += CTimeMgr::GetInst()->GetDeltaTime();
		if (mParticles[i].curTime >= mParticles[i].endTime)
		{
			mParticles[i].state = (UINT)eParticleState::Dead;
		}
	}
	mBuffer->CreateStructedBuffer(sizeof(Particle), mParticleNum, eViewType::UAV, mParticles);
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
	GetMesh()->RenderInstanced(mParticleNum);

	mBuffer->Clear();
}
