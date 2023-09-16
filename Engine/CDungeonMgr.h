#pragma once

#include "CSingleton.h"
#include "Header.h"

class CDungeonMgr
	: public CSingleton<CDungeonMgr>
{
	enum class eGateDirection
	{
		Down,
		Left,
		Right,
		Up,
		End,
	};

private:
	vector<Vector2> mvMapList;
	vector<Vector2> mvAroundCenterList;
	Vector2 mAroundStardardArray[4];
	std::map<UINT,vector<eGateDirection>> mmGateList; // mvMapList �� �� ���(map) �� ������ �ִ� Gate ���

public :
	CDungeonMgr();
	~CDungeonMgr();

	void Init();
	void Update();
	void LateUpdate();
	void Render();

	void CreateMap();
	void SetGateList();
};

