#include "CAnimator.h"
#include "CGameObject.h"
#include "CMeshRender.h"

CAnimator::CAnimator()
	: CComponent(eComponentType::Animator)
	, mbChange(false)
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

	for (auto& iter : mEvents)
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
		Events* events = FindEvents(mActiveAnimation->GetKey());
		if (events)
		{
			events->completeEvent();
		}
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

	Events* events = FindEvents(aniName);
	if (events != nullptr)
	{
		return;
	}

	events = new Events();
	mEvents.insert(std::make_pair(aniName, events));
	
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

CAnimator::Events* CAnimator::FindEvents(const std::wstring& name)
{
	std::map<std::wstring, Events*>::iterator iter
		= mEvents.find(name);

	if (iter == mEvents.end())
	{
		return nullptr;
	}

	return iter->second;
}

void CAnimator::PlayAnimation(const std::wstring& aniName, bool loop)
{
	CAnimation* prevAnimation = mActiveAnimation;

	Events* events;
	if (prevAnimation != nullptr)
	{
		// ������ �ִϸ��̼��� ����
		events = FindEvents(prevAnimation->GetKey());
		if (events)
		{
			events->endEvent();
		}
	}

	CAnimation* ani = FindAnimation(aniName);
	if (ani)
	{
		// ���ο� �ִϸ��̼�
		mActiveAnimation = ani;
	}

	// ���ο� �ִϸ��̼��� ����
	events = FindEvents(mActiveAnimation->GetKey());
	if (events)
	{
		events->startEvent();
	}
	
	CMeshRender* mr = this->GetOwner()->GetComponent<CMeshRender>(eComponentType::MeshRender);
	std::shared_ptr<CMaterial> mt = CResourceMgr::Find<CMaterial>(L"mt_atlas_" + aniName);
	mr->SetMaterial(mt);

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

std::function<void()>& CAnimator::StartEvent(const std::wstring key)
{
	Events* events = FindEvents(key);

	return events->startEvent.mEvent;
}

std::function<void()>& CAnimator::CompleteEvent(const std::wstring key)
{
	Events* events = FindEvents(key);

	return events->completeEvent.mEvent;
}

std::function<void()>& CAnimator::EndEvent(const std::wstring key)
{
	Events* events = FindEvents(key);

	return events->endEvent.mEvent;
}
