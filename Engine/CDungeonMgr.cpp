#include "CDungeonMgr.h"
#include <random>

CDungeonMgr::CDungeonMgr()
{
	mAroundStandardArray[0] = Vector2(-1, 0);
	mAroundStandardArray[1] = Vector2(1, 0);
	mAroundStandardArray[2] = Vector2(0, -1);
	mAroundStandardArray[3] = Vector2(0, 1);

	for (UINT i = 1; i < 6; i++)
	{
		vector<sColliderOnMap> initVector;
		mmColliderList.insert(std::make_pair(i, initVector));
	}
}

CDungeonMgr::~CDungeonMgr()
{
}

void CDungeonMgr::Init()
{
}

void CDungeonMgr::Update()
{
}

void CDungeonMgr::LateUpdate()
{
}

void CDungeonMgr::Render()
{
}

void CDungeonMgr::CreateMap()
{
	mvMapList.clear();
	
	vector<Vector2> vRandomMapList;
	vRandomMapList.push_back(Vector2(3, 3));
	
	while (true)
	{
		// 랜덤으로 (1,1) 부터 (5,5) 까지의 좌표 생성
		std::random_device rd;
		std::mt19937 generator(rd());

		int min_value = 1;
		int max_value = 5;
		std::uniform_int_distribution<int> distribution(min_value, max_value);

		int randomInt_X = distribution(generator);
		int randomInt_Y = distribution(generator);

		Vector2 mapElement = Vector2(randomInt_X, randomInt_Y);

		// 생성된 랜덤 좌표가 vMapList 에서 검색하여 없다면 추가
		if (std::find(vRandomMapList.begin(), vRandomMapList.end(), mapElement) == vRandomMapList.end())
		{
			vRandomMapList.push_back(Vector2(randomInt_X, randomInt_Y));
		}

		// mbMapList 의 최대 개수일 때 종료
		if (vRandomMapList.size() == 12)
		{
			// (3,3) 을 기준으로 얼마다 떨어져 있는지에 대한 단계별 map List
			std::map<UINT, vector<Vector2>> mStepConnectedMapList;

			// map 의 전체적인 규모를 정한다.
			int mapSize = 4;
			for (int i = 0; i < mapSize; i++)
			{
				vector<Vector2> mapList;
				if (i == 0)
				{
					mapList.push_back(Vector2(3, 3));
				}
				mStepConnectedMapList.insert(make_pair(i, mapList));
			}

			// mvMapList 에 존재하는 요소들 각각에 주변에 연결된 map 을 vMapList 에서 검색하여 mvMapList 에 저장한다.
			std::map<UINT, vector<Vector2>>::iterator prevIter;
			std::map<UINT, vector<Vector2>>::iterator curIter;
			std::map<UINT, vector<Vector2>>::iterator nextIter;

			for (int k = 0; k < mapSize-1; k++)
			{
				//int memberMapListSize = mvMapList.size();
				if (k > 0)
				{
					prevIter = mStepConnectedMapList.find(k - 1);
				}
				curIter = mStepConnectedMapList.find(k);
				nextIter = mStepConnectedMapList.find(k+1);
				for (int i = 0; i < curIter->second.size(); i++)
				{
					for (int j = 0; j < 4; j++)
					{
						Vector2 mapVec = Vector2((curIter->second)[i].x + mAroundStandardArray[j].x, (curIter->second)[i].y + mAroundStandardArray[j].y);
						if (std::find(vRandomMapList.begin(), vRandomMapList.end(), mapVec) != vRandomMapList.end())
						{
							if (k == 0)
							{
								mvMapList.push_back(mapVec);
								nextIter->second.push_back(mapVec);
							}
							else
							{
								if (std::find(prevIter->second.begin(), prevIter->second.end(), mapVec) == prevIter->second.end()
									&& std::find(nextIter->second.begin(), nextIter->second.end(), mapVec) == nextIter->second.end())
								{
									mvMapList.push_back(mapVec);
									nextIter->second.push_back(mapVec);
								}
							}
						}
					}
				}
				// 이를 통해 mvMapList 는 vRandomMapList 에서 (3,3) 과 연결된 자표만 저장된다.
			}

			std::map<UINT, vector<Vector2>>::iterator iter = mStepConnectedMapList.find(1);

			if (iter->second.size() >= 3 &&	mvMapList.size() > 8)
			{
				mvMapList.push_back(Vector2(3, 3));
				SetGateList();
				SetColliderList();
				mmColliderList;
				return;
			}
			{
				mvMapList.clear();
				vRandomMapList.clear();
			}
		}
	}
}

void CDungeonMgr::SetGateList()
{
	mmGateList.erase(mmGateList.begin(), mmGateList.end());
	// 1. 각 mvList 에 주변 map 이 존재하는지 파악한다.
	for (int i = 0; i < mvMapList.size(); i++)
	{
		for (int j = 0; j < 4; j++)
		{
			// 존재하는지 검색의 대상이 되는 맵
			Vector2 mapVec = Vector2(mvMapList[i].x + mAroundStandardArray[j].x, mvMapList[i].y + mAroundStandardArray[j].y);

			// map이 mvMaplist 에 존재하는지 검색
			if (std::find(mvMapList.begin(), mvMapList.end(), mapVec) != mvMapList.end())
			{
				// 존재하는 경우
				std::map<UINT, vector<eGateDirection>>::iterator iter = mmGateList.find(mvMapList[i].x*10 + mvMapList[i].y);
				if (iter == mmGateList.end())
				{
					// 각 map 에 대한 Gate 저장
					vector<eGateDirection> gateDirection;
					gateDirection.push_back((eGateDirection)j);
					mmGateList.insert(make_pair(mvMapList[i].x * 10 + mvMapList[i].y, gateDirection));
				}
				else
				{
					iter->second.push_back((eGateDirection)j);
				}
			}
		}
	}
}

void CDungeonMgr::SetObjectList(UINT mapNum)
{
	sObjectOnMap ObjectDataOnMap;

	SetMonsterList(ObjectDataOnMap, mapNum);
	SetColliderList();

	mmObjectList.insert(std::make_pair(mapNum, ObjectDataOnMap));
}

void CDungeonMgr::SetMonsterList(sObjectOnMap data, UINT mapNum)
{
	switch (mapNum)
	{
	case 1:
		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
		break;
	case 5:
		break;
	}
}

void CDungeonMgr::SetColliderList()
{
	std::filesystem::path dataFilePath = L"..\\Data\\Dungeon3MapColliderData.json";

	std::wifstream DataFile(dataFilePath);
	if(DataFile.is_open())
	{
		std::wstring line;
		int idNum = 1;
		int mapNum = 0;
		while (std::getline(DataFile, line))
		{
			
			std::wstring ColliderId = L"\"id\": ";
			ColliderId += std::to_wstring(idNum);

			if (line.find(ColliderId) != std::string::npos)
			{
				sColliderOnMap colliderData;

				std::getline(DataFile, line);
				if (line.find(L"\"Position\": ") != std::string::npos)
				{
					size_t startPos = line.find(L"[") + 1;
					size_t endPos = line.find(L"]");
					std::wstring numStr = line.substr(startPos, endPos - startPos);
					int PosX, PosY;
					swscanf_s(numStr.c_str(), L"%d, %d", &PosX, &PosY);
					colliderData.vColliderPos.x = PosX * 0.01f;
					colliderData.vColliderPos.y = PosY * 0.01f;
				}
				std::getline(DataFile, line);
				if (line.find(L"\"Quadrant\": ") != std::string::npos)
				{
					size_t startPos = line.find(L"[") + 1;
					size_t endPos = line.find(L"]");
					std::wstring numStr = line.substr(startPos, endPos - startPos);

					int quadrant;
					swscanf_s(numStr.c_str(), L"%d", &quadrant);
					switch (quadrant)
					{
					case 1 : 
						break;
					case 2:
						colliderData.vColliderPos.x *= -1;
						break;
					case 3:
						colliderData.vColliderPos.x *= -1;
						colliderData.vColliderPos.y *= -1;
						break;
					case 4:
						colliderData.vColliderPos.y *= -1;
						break;
					}
				}
				std::getline(DataFile, line);
				if (line.find(L"\"Scale\": ") != std::string::npos)
				{
					size_t startPos = line.find(L"[") + 1;
					size_t endPos = line.find(L"]");
					std::wstring numStr = line.substr(startPos, endPos - startPos);
					int ScaleX, ScaleY;
					swscanf_s(numStr.c_str(), L"%d, %d", &ScaleX, &ScaleY);
					colliderData.vColliderScale.x = ScaleX * 0.01f;
					colliderData.vColliderScale.y = ScaleY * 0.01f;
				}
				std::getline(DataFile, line);
				if (line.find(L"\"Type\": ") != std::string::npos)
				{
					size_t startPos = line.find(L"[") + 1;
					size_t endPos = line.find(L"]");
					std::wstring numStr = line.substr(startPos, endPos - startPos);

					int type;
					swscanf_s(numStr.c_str(), L"%d", &type);
					colliderData.ColliderType = (BackgroundColliderType)type;
				}
				std::getline(DataFile, line);
				if (line.find(L"\"MapNum\": ") != std::string::npos)
				{
					size_t startPos = line.find(L"[") + 1;
					size_t endPos = line.find(L"]");
					std::wstring numStr = line.substr(startPos, endPos - startPos);

					swscanf_s(numStr.c_str(), L"%d", &mapNum);

					std::map<UINT, vector<sColliderOnMap>>::iterator iter = mmColliderList.find(mapNum);
					iter->second.push_back(colliderData);
					idNum++;
				}
			}
		}
	}
}


Vector2 CDungeonMgr::GetMapPos(UINT mapNum)
{
	std::map<UINT, vector<eGateDirection>>::iterator iter = mmGateList.begin();
	for (int i = 0; i < mapNum; i++)
	{
		iter++;
	}
	Vector2 vec2;
	vec2.x = (iter->first) / 10;
	vec2.y = (iter->first) % 10;
	return vec2;
}

vector<CDungeonMgr::eGateDirection> CDungeonMgr::GetDoorList(UINT mapNum)
{
	std::map<UINT, vector<eGateDirection>>::iterator iter = mmGateList.begin();
	for (int i = 0; i < mapNum; i++)
	{
		iter++;
	}

	return iter->second;
};
