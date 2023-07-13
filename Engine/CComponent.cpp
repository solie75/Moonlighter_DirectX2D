#include "CComponent.h"

CComponent::CComponent(eComponentType type)
	: mType(type)
	, mOwner(nullptr)
{
}

CComponent::~CComponent()
{
}

void CComponent::Initialize()
{
}

void CComponent::Update()
{
}

void CComponent::LateUpdate()
{
}

void CComponent::Render()
{
}
