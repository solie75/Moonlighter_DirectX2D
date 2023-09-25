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
		// �������� (1,1) ���� (5,5) ������ ��ǥ ����
		std::random_device rd;
		std::mt19937 generator(rd());

		int min_value = 1;
		int max_value = 5;
		std::uniform_int_distribution<int> distribution(min_value, max_value);

		int randomInt_X = distribution(generator);
		int randomInt_Y = distribution(generator);

		Vector2 mapElement = Vector2(randomInt_X, randomInt_Y);

		// ������ ���� ��ǥ�� vMapList ���� �˻��Ͽ� ���ٸ� �߰�
		if (std::find(vRandomMapList.begin(), vRandomMapList.end(), mapElement) == vRandomMapList.end())
		{
			vRandomMapList.push_back(Vector2(randomInt_X, randomInt_Y));
		}

		// mbMapList �� �ִ� ������ �� ����
		if (vRandomMapList.size() == 12)
		{
			// (3,3) �� �������� �󸶴� ������ �ִ����� ���� �ܰ躰 map List
			std::map<UINT, vector<Vector2>> mStepConnectedMapList;

			// map �� ��ü���� �Ը� ���Ѵ�.
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

			// mvMapList �� �����ϴ� ��ҵ� ������ �ֺ��� ����� map �� vMapList ���� �˻��Ͽ� mvMapList �� �����Ѵ�.
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
				// �̸� ���� mvMapList �� vRandomMapList ���� (3,3) �� ����� ��ǥ�� ����ȴ�.
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
	// 1. �� mvList �� �ֺ� map �� �����ϴ��� �ľ��Ѵ�.
	for (int i = 0; i < mvMapList.size(); i++)
	{
		for (int j = 0; j < 4; j++)
		{
			// �����ϴ��� �˻��� ����� �Ǵ� ��
			Vector2 mapVec = Vector2(mvMapList[i].x + mAroundStandardArray[j].x, mvMapList[i].y + mAroundStandardArray[j].y);

			// map�� mvMaplist �� �����ϴ��� �˻�
			if (std::find(mvMapList.begin(), mvMapList.end(), mapVec) != mvMapList.end())
			{
				// �����ϴ� ���
				std::map<UINT, vector<eGateDirection>>::iterator iter = mmGateList.find(mvMapList[i].x*10 + mvMapList[i].y);
				if (iter == mmGateList.end())
				{
					// �� map �� ���� Gate ����
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

vector<CDungeonMgr::sColliderOnMap> CDungeonMgr::GetColliderData(UINT mapNum)
{
	std::map<UINT, vector<sColliderOnMap>>::iterator iter = mmColliderList.find(mapNum);
	if (iter != mmColliderList.end())
	{
		return iter->second;
	}

	vector<CDungeonMgr::sColliderOnMap> dummy;

	return dummy;
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
