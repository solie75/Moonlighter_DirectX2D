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

void CAnimation::CreateAnimation(std::wstring aniName, std::shared_ptr<CTexture> atlas, Vector2 LeftTop, Vector2 size, UINT columnLength, Vector2 offset, float duration)
{
	SetKey(aniName);
	mAtlas = atlas;

	float width = (float)atlas->GetWidth();
	float height = (float)atlas->GetHeight();

	for (size_t i = 0 ; i < columnLength; i++)
	{
		Sprite sprite = {};
		sprite.leftTop.x = LeftTop.x + (i * size.x) / width; // ���� ���� �ʴ´�. width/atlasNum * i ���� �ϴ°� �ƴѰ�
		sprite.leftTop.y = LeftTop.y / height; // ������ sprite ������ 10 ���� �����ϰ� ���� �����ٷ� �Ѿ�� �Ÿ� �ȵǳ�
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
