#include "CDungeonMgr.h"
#include <random>

CDungeonMgr::CDungeonMgr()
{
	// center(3.3) �� ������ ����� �� �ִ� �ֺ� map
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
				//mapList.clear();
				if (i == 0)
				{
					mapList.push_back(Vector2(3, 3));
				}
				mStepConnectedMapList.insert(make_pair(i, mapList));
			}

			//// 3.3 �� ����� ���� ����
			//for (int i = 0; i < 4; i++)
			//{
			//	Vector2 centerVec = Vector2(3, 3);

			//	// (3,3)�� ���� ���ɼ��� �ִ� ���� ��ġ
			//	Vector2 mapVec = Vector2(centerVec.x + mAroundStardardArray[i].x, centerVec.y + mAroundStardardArray[i].y);

			//	if (std::find(vRandomMapList.begin(), vRandomMapList.end(), mapVec) != vRandomMapList.end())
			//	{
			//		int listIndex = std::find(vRandomMapList.begin(), vRandomMapList.end(), mapVec) - vRandomMapList.begin();

			//		// vMapList �� �����ϴ� 3.3 �� ���ᱭ ���� mvMapList �� �����Ѵ�.
			//		mvMapList.push_back(vRandomMapList[listIndex]);
			//	}
			//}

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
				// �̸� ���� mvMapList �� vRandomMapList ���� (3,3) �� ����� ��ǥ�� ����ȴ�.
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

			//// 3.3 �� ����� ���� 3�� �̻� �����ϴ� ���� ���� Ȯ��
			//if (vRandomMapList.size() >= 3)
			//{
			//	// (3,3) �� ������� ���� map �� mvMapList ���� �����Ѵ�.

			//	// 1. (3.3) �� ���������� ����� map �˻�
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
			//else //3.3 �� ����� ���� 2�� �̻� �������� �ʴ� ��� ó������ �ٽ� map �� �����Ѵ�.
			//{
			//	mvMapList.clear();
			//}

		}
	}




}

void CDungeonMgr::SetGateList()
{
	// 1. �� mvList �� �ֺ� map �� �����ϴ��� �ľ��Ѵ�.
	for (int i = 0; i < mvMapList.size(); i++)
	{
		mvMapList[0];
	}
	
}
