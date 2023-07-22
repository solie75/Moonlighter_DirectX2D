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

void CAnimation::CreateAnimation(std::wstring aniName, std::shared_ptr<CTexture> atlas, Vector2 LeftTop, Vector2 size, UINT columnLength, Vector2 offset, float duration)
{
	SetKey(aniName);
	mAtlas = atlas;

	float width = (float)atlas->GetWidth();
	float height = (float)atlas->GetHeight();

	for (size_t i = 0 ; i < columnLength; i++)
	{
		Sprite sprite = {};
		sprite.leftTop.x = LeftTop.x + (i * size.x) / width; // 이해 가지 않는다. width/atlasNum * i 여야 하는것 아닌가
		sprite.leftTop.y = LeftTop.y / height; // 가로의 sprite 개수를 10 개로 한정하고 다음 가로줄로 넘어가는 거면 안되나
		sprite.size = size; 
		sprite.Offset = offset;
		sprite.atlasSize = Vector2(200.0f / width, 200.0f / height);
		sprite.duration = duration;
		
		mSprites.push_back(sprite);
	}
}

void CAnimation::Binds(CConstantBuffer* aniCB)
{
	// texture bind'
	mAtlas->BindShaderResource(eShaderStage::PS, 3);

	// Animation CB
	AnimatorCB cb;
	cb.spriteLeftTop = mSprites[mIndex].leftTop;
	cb.spriteSize = mSprites[mIndex].size;
	cb.spriteOffset = mSprites[mIndex].Offset;
	cb.atlasSize = mSprites[mIndex].atlasSize;
	cb.animationType = 1;

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
