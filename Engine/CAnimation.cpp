#include "CAnimation.h"
#include "CTimeMgr.h"

CAnimation::CAnimation()
	: CResource(eResourceType::Animation)
	, mAtlas(nullptr)
	, mAnimator(nullptr)
	, mSprites{}
	, mIndex(-1)
	, mTime(0.0f)
	, mbComplete(false)
{
}

CAnimation::~CAnimation()
{
}

void CAnimation::Update()
{
}

void CAnimation::LateUpdate()
{
	if (mbComplete)
	{
		return;
	}

	mTime += CTimeMgr::GetInst()->GetDeltaTime();

	if (mSprites[mIndex].duration <= mTime)
	{
		mIndex++;
		mTime = 0.0f;

		if (mSprites.size() <= mIndex)
		{

		}
	}
}

void CAnimation::Render()
{
}

void CAnimation::CreateAnimation(std::wstring aniName, std::shared_ptr<CTexture> atlas, Vector2 LeftTop, Vector2 size, UINT columnLength, Vector2 offset, float duration)
{
	SetKey(aniName);
	mAtlas = atlas;

	float width = (float)atlas->GetWidth();
	float height = (float)atlas->GetHeight();

	for (size_t i = 0 ; i < columnLength; i++)
	{
		Sprite sprite = {};
		sprite.leftTop.x = LeftTop.x + (i * size.x) / width;
		sprite.leftTop.y = LeftTop.y / height;
		sprite.size = size;
		sprite.Offset = offset;
		sprite.duration = duration;
		
		mSprites.push_back(sprite);
	}
}

void CAnimation::Binds()
{
	// texture bind'
	mAtlas->BindShaderResource(eShaderStage::PS, 12);

	// Animation CB

}

void CAnimation::Reset()
{
	mTime = 0.0f;
	mbComplete = false;
	mIndex = 0;
}
