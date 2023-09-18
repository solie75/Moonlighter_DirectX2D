#pragma once

#include "CSingleton.h"
#include "Header.h"

class CDungeonMgr
	: public CSingleton<CDungeonMgr>
{
	enum class eGateDirection
	{
		Left,
		Right,
		Up,
		Down,
		End,
	};

private:
	vector<Vector2> mvMapList;
	vector<Vector2> mvAroundCenterList;
	Vector2 mAroundStardardArray[4];
	std::map<UINT, vector<eGateDirection>> mmGateList; // mvMapList 의 각 요소(map) 이 가지고 있는 Gate 목록, 이때 key 가 되는 UINT 는 Vector2.x *10 + Vector2.y + 1 의 결과 값이다.

public :
	CDungeonMgr();
	~CDungeonMgr();

	void Init();
	void Update();
	void LateUpdate();
	void Render();

	void CreateMap();
	void SetGateList();

	UINT GetMapListSize() { return mvMapList.size(); }
	Vector2 GetMapPos(UINT num);
};

