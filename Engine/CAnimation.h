#pragma once
#include "CResource.h"
#include "CTexture.h"
#include "CAnimator.h"

class CAnimation
	: public CResource
{
public:
	struct Sprite
	{
		Vector2 leftTop;
		Vector2 size;
		Vector2 Offset;
		float duration;

		Sprite()
			: leftTop(Vector2::Zero)
			, size(Vector2::Zero)
			, Offset(Vector2::Zero)
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
public:
	CAnimation();
	~CAnimation();

	void Update();
	void LateUpdate();
	void Render();

	void CreateAnimation(std::wstring aniName
		, std::shared_ptr<CTexture> atlas
		, Vector2 LeftTop
		, Vector2 size
		, UINT columnLength
		, Vector2 offset = Vector2::Zero
		, float duration = 0.0f);

	void Binds();
	void Reset();

	virtual HRESULT Load(const std::wstring& path) { return S_FALSE; }
};

