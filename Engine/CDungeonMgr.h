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
	std::map<UINT, vector<eGateDirection>> mmGateList; // mvMapList �� �� ���(map) �� ������ �ִ� Gate ���, �̶� key �� �Ǵ� UINT �� Vector2.x *10 + Vector2.y + 1 �� ��� ���̴�.
	std::map<UINT, CAimSight::eSight> mmGateLinkData; // �ϳ��� door �� ��� ����Ǿ� �ִ��� ����� door �� �ٶ󺸴� ������ ������� 

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