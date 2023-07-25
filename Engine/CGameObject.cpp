#include "CGameObject.h"

CGameObject::CGameObject()
	: mState(eState::Active)
	, mCurBehave(eBehave::Idle)
	, mPrevBehave(eBehave::Idle)
	, mDirection(eDirection::Down)
{
	AddComponent<CTransform>();
}

CGameObject::~CGameObject()
{
	for (CComponent* comp : mComponent)
	{
		if (comp == nullptr)
		{
			continue;
		}
		delete comp;
		comp = nullptr;
	}
}

void CGameObject::Initialize()
{
	for (CComponent* comp : mComponent)
	{
		comp->Initialize();
	}
}

void CGameObject::Update()
{
	for (CComponent* comp : mComponent)
	{
		comp->Update();
	}
}

void CGameObject::LateUpdate()
{
	for (CComponent* comp : mComponent)
	{
		comp->LateUpdate();
	}
}

void CGameObject::Render()
{
	for (CComponent* comp : mComponent)
	{
		comp->Render();
	}
}
