#include "CDungeonMgr.h"
#include <random>

CDungeonMgr::CDungeonMgr()
{
	// center(3.3) 에 문으로 연결될 수 있는 주변 map
	mvAroundCenterList.push_back(Vector2(2,3));
	mvAroundCenterList.push_back(Vector2(4,3));
	mvAroundCenterList.push_back(Vector2(3,2));
	mvAroundCenterList.push_back(Vector2(3,4));

	mAroundStardardArray[0] = Vector2(-1, 0);
	mAroundStardardArray[1] = Vector2(1, 0);
	mAroundStardardArray[2] = Vector2(0, -1);
	mAroundStardardArray[3] = Vector2(0, 1);
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
				//mapList.clear();
				if (i == 0)
				{
					mapList.push_back(Vector2(3, 3));
				}
				mStepConnectedMapList.insert(make_pair(i, mapList));
			}

			//// 3.3 과 연결된 맵을 저장
			//for (int i = 0; i < 4; i++)
			//{
			//	Vector2 centerVec = Vector2(3, 3);

			//	// (3,3)과 연결 가능성이 있는 맵의 위치
			//	Vector2 mapVec = Vector2(centerVec.x + mAroundStardardArray[i].x, centerVec.y + mAroundStardardArray[i].y);

			//	if (std::find(vRandomMapList.begin(), vRandomMapList.end(), mapVec) != vRandomMapList.end())
			//	{
			//		int listIndex = std::find(vRandomMapList.begin(), vRandomMapList.end(), mapVec) - vRandomMapList.begin();

			//		// vMapList 에 존재하는 3.3 과 연결괸 맵을 mvMapList 에 저장한다.
			//		mvMapList.push_back(vRandomMapList[listIndex]);
			//	}
			//}

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
						Vector2 mapVec = Vector2((curIter->second)[i].x + mAroundStardardArray[j].x, (curIter->second)[i].y + mAroundStardardArray[j].y);
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
				return;
			}
			
			{
				mvMapList.clear();
				vRandomMapList.clear();
			}

			//// 3.3 과 연결된 맵이 3개 이상 존재하는 지에 대한 확인
			//if (vRandomMapList.size() >= 3)
			//{
			//	// (3,3) 과 연결되지 않은 map 을 mvMapList 에서 삭제한다.

			//	// 1. (3.3) 와 일차적으로 연결된 map 검색
			//	for (int i = 0; i < mvMapList.size(); i++)
			//	{
			//		if(std::find(mvMapList.begin(), mvMapList.end(), Vector2(mapVector[i]))
			//	}

			//	if (std::find(mvMapList.begin(), mvMapList.end(), ))
			//	{

			//	}

			//	for (UINT i = 0; i < mvMapList.size(); i++)
			//	{
			//		bool vConnected = false;
			//		for (UINT j = 0; j < 4; j++)
			//		{
			//			std::find(mvMapList.begin(), mvMapList.end(), )
			//		}
			//		mvMapList[i].x
			//	}
			//}
			//else //3.3 과 연결된 맵이 2개 이상 존재하지 않는 경우 처음주터 다시 map 을 구축한다.
			//{
			//	mvMapList.clear();
			//}

		}
	}




}

void CDungeonMgr::SetGateList()
{
	// 1. 각 mvList 에 주변 map 이 존재하는지 파악한다.
	for (int i = 0; i < mvMapList.size(); i++)
	{
		mvMapList[0];
	}
	
}
