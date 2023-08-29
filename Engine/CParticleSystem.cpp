#include "CParticleSystem.h"
#include "CTimeMgr.h"
#include <random>

CParticleSystem::CParticleSystem()
	: mParticleNum(75)
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

	for (size_t i = 0; i < mParticleNum; i++)
	{
		Vector4 pos = SetRendomPos();

		float valueX = SetRendomFloat(90.f, 270.f);
		float valueY = SetRendomFloat(90.f, 270.f);
		float valueSpeed = SetRendomFloat(0.01f, 0.02f);
		float valueTime = SetRendomFloat(1.0f, 2.5f); 


		float directionX = cosf(valueX * (XM_2PI / (float)360));
		float directionY = sinf(valueY * (XM_2PI / (float)360));


		mParticles[i].direction =
			Vector4(directionX, directionY, 0.0f, 1.0f);

		mParticles[i].position = pos;
		mParticles[i].speed = valueSpeed;
		mParticles[i].state = (UINT)eParticleState::Active;
		mParticles[i].startSize = Vector4(0.1f, 0.1f, 0.1f, 0.0f);
		mParticles[i].endSize = Vector4::One;
		mParticles[i].startColor = Vector4(0.8f, 0.447f, 0.239f, 0.0f);
		mParticles[i].endColor = Vector4::One;
		mParticles[i].endTime = valueTime;
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

Vector4 CParticleSystem::SetRendomPos()
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

	return pos;
}

float CParticleSystem::SetRendomFloat(float leftValue, float rightValue)
{
	std::random_device rd;
	std::mt19937 gen(rd());

	std::uniform_real_distribution<float> realDistribution(leftValue, rightValue);

	return realDistribution(gen);
}