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

	enum class BackgroundColliderType
	{
		Wall,
		Hole,
		End,
	};

	struct sColliderOnMap
	{
		Vector2 vColliderPos;
		Vector2 vColliderScale;
		BackgroundColliderType ColliderType;
	};

	struct sMonsterOnMap
	{
		Vector2 vMonsterScale;
		std::wstring sMonsterName;
	};

	struct sObjectOnMap
	{
		vector<sColliderOnMap> vColliderOnMap;
		vector<sMonsterOnMap> vMonsterOnMap;
	};

	

private:
	vector<Vector2> mvMapList;
	Vector2 mAroundStandardArray[4];
	std::map<UINT, vector<eGateDirection>> mmGateList; // mvMapList �� �� ���(map) �� ������ �ִ� Gate ���, �̶� key �� �Ǵ� UINT �� Vector2.x *10 + Vector2.y + 1 �� ��� ���̴�.
	std::map<UINT, sObjectOnMap> mmObjectList; // mvMapList �� �� ���(map) �� ������ �ִ� object ���
	std::map<UINT, vector<sColliderOnMap>> mmColliderList;



public :
	CDungeonMgr();
	~CDungeonMgr();

	void Init();
	void Update();
	void LateUpdate();
	void Render();

	void CreateMap();
	void SetGateList();
	void SetObjectList(UINT mapNum);
	void SetMonsterList(sObjectOnMap data, UINT mapNum);
	void SetColliderList(sObjectOnMap data, UINT mapNum);

	UINT GetMapListSize() { return mvMapList.size(); }
	Vector2 GetMapPos(UINT mapNum);
	vector<eGateDirection> GetDoorList(UINT mapNum);



};