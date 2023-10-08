#pragma once
#include "CResource.h"
#include "CTexture.h"
#include "CConstantBuffer.h"

class CAnimator;
class CAnimation
	: public CResource
{
public:
	struct Sprite
	{
		Vector2 leftTop;
		Vector2 spriteSize;
		Vector2 Offset;
		Vector2 atlasSize;
		float duration;

		Sprite()
			: leftTop(Vector2::Zero)
			, spriteSize(Vector2::Zero)
			, Offset(Vector2::Zero)
			, atlasSize(Vector2::Zero)
			, duration(0.0f)
		{ }
	};
private:
	std::shared_ptr<CTexture> mAtlas;
	CAnimator* mAnimator;
	std::vector<Sprite> mSprites;
	int mIndex;
	float mTime;
	bool mbComplete;

	eAnimationType mAnimationType;

public:
	CAnimation();
	~CAnimation();

	void Update();
	void LateUpdate();
	void Render();

	void CreateAnimation(std::wstring aniName
		, std::shared_ptr<CTexture> atlas
		, Vector2 LeftTop
		, Vector2 spriteSize
		, UINT spriteNum
		, float duration
		, Vector2 offset
		);

	void Binds(CConstantBuffer* aniCB);
	void Reset();

	bool IsComplete() { return mbComplete; }
	int GetAnimationIndex() { return mIndex; }
	void SetAnimationType(eAnimationType aniType) { mAnimationType = aniType; }
	eAnimationType GetAnimationType() { return mAnimationType; }
	virtual HRESULT ResourceLoad(const std::wstring name, const std::wstring& path) { return S_FALSE; }

	//void CreateAtlas(const std::wstring& path, const std::wstring& spriteName, int spriteNum);
};

