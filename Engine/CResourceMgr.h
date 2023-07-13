#pragma once
#include "CSingleton.h"
#include "CResource.h"


class CResourceMgr : public CSingleton<CResourceMgr>
{
private:
	std::map<std::wstring, std::shared_ptr<CResource>> mResources;

public:
	CResourceMgr();
	~CResourceMgr();

	template <typename T>
	static std::shared_ptr<T> Find(const std::wstring& key)
	{
		std::map<std::wstring, std::shared_ptr<CResource>>::iterator iter = mResources.find(key);

		if (iter != mResources.end())
		{
			return iter->second;
			//return std::dynamic_pointer_cast<T>(iter->second);
		}

		return nullptr;
	}

	template <typename T>
	static std::shared_ptr<T> Load(const std::wstring& key, const std::wstring& path)
	{
		std::shared_ptr<T> resource = CResource::Find<T>(key);
		if (resource != nullptr)
		{
			return resource;
		}

		resource = std::make_shared<T>();
		if (FAILED(resource->ResourceLoad(path)))
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

