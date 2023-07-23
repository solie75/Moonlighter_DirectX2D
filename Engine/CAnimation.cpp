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
	{ // �ִϸ��̼��� �������� return
		return;
	}

	// �ִϸ��̼��� ������ ���� ���
	mTime += CTimeMgr::GetInst()->GetDeltaTime(); // �ð� ����

	if (mSprites[mIndex].duration <= mTime)
	{ // �ִϸ��̼��� �� �������� ���� �ð��� �����ٸ� 
		mIndex++; // ���� ����������
		mTime = 0.0f; // ������ �ð� clear

		if (mSprites.size() <= mIndex)
		{ // ����Ű�� �������� ��������Ʈ �԰� �ܶ�� ������ �������� ����Ű���� �Ѵ�.
			mIndex = mSprites.size() - 1;
			mbComplete = true; // �ϳ��� �ִϸ��̼��� ����
		}
	}
}

void CAnimation::Render()
{
}

void CAnimation::CreateAnimation(std::wstring aniName, std::shared_ptr<CTexture> atlas, Vector2 LeftTop, Vector2 spriteSize, UINT spriteNum, Vector2 offset, float duration)
{
	SetKey(aniName);
	mAtlas = atlas;

	float width = (float)atlas->GetWidth();
	float height = (float)atlas->GetHeight();

	for (int i = 0 ; i < spriteNum; i++)
	{
		Sprite sprite = {};
		//sprite.leftTop.x = LeftTop.x + (i * size.x) / width; // ���� ���� �ʴ´�. width/atlasNum * i ���� �ϴ°� �ƴѰ�
		sprite.leftTop.x = LeftTop.x + i * (width / 10.f);
		//sprite.leftTop.y = LeftTop.y / height; // ������ sprite ������ 10 ���� �����ϰ� ���� �����ٷ� �Ѿ�� �Ÿ� �ȵǳ�
		sprite.leftTop.y = LeftTop.y + ((int)i / 10) * spriteSize.y;
		sprite.spriteSize = spriteSize;
		sprite.Offset = offset;
		sprite.atlasSize = Vector2(width, height);
		sprite.duration = duration;
		
		mSprites.push_back(sprite);
	}
}

void CAnimation::Binds(CConstantBuffer* aniCB)
{
	// texture bind'
	mAtlas->BindShaderResource(eShaderStage::PS, 12);

	Vector2 scale = Vector2(mSprites[mIndex].spriteSize.x / mSprites[mIndex].atlasSize.x, mSprites[mIndex].spriteSize.y / mSprites[mIndex].atlasSize.y);
	Vector2 offset = Vector2(mIndex * scale.x, (mIndex / 10) * scale.y);

	AnimatorCB cb;
	cb.SpriteSize = scale;
	cb.Offset = offset;
	cb.AnimationType = 1;

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
