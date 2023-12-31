#include "CAnimation.h"
#include "CTimeMgr.h"
#include "Graphic.h"
#include "CRenderMgr.h"


CAnimation::CAnimation()
	: CResource(eResourceType::Animation)
	, mAtlas(nullptr)
	, mAnimator(nullptr)
	, mSprites{}
	, mIndex(-1)
	, mTime(0.0f)
	, mbComplete(false)
{
	mAnimationType = eAnimationType::Basic;
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
	{ // 애니메이션이 끝났으면 return
		return;
	}

	// 애니메이션이 끝나지 않은 경우
	mTime += CTimeMgr::GetInst()->GetDeltaTime(); // 시간 축적

	if (mSprites[mIndex].duration <= mTime)
	{ // 애니메이션의 한 프레임의 지속 시간이 지났다면 
		mIndex++; // 다음 프레임으로
		mTime = 0.0f; // 축적된 시간 clear

		if (mSprites.size() <= mIndex)
		{ // 가리키는 프레임이 스프라이트 규격 외라면 마지막 프레임을 가리키도록 한다.
			mIndex = mSprites.size() - 1;
			mbComplete = true; // 하나의 애니메이션의 종료
		}
	}
}

void CAnimation::Render()
{
}

void CAnimation::CreateAnimation(std::wstring aniName, std::shared_ptr<CTexture> atlas, Vector2 LeftTop, Vector2 spriteSize, UINT spriteNum, float duration, Vector2 offset)
{
	SetKey(aniName);
	mAtlas = atlas;

	float width = (float)atlas->GetMetadataWidth();
	float height = (float)atlas->GetMetadataHeight();

	for (int i = 0 ; i < spriteNum; i++)
	{
		Sprite sprite = {};
		sprite.leftTop.x = i * (spriteSize.x);
		sprite.leftTop.y = 0.0f;
		sprite.spriteSize = spriteSize;
		sprite.Offset = Vector2(i*(spriteSize.x / width), 0.0f);
		sprite.atlasSize = Vector2(width, height);
		sprite.duration = duration;
		
		mSprites.push_back(sprite);
	}
}

void CAnimation::Binds(CConstantBuffer* aniCB)
{
	// texture bind'
	mAtlas->BindShaderResource(eShaderStage::PS, 12);

	Vector2 scale = Vector2(mSprites[mIndex].spriteSize.x / mSprites[mIndex].atlasSize.x, 1.0f);
	Vector2 offset = mSprites[mIndex].Offset;

	AnimatorCB cb;
	cb.SpriteSize = scale;
	cb.Offset = offset;
	cb.AnimationType = (UINT)mAnimationType;

	aniCB->InitConstantBuffer(sizeof(AnimatorCB), eCBType::Animator, &cb);
	CRenderMgr::GetInst()->BindConstantBuffer(eShaderStage::VS, aniCB);
	CRenderMgr::GetInst()->BindConstantBuffer(eShaderStage::PS, aniCB);
}

void CAnimation::Reset()
{
	mTime = 0.0f;
	mbComplete = false;
	mIndex = 0;
}


