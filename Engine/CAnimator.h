#pragma once
#include "CComponent.h"
#include "CAnimation.h"
#include "CTexture.h"
#include "CConstantBuffer.h"

class CAnimator :
    public CComponent
{
private:
	std::map<std::wstring, CAnimation*> mAnimations;
	CAnimation* mActiveAnimation;
	bool mbLoop;
	//std::map<std::wstring, Events*> mEvents;
	CConstantBuffer* mAniCB;

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
		, Vector2 size
		, UINT columnLength
		, Vector2 offset = Vector2::Zero
		, float duration = 0.1f);
	CAnimation* FindAnimation(const std::wstring& aniName);
	void PlayAnimation(const std::wstring& aniName, bool loop);
	void Binds();
};

