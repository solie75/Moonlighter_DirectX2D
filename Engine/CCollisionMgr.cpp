#include "CCollisionMgr.h"
#include "CGameObject.h"


CCollisionMgr::CCollisionMgr()
{
}

CCollisionMgr::~CCollisionMgr()
{
}

void CCollisionMgr::Update()
{
	for (UINT column = 0; column < (UINT)eLayerType::End; column++)
	{
		for (UINT row = 0; row < (UINT)eLayerType::End; row++)
		{
			if (mMatrix[column][row] == true)
			{
				ObjectCollision((eLayerType)column, (eLayerType)row);
			}
		}
	}
}

void CCollisionMgr::LateUpdate()
{
	for (UINT column = 0; column < (UINT)eLayerType::End; column++)
	{
		for (UINT row = 0; row < (UINT)eLayerType::End; row++)
		{
			if (mMatrix[column][row] == true)
			{
				DecreaseDeadObject((eLayerType)column, (eLayerType)row);
			}
		}
	}
}

void CCollisionMgr::DecreaseDeadObject(eLayerType leftLayer, eLayerType rightLayer)
{
	const std::vector<CGameObject*>& lefts
		= CSceneMgr::GetInst()->GetActiveScene()->GetLayer(leftLayer).GetGameObjects();

	const std::vector<CGameObject*>& rights =
		CSceneMgr::GetInst()->GetActiveScene()->GetLayer(rightLayer).GetGameObjects();

	for (CGameObject* leftObj : lefts)
	{
		for (CGameObject* rightObj : rights)
		{
			CCollider2D* leftCol = leftObj->GetComponent<CCollider2D>(eComponentType::Collider2D);
			CCollider2D* rightCol = rightObj->GetComponent<CCollider2D>(eComponentType::Collider2D);

			if (leftCol != nullptr && rightCol != nullptr)
			{
				if (leftObj->GetState() == CGameObject::eObjectState::Dead)
				{
					rightCol->OnCollisionExit(leftCol);
				}
				if (rightObj->GetState() == CGameObject::eObjectState::Dead)
				{
					leftCol->OnCollisionExit(rightCol);
				}
			}
		}
	}
}



void CCollisionMgr::ObjectCollision(eLayerType leftLayer, eLayerType rightLayer)
{
	const std::vector<CGameObject*>& lefts
	 = CSceneMgr::GetInst()->GetActiveScene()->GetLayer(leftLayer).GetGameObjects();

	const std::vector<CGameObject*>& rights =
	CSceneMgr::GetInst()->GetActiveScene()->GetLayer(rightLayer).GetGameObjects();

	for (CGameObject* leftObj : lefts)
	{
		CCollider2D* leftCol = leftObj->GetComponent<CCollider2D>(eComponentType::Collider2D);

		if (leftCol == nullptr || leftObj->GetState() != CGameObject::eObjectState::Active)
		{
			continue;
		}

		for (CGameObject* rightObj : rights)
		{
			CCollider2D* rightCol = rightObj->GetComponent<CCollider2D>(eComponentType::Collider2D);

			if (leftObj == rightObj)
			{
				continue;
			}
			if (rightCol == nullptr || rightObj->GetState() != CGameObject::eObjectState::Active)
			{
				continue;
			}

			ColliderCollision(leftCol, rightCol);
		}
	}
}

void CCollisionMgr::ColliderCollision(CCollider2D* leftCol, CCollider2D* rightCol)
{
	if (Intersect(leftCol, rightCol))
	{ // 두 충돌 체가 충돌한 경우
		if (leftCol->FindColliderID(rightCol->GetColliderID()) == true) // 이미 leftCol 에 RightCol 의 정보가 존재한다면
		{
			leftCol->OnCollisionStay(rightCol);
		}
		else // leftCol 에 rightCol 의 정보가 없다면
		{
			leftCol->OnCollisionEnter(rightCol);
		}

		if (rightCol->FindColliderID(leftCol->GetColliderID()) == true) // 이미 RightCol 에 leftCol 의 정보가 존재한다면
		{
			rightCol->OnCollisionStay(leftCol);
		}
		else // rightCol 에 leftCol 의 정보가 없다면
		{
			rightCol->OnCollisionEnter(leftCol);
		}
	}
	else
	{ // 현재 충돌 중이 아닌 경우
		if (leftCol->FindColliderID(rightCol->GetColliderID()) == true)
		{
			leftCol->OnCollisionExit(rightCol);
		}
		else
		{
			return;
		}

		if (rightCol->FindColliderID(leftCol->GetColliderID()) == true)
		{
			rightCol->OnCollisionExit(leftCol);
		}
		else
		{
			return;
		}
	}
}

bool CCollisionMgr::Intersect(CCollider2D* leftCol, CCollider2D* rightCol)
{
	// Rect vs Rect 
	// 0 --- 1
	// |     |
	// 3 --- 2
	Vector3 arrLocalPos[4] =
	{
		Vector3(-0.5f, 0.5f, 0.0f),
		Vector3(0.5f, 0.5f, 0.0f),
		Vector3(0.5f, -0.5f, 0.0f),
		Vector3(-0.5f, -0.5f, 0.0f)
	};

	CTransform* leftTr = leftCol->GetOwner()->GetComponent <CTransform>(eComponentType::Transform);
	CTransform* rightTr = rightCol->GetOwner()->GetComponent<CTransform>(eComponentType::Transform);

	Matrix leftMatrix = leftTr->GetWorldMatrix(); // 월드 변환
	Matrix rightMatrix = rightTr->GetWorldMatrix();

	Vector3 leftScale = Vector3(leftCol->GetSize().x, leftCol->GetSize().y, 1.0f);
	Matrix  leftScaleMatrix = Matrix::CreateScale(leftScale);
	leftMatrix *= leftScaleMatrix; // 월드 변환에 충돌체의 크기 적용

	Vector3 rightScale = Vector3(rightCol->GetSize().x, rightCol->GetSize().y, 1.0f);
	Matrix rightScaleMatrix = Matrix::CreateScale(rightScale);
	rightMatrix *= rightScaleMatrix;
	
	// 분리축 배열
	Vector3 Axis[4] = {};

	// 두 충돌체의 1번과 3번 꼭짓점 벡터를 월드 변환 계산한다.
	Axis[0] = Vector3::Transform(arrLocalPos[1], leftMatrix);
	Axis[1] = Vector3::Transform(arrLocalPos[3], leftMatrix);
	Axis[2] = Vector3::Transform(arrLocalPos[1], rightMatrix);
	Axis[3] = Vector3::Transform(arrLocalPos[3], rightMatrix);
	
	// 월드 변환 적용된 1번과 3번 에 월드 변환 적용된 0을 뺌으로서
	// 0번 꼭짓점에서 1과 3번 꼭짓점으로의 벡터가 완성된다.
	Axis[0] -= Vector3::Transform(arrLocalPos[0], leftMatrix);
	Axis[1] -= Vector3::Transform(arrLocalPos[0], leftMatrix);
	Axis[2] -= Vector3::Transform(arrLocalPos[0], rightMatrix);
	Axis[3] -= Vector3::Transform(arrLocalPos[0], rightMatrix);


	// 2차원에서의 충돌을 계산하기 위해서 z 값을 0.0f 으로 통일한다.
	for (size_t i = 0; i < 4; i++)
	{
		Axis[i].z = 0.0f;
	}
	
	// 두 충돌체의 중심 사이의 거리
	Vector3 vDist = leftTr->GetColliderPosition() - rightTr->GetColliderPosition();
	vDist.z = 0.0f;

	Vector3 vDistBetweenCols = vDist;

	for (size_t i = 0; i < 4; i++)
	{
		// 기준이 되는 분리축의 정규화
		Vector3 vAxis = XMVector3Normalize(Axis[i]);

		float projLength = 0.0f;
		for (size_t j = 0; j < 4; j++)
		{
			// 정규화된 분리축에 각 벡터(0->1 또는 3)들을 투영한 사영길이를 구하고 2 로 나눈다.
			// 구해진 사영길이들을 모두 더한다.
			projLength += fabsf(Axis[j].Dot(vAxis) / 2.0f);
		}

		// 위의 사영길이 더한것과 두 충돌체 사이의 거리의 사영길이를 비교한다.
		if (projLength <= fabsf(vDistBetweenCols.Dot(vAxis)))
		{
			// 하나의 분리축의 경우라도 사영길이 더한것보다 두 충돌체의 거리의 사영길이가 더 큰경우
			// 즉, 하나의 분리축으로 두 도형을 사영했을 때 빈 공간이 있는 경우 충돌하지 않았다.
			return false;
		}
	}

	if (leftCol->GetOwner()->GetName() == L"Boss3_Head" || rightCol->GetOwner()->GetName() == L"Boss3_Head")
	{
		int a = 0;
	}

	return true;
}

void CCollisionMgr::SetCollideLayer(eLayerType leftLayer, eLayerType rightLayer, bool enable)
{
	UINT row = -1;
	UINT col = -1;

	UINT iLeft = (UINT)leftLayer;
	UINT iRight = (UINT)rightLayer;

	if (iLeft <= iRight)
	{
		row = iLeft;
		col = iRight;
	}
	else
	{
		row = iRight;
		col = iLeft;
	}

	// 일반적으로 2차원 공간은 가로X세로 로 표기하지만 배열로 만들 때는 세로X가로로 표기한다.
	mMatrix[col][row] = enable;
}

void CCollisionMgr::Clear()
{
	mMatrix->reset();
}

