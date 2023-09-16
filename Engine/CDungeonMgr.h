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
	std::map<Vector2,vector<eGateDirection>> mmGateList; // mvMapList 의 각 요소(map) 이 가지고 있는 Gate 목록

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

