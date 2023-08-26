#include "CParticleShader.h"
#include "CTimeMgr.h"
#include "CRenderMgr.h"


CParticleShader::CParticleShader()
	: CComputeShader(128, 1, 1)
	, mParticleBuffer(nullptr)
{
}

CParticleShader::~CParticleShader()
{
}

void CParticleShader::Binds()
{
	mParticleBuffer->BindUAV(0);

	mGroupX = mParticleBuffer->GetStride() / mThreadGroupCountX + 1;
	mGroupY = 1;
	mGroupZ = 1;
}

void CParticleShader::Clear()
{
	mParticleBuffer->Clear();
}

void CParticleShader::SetParticleBuffer(CStructedBuffer* particleBuffer)
{
	mParticleBuffer = particleBuffer;

	static float elapsedTime = 0.0f; // 이 변수가 하는 역할이 뭐길래  static 이지? (elapsed : 경과)
	elapsedTime += CTimeMgr::GetInst()->GetDeltaTime();

	ParticleCB cbData = {};
	cbData.elementCount = mParticleBuffer->GetStride();
	cbData.elpasedTime = CTimeMgr::GetInst()->GetDeltaTime(); // 

	mParticleCB->InitConstantBuffer(sizeof(mParticleCB), eCBType::Particle, &cbData);
	CRenderMgr::GetInst()->BindConstantBuffer(eShaderStage::CS, mParticleCB);
}
