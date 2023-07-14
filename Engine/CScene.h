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

	void AddGameObject(eLayerType type, CGameObject* gameObj, const std::wstring& name);
};

