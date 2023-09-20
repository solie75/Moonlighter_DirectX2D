#pragma once

#include "CSingleton.h"
#include "Header.h"
#include "CAimSight.h"

class CDungeonMgr
	: public CSingleton<CDungeonMgr>
{
public:
	enum class eGateDirection
	{
		Left,
		Right,
		Up,
		Down,
		End,
	};

	struct sGateLinkData
	{
		Vector2 DestinationGatePos;
		eGateDirection DestinationGatesDirection;
	};

private:
	vector<Vector2> mvMapList;
	vector<Vector2> mvAroundCenterList;
	Vector2 mAroundStandardArray[4];
	std::map<UINT, vector<eGateDirection>> mmGateList; // mvMapList 의 각 요소(map) 이 가지고 있는 Gate 목록, 이때 key 가 되는 UINT 는 Vector2.x *10 + Vector2.y + 1 의 결과 값이다.
	std::map<UINT, CAimSight::eSight> mmGateLinkData; // 하나의 door 가 어디에 연결되어 있는지 연결된 door 가 바라보는 방향은 어디인지 

public :
	CDungeonMgr();
	~CDungeonMgr();

	void Init();
	void Update();
	void LateUpdate();
	void Render();

	void CreateMap();
	void SetGateList();
	void SetGateLinkData();

	UINT GetMapListSize() { return mvMapList.size(); }
	Vector2 GetMapPos(UINT mapNum);
	vector<eGateDirection> GetDoorList(UINT mapNum);
	
};