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
	std::map<UINT, vector<eGateDirection>> mmGateList; // mvMapList 의 각 요소(map) 이 가지고 있는 Gate 목록, 이때 key 가 되는 UINT 는 Vector2.x *10 + Vector2.y + 1 의 결과 값이다.
	std::map<UINT, sObjectOnMap> mmObjectList; // mvMapList 의 각 요소(map) 이 가지고 있는 object 목록
	std::map<UINT, vector<sColliderOnMap>> mmColliderList; // map num, ColliderData



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
	void SetColliderList();
	vector<sColliderOnMap> GetColliderData(UINT mapNum);


	UINT GetMapListSize() { return mvMapList.size(); }
	Vector2 GetMapPos(UINT mapNum);
	vector<eGateDirection> GetDoorList(UINT mapNum);



};