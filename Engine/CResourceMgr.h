#pragma once
#include "CSingleton.h"
#include "Header.h"
#include "CResource.h"
#include "CPathMgr.h"
#include "Graphic.h"
#include "CAnimator.h"
#include "CRenderMgr.h"

class CResourceMgr : public CSingleton<CResourceMgr>
{
public:
	struct AnimationData
	{
		std::wstring name;
		int spriteNum;
		eRenderingMode renderingMode;
		Vector2 size;
		std::wstring objName;
		float duration;
	};
private:
	std::map<std::wstring, std::shared_ptr<CResource>> mResources;
	std::vector<AnimationData> mAnimationDatas; // <ObjectName, data>
public:
	CResourceMgr();
	~CResourceMgr();

	void LoadAnimationData();
	void CreateAtlas(const std::wstring& spriteName, int spriteNum);
	void CreateAnimationTest(const std::wstring& objName, CAnimator* animator)
	{
		for (int i = 0; i < mAnimationDatas.size(); i++)
		{
			if (mAnimationDatas[i].objName == objName) // 함수의 인자에 해당하는 mAnimationData 의 데이터에 대하여 애니메이션을 생성한다.
			{
				// atlas 생성
				CreateAtlas(mAnimationDatas[i].name, mAnimationDatas[i].spriteNum);
				std::wstring atlasTexkey = L"atlas_" + mAnimationDatas[i].name;

				std::shared_ptr<CShader> shader = CResourceMgr::GetInst()->Find<CShader>(L"AnimationShader");
				// Material 생성
				CreateMaterial(shader, atlasTexkey, (eRenderingMode)mAnimationDatas[i].renderingMode);

				// Animation 생성
				animator->Create(mAnimationDatas[i].name,
					CResourceMgr::GetInst()->Load<CTexture>(atlasTexkey, L""),
					Vector2(0.0f, 0.0f),
					Vector2(mAnimationDatas[i].size.x, mAnimationDatas[i].size.y),
					mAnimationDatas[i].spriteNum,
					mAnimationDatas[i].duration * 0.001f);
			}
		}
	}

	void CreateMaterial(std::shared_ptr<CShader> shader, const std::wstring& textureName, eRenderingMode renderMode)
	{
		std::shared_ptr<CTexture> tex = CResourceMgr::GetInst()->Find<CTexture>(textureName);

		std::shared_ptr<CMaterial> mt = std::make_shared<CMaterial>();
		mt->SetName(L"mt_" + textureName);
		mt->SetShader(shader);
		mt->SetTexture(tex);
		mt->SetRenderMode(renderMode);
		CResourceMgr::GetInst()->Insert(L"mt_" + textureName, mt);
	}


	template <typename T>
	static std::shared_ptr<T> Find(const std::wstring& key)
	{
		std::map<std::wstring, std::shared_ptr<CResource>>::iterator iter = CResourceMgr::GetInst()->mResources.find(key);

		if (iter != CResourceMgr::GetInst()->mResources.end())
		{
			//return iter->second;
			return std::dynamic_pointer_cast<T>(iter->second);
		}

		return nullptr;
	}

	template <typename T>
	static std::shared_ptr<T> Load(const std::wstring& key, const std::wstring& path)
	{
		std::shared_ptr<T> resource = CResourceMgr::Find<T>(key);
		if (resource != nullptr)
		{
			return resource;
		}

		resource = std::make_shared<T>();
		if (FAILED(resource->ResourceLoad(key, path)))
		{
			assert(false);
			return nullptr;
		}

		resource->SetKey(key);
		resource->SetPath(path);
		CResourceMgr::GetInst()->mResources.insert(std::make_pair(key, resource));

		return resource;
	}

	template <typename T>
	static void Insert(const std::wstring& key, std::shared_ptr<T> resource)
	{
		CResourceMgr::GetInst()->mResources.insert(std::make_pair(key, resource));
	}
};

