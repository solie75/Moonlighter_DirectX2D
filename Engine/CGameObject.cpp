#include "CGameObject.h"

CGameObject::CGameObject()
	: mState(eState::Active)
{
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
