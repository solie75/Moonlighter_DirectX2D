#pragma once
#include "CComponent.h"
#include "CAnimation.h"
#include "CTexture.h"
#include "CConstantBuffer.h"

class CAnimator :
    public CComponent
{
public:
	struct Event
	{
		std::function<void()> mEvent;

		void operator=(std::function<void()> func)
		{
			mEvent = std::move(func);
		}
		void operator()()
		{
			if (mEvent)
			{
				mEvent();
			}
		}
	};

	struct Events
	{
		Event startEvent;
		Event completeEvent;
		Event endEvent;
	};

private:
	std::map<std::wstring, CAnimation*> mAnimations;
	CAnimation* mActiveAnimation;
	bool mbLoop;
	std::map<std::wstring, Events*> mEvents;
	CConstantBuffer* mAniCB;
	bool mbChange;

public:
	CAnimator();
	~CAnimator();

	virtual void Initialize();
	virtual void Update();
	virtual void LateUpdate();
	virtual void Render();

	void Create(const std::wstring& name
		, std::shared_ptr<CTexture> atlas
		, Vector2 leftTop
		, Vector2 spriteSize
		, UINT spriteNum
		, float duration // = 0.1f
		, Vector2 offset = Vector2::Zero
		);
	CAnimation* FindAnimation(const std::wstring& aniName);
	Events* FindEvents(const std::wstring& aniName);
	void PlayAnimation(const std::wstring& aniName, bool loop);
	void Binds();
	CAnimation* GetCurAnimation() { return mActiveAnimation; }

	std::function<void()>& StartEvent(const std::wstring key);
	std::function<void()>& CompleteEvent(const std::wstring key);
	std::function<void()>& EndEvent(const std::wstring key);
};

