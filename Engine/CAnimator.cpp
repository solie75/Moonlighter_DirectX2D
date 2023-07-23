#include "CAnimator.h"

CAnimator::CAnimator()
	: CComponent(eComponentType::Animator)
{
	mAniCB = new CConstantBuffer();
}

CAnimator::~CAnimator()
{
	for (auto& iter : mAnimations)
	{
		delete iter.second;
		iter.second = nullptr;
	}
}

void CAnimator::Initialize()
{
}

void CAnimator::Update()
{
	if (mActiveAnimation == nullptr)
	{
		return;
	}
	if (mActiveAnimation->IsComplete() && mbLoop)
	{
		mActiveAnimation->Reset();
	}
	mActiveAnimation->LateUpdate();
}

void CAnimator::LateUpdate()
{
}

void CAnimator::Render()
{
}

void CAnimator::Create(const std::wstring& aniName, std::shared_ptr<CTexture> atlas, Vector2 leftTop, Vector2 spriteSize, UINT spriteNum, Vector2 offset, float duration)
{
	CAnimation* ani = FindAnimation(aniName);
	if (nullptr != ani)
	{
		return; // �̹� �ش� �ִϸ��̼��� �����ϴ� ���
	}

	ani = new CAnimation();
	ani->SetKey(aniName);
	ani->SetName(aniName);
	ani->CreateAnimation(aniName
		, atlas
		, leftTop
		, spriteSize
		, spriteNum
		, offset
		, duration);

	mAnimations.insert(std::make_pair(aniName, ani));

}

CAnimation* CAnimator::FindAnimation(const std::wstring& aniName)
{
	std::map<std::wstring, CAnimation*>::iterator iter
		= mAnimations.find(aniName);
	if (iter == mAnimations.end())
	{
		return nullptr;
	}
	return iter->second;
}

void CAnimator::PlayAnimation(const std::wstring& aniName, bool loop)
{
	CAnimation* prevAni = mActiveAnimation;

	CAnimation* ani = FindAnimation(aniName);
	if (ani)
	{
		mActiveAnimation = ani;
	}
	mbLoop = loop;
	mActiveAnimation->Reset();
}

void CAnimator::Binds()
{
	if (mActiveAnimation == nullptr)
	{
		return;
	}
	mActiveAnimation->Binds(mAniCB);
}
