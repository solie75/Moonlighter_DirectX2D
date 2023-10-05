#pragma once
#include "CComponent.h"
#include "CCollider2D.h"

class CColliderMgr :
    public CComponent
{
private:
    vector<CCollider2D*> ColliderList;

public:
	CColliderMgr();
	~CColliderMgr();

	virtual void Initialize();
	virtual void Update();
	virtual void LateUpdate();
	virtual void Render();

	void AddCollider(CCollider2D* Collider2D)
	{
		Collider2D->SetOwnerObjectScale(this->GetOwner()->GetComponent<CTransform>(eComponentType::Transform)->GetScale());
		ColliderList.push_back(Collider2D);
	}

	CCollider2D* GetCollider(eCollideType type)
	{
		for (int i = 0; i < ColliderList.size(); i++)
		{
			if (ColliderList[i]->GetCollideType() == type)
			{
				return ColliderList[i];
			}
		}
		return nullptr;
	}

	vector<CCollider2D*>& GetColliderList()
	{
		return ColliderList;
	}
};

