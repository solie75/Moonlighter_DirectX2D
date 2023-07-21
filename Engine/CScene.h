#pragma once
#include "CEntity.h"
#include "CLayer.h"

class CScene :
    public CEntity
{
private:
	std::vector<CLayer> mLayers;

public:
	CScene();
	 ~CScene();

	virtual void Initialize();
	virtual void Update();
	virtual void LateUpdate();
	virtual void Render();

	virtual void Destroy();

	void AddGameObject(eLayerType type, CGameObject* gameObj, const std::wstring& objName
		, Vector3 position, Vector3 scale, bool meshRenderBool, const std::wstring& meshName, const std::wstring& materialName);

	CLayer& GetLayer(eLayerType type) { return mLayers[(UINT)type]; }

	/*template <typename T>
	std::vector<T*> FindObjectsOfType()
	{
		std::vector<T*> findObjs = {};
		for (CLayer* layer : mLayers)
		{
			auto gameObjs = layer->GetGameObjects();
		}
	}*/
};

