#include "CGolemSoldierScript.h"
#include "CKeyMgr.h"
#include "CColliderMgr.h"
#include <random>

CGolemSoldierScript::CGolemSoldierScript()
{
	mNaviScript = new CNaviScript;
	mbLockOn = false;
	mTargetPos = Vector2::Zero;
	mbMoving = false;
	pauseTime = 0.0f;
}

CGolemSoldierScript::~CGolemSoldierScript()
{
}

void CGolemSoldierScript::Initialize()
{
	/*Vector3 GetBackColSize = GetOwner()->GetComponent<CColliderMgr>(eComponentType::ColliderList)->GetCollider(eCollideType::Background)->GetColliderScale();
	mNaviScript->SetNodeSize(Vector2(GetBackColSize.x, GetBackColSize.y));*/

	SetOwnerOnMonsterScript(GetOwner());
	CMonsterScript::Initialize();
	GetOwner()->SetHP(100);
	
	GetMonsterState()->SetState(eState::Idle);

	CColliderMgr* golemSoldierCdList = GetOwner()->AddComponent<CColliderMgr>(eComponentType::ColliderList);

	CCollider2D* golemSoldierCDforBackground = new CCollider2D;
	golemSoldierCDforBackground->SetName(L"golemSoldierCDforBackground");
	golemSoldierCDforBackground->SetCollideType(eCollideType::Background);

	golemSoldierCDforBackground->SetOffset(Vector2(0.0f, -0.2f));
	golemSoldierCdList->AddCollider(golemSoldierCDforBackground);
	golemSoldierCDforBackground->SetSize(Vector2(0.4f, 0.1f));

	CCollider2D* golemSoldierCDforHit = new CCollider2D;
	golemSoldierCDforHit->SetName(L"golemSoldierCDforHit");
	golemSoldierCDforHit->SetCollideType(eCollideType::Hit);

	golemSoldierCDforHit->SetOffset(Vector2(0.0f, 0.0f));
	golemSoldierCdList->AddCollider(golemSoldierCDforHit);
	golemSoldierCDforHit->SetSize(Vector2(1.0f, 1.0f));

	CCollider2D* golemSoldierCdforDetection = new CCollider2D;
	golemSoldierCdforDetection->SetName(L"golemSoldierCdforDetection");
	golemSoldierCdforDetection->SetCollideType(eCollideType::Detection);

	golemSoldierCdforDetection->SetOffset(Vector2(0.0f, 0.0f));
	golemSoldierCdforDetection->SetSize(Vector2(3.0f, 3.0f));
	golemSoldierCdList->AddCollider(golemSoldierCdforDetection);
	
}

void CGolemSoldierScript::Update()
{
	eState curState = GetMonsterState()->GetCurState();
	eState prevState = GetMonsterState()->GetPrevState();

	std::wstring aniName = L"Monster_GolemSoldier_";

	CAnimator* thisAt = GetOwner()->GetComponent<CAnimator>(eComponentType::Animator);
	CTransform* thisTr = GetOwner()->GetComponent<CTransform>(eComponentType::Transform);
	Vector3 thisPos = thisTr->GetPosition();

	CColliderMgr* thisColList = GetOwner()->GetComponent<CColliderMgr>(eComponentType::ColliderList);

	if (curState == eState::Idle)
	{
		CCollider2D* CdforHit = thisColList->GetCollider(eCollideType::Hit);
		if (CdforHit->GetColliderData(eLayerType::Player).id != 0)
		{
			GetMonsterState()->SetState(eState::Attack);
			if (CdforHit->GetColliderData(eLayerType::Player).pos.x > thisPos.x)
			{
				GetMonsterAimSight()->SetSight(CAimSight::eSight::Right);
			}
			else
			{
				GetMonsterAimSight()->SetSight(CAimSight::eSight::Left);
			}
		}

		if (prevState != eState::Idle)
		{
			thisTr->SetScale(Vector3(0.5f, 0.7f, 0.0f));
			aniName += L"Floating_";
			aniName += GetGolemSoldierSightStr(GetMonsterAimSight()->GetCurSight());

			thisAt->PlayAnimation(aniName, true);
			GetMonsterState()->SetState(eState::Idle);
		}


		// Lock on 된 대상자가 없을 때
		if (playerCol == nullptr)
		{
			CCollider2D* golemDetectionCol = thisColList->GetCollider(eCollideType::Detection);

			if (mbMoving == false)
			{
				pauseTime += CTimeMgr::GetInst()->GetDeltaTime(); // 멈춰있는 시간
				if (pauseTime > 1.0f)
				{
					int randomInt_X = 0;
					int randomInt_Y = 0;

					while (true)
					{
						std::random_device rd;
						std::mt19937 generator(rd());

						int min_value = 5;
						int max_value = 30;
						std::uniform_int_distribution<int> distribution(min_value, max_value);

						randomInt_X = distribution(generator);
						randomInt_Y = distribution(generator);

						if (mNaviScript->IsCollideNode(randomInt_X * 100 + randomInt_Y) == false)
						{
							break;
						}
					}

					mNaviScript->WayNodeListClear();
					CCollider2D* golemBackCol = thisColList->GetCollider(eCollideType::Background);
					Vector3 golemBackColPos = golemBackCol->GetColliderPosition();

					// golemsoldier 가 현재 위치한 Node 의 아이디를 지정한다.
					mNaviScript->SetStartNode(Vector2(golemBackColPos.x, golemBackColPos.y));
					mNaviScript->SetGoalNode(randomInt_X * 100 + randomInt_Y);
					// 이 부분에서 A* 알고리즘 구현 (NodeList 구현)
					mNaviScript->AStarNodeListClear();
					UINT stepNum = mNaviScript->SetWayNodeList();
					
					mNaviScript->SetAStarNodeList(stepNum);
					mbMoving = true;
					pauseTime = 0.0f;
				}
			}
			else // mbMoving == ture
			{
				CCollider2D* golemBackCol = thisColList->GetCollider(eCollideType::Background);
				Vector3 golemBackColPos = golemBackCol->GetColliderPosition();
				// calculate Moveing 
				Vector2 direction = mNaviScript->GetMovingDirection(Vector2(golemBackColPos.x, golemBackColPos.y));
				if (direction == Vector2(0.0f, 0.0f))
				{ // goalNode 에 도달한 경우
					mbMoving = false;
					mNaviScript->WayNodeListClear();
				}
				float speed = 0.005f;
				thisTr->SetPosition(thisPos.x + (direction.x * speed), thisPos.y + (direction.y * speed), 0.0f);
			}
			
			

			if (golemDetectionCol->GetColliderData(eLayerType::Player).id != 0)
			{
				playerCol = golemDetectionCol->GetColliderData(eLayerType::Player).otherCol;
				mbLockOn = true;
				
			}
			else
			{
				// 여기에서 BackCol 과 충돌하지 않은 node 를 하나 지정하며 움직인다. 목적지에 도달하면 몇초간 멈췄다가 다시 움직인다.
			}
		}
		else // 대상자가 lock on 되었을 때
		{
			// 노드 리스트 초기화
			mNaviScript->WayNodeListClear();

			// 현재 GolemSoldier 가 위치한 노드의 정보를 초기화
			CCollider2D* golemBackCol = thisColList->GetCollider(eCollideType::Background);
			Vector3 golemBackColPos = golemBackCol->GetColliderPosition();

			// golemsoldier 가 현재 위치한 Node 의 아이디를 지정한다.
			mNaviScript->SetStartNode(Vector2(golemBackColPos.x, golemBackColPos.y));
			mNaviScript->SetGoalNode(Vector2(playerCol->GetColliderPosition().x, playerCol->GetColliderPosition().y));
			// 이 부분에서 A* 알고리즘 구현 (NodeList 구현)

			mNaviScript->AStarNodeListClear();
			UINT stepNum = mNaviScript->SetWayNodeList();
			mNaviScript->SetAStarNodeList(stepNum);

			Vector2 direction = mNaviScript->GetMovingDirection(Vector2(golemBackColPos.x, golemBackColPos.y));
			float speed = 0.01f;
			thisTr->SetPosition(thisPos.x + (direction.x * speed), thisPos.y + (direction.y * speed), 0.0f);
		}

		
	}
	else if (curState == eState::Attack)
	{
		Vector3 sclae = thisTr->GetScale();
		if (prevState != eState::Attack)
		{
			
			switch (GetMonsterAimSight()->GetCurSight())
			{
			case CAimSight::eSight::Down :
				thisTr->SetPosition(Vector3(thisPos.x, thisPos.y - 0.05f, 0.0f));
				thisTr->SetScale(Vector3(sclae.x, 1.0f, 0.0f));
				break;
			case CAimSight::eSight::Left :
				thisTr->SetPosition(Vector3(thisPos.x - 0.17f, thisPos.y, 0.0f));
				thisTr->SetScale(Vector3(0.85f, 0.75f, 0.0f));
				break;
			case CAimSight::eSight::Right :
				thisTr->SetPosition(Vector3(thisPos.x + 0.17f, thisPos.y, 0.0f));
				thisTr->SetScale(Vector3(0.85f, 0.75f, 0.0f));
				break;
			case CAimSight::eSight::Up :
				thisTr->SetPosition(Vector3(thisPos.x, thisPos.y + 0.15f, 0.0f));
				thisTr->SetScale(Vector3(sclae.x, 1.0f, 0.0f));
				break;
			}
			aniName += L"Attack_";
			aniName += GetGolemSoldierSightStr(GetMonsterAimSight()->GetCurSight());
			thisAt->PlayAnimation(aniName, false);
			GetMonsterState()->SetState(eState::Attack);
		}
		else
		{
			if (thisAt->GetCurAnimation()->IsComplete() == true)
			{
				switch (GetMonsterAimSight()->GetCurSight())
				{
				case CAimSight::eSight::Down:
					thisTr->SetPosition(Vector3(thisPos.x, thisPos.y + 0.05f, 0.0f));
					break;
				case CAimSight::eSight::Left:
					thisTr->SetPosition(Vector3(thisPos.x + 0.17f, thisPos.y, 0.0f));
					break;
				case CAimSight::eSight::Right:
					thisTr->SetPosition(Vector3(thisPos.x - 0.17f, thisPos.y, 0.0f));
					break;
				case CAimSight::eSight::Up:
					thisTr->SetPosition(Vector3(thisPos.x, thisPos.y - 0.15f, 0.0f));
					break;
				}
				GetMonsterState()->SetState(eState::Idle);
			}
		}
	}
	

	if (GetMonsterAimSight()->GetCurSight() != GetMonsterAimSight()->GetPrevSight())
	{
		aniName += L"Floating_";
		aniName += GetGolemSoldierSightStr(GetMonsterAimSight()->GetCurSight());

		thisAt->PlayAnimation(aniName, true);
		GetMonsterAimSight()->SetSight(GetMonsterAimSight()->GetCurSight());
	}

	//if (curState == eState::Idle)
	//{
	//	// 어떤 원인으로 시야가 변경되면 변경된 시야에 맞게 애니메이션 재생
	//	if (GetMonsterAimSight()->GetCurSight() != GetMonsterAimSight()->GetPrevSight())
	//	{
	//		aniName += L"Floating_";
	//		aniName += GetGolemSoldierSightStr(GetMonsterAimSight()->GetCurSight());

	//		thisAt->PlayAnimation(aniName, true);
	//		GetMonsterAimSight()->SetSight(GetMonsterAimSight()->GetCurSight());
	//	}
	//	// 움직임 로직
	//	// 타겟팅할 대상이 존재 하지 않을 때의 몬스터의 움직임 로직
	//	// grid 로 갈수있는 곳을 지정하고 최단거리로 이동한다.
	//	// 중간에 플레이어를 만나 타겟팅 모드가 되면 최단거리의 대상이 플레이어로 고정된다.
	//	// 우선 키 버튼으로 정상적으로 움직이는 것을 확인해 보자
	//}
	//else if (curState == eState::Attack)
	//{
	//	if (prevState != eState::Attack)
	//	{
	//		GetMonsterState()->SetState(eState::Attack);
	//		aniName += L"Attack_";
	//		aniName += GetGolemSoldierSightStr(GetMonsterAimSight()->GetCurSight());
	//		thisAt->PlayAnimation(aniName, false);
	//	}
	//	else if (prevState == eState::Attack && thisAt->GetCurAnimation()->IsComplete() == true)
	//	{
	//		GetMonsterState()->SetState(eState::Idle);
	//	}
	//}

	CMonsterScript::Update();
}

void CGolemSoldierScript::LateUpdate()
{
	CMonsterScript::LateUpdate();
}

std::wstring CGolemSoldierScript::GetGolemSoldierSightStr(CAimSight::eSight sight)
{
	switch (sight)
	{
	case CAimSight::eSight::Down:
		return L"Down";
	case CAimSight::eSight::Right:
		return L"Right";
	case CAimSight::eSight::Left:
		return L"Left";
	case CAimSight::eSight::Up:
		return L"Up";
	}
}