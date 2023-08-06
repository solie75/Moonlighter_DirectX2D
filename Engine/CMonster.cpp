#include "CMonster.h"

CMonster::CMonster()
	: mCreatureType(eCreatureType::Monster)
{
}

CMonster::~CMonster()
{
}

void CMonster::Initialize()
{
	CGameObject::Initialize();
}

void CMonster::Update()
{
	CGameObject::Update();
}

void CMonster::LateUpdate()
{
	CGameObject::LateUpdate();
}

void CMonster::Render()
{
	CGameObject::Render();
}
