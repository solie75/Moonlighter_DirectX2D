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

void CCollisionMgr::ObjectCollision(eLayerType leftLayer, eLayerType rightLayer)
{
	const std::vector<CGameObject*>& lefts = 
		CSceneMgr::GetInst()->GetActiveScene()->GetLayer(leftLayer).GetGameObjects();

	const std::vector<CGameObject*>& rights =
		CSceneMgr::GetInst()->GetActiveScene()->GetLayer(rightLayer).GetGameObjects();

	for (CGameObject* leftObj : lefts)
	{
		CCollider2D* leftCol = leftObj->GetComponent<CCollider2D>(eComponentType::Collider2D);

		if (leftCol == nullptr || leftObj->GetState() != CGameObject::eState::Active)
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
			if (rightCol == nullptr || rightObj->GetState() != CGameObject::eState::Active);
			{
				continue;
			}

			ColliderCollision(leftCol, rightCol);
		}
	}
}

void CCollisionMgr::ColliderCollision(CCollider2D* leftCol, CCollider2D* rightCol)
{
	collisionID colID = {};
	colID.Left = leftCol->GetColliderID();
	colID.Right = rightCol->GetColliderID();

	// �浹 ����
	std::map<UINT64, bool>::iterator iter = mCollisionMap.find(colID.CollisionId);
	if (iter == mCollisionMap.end())
	{
		mCollisionMap.insert(std::make_pair(colID.CollisionId, false));
		iter = mCollisionMap.find(colID.CollisionId);
	}

	if (Intersect(leftCol, rightCol));
}

bool CCollisionMgr::Intersect(CCollider2D* leftCol, CCollider2D* rightCol)
{
	// Rect vs Rect 
	// 0 --- 1
	// |     |
	// 3 --- 2
	return false;
	Vector3 arrLocalPos[4] =
	{
		Vector3(-0.5f, 0.5f, 0.0f),
		Vector3(0.5f, 0.5f, 0.0f),
		Vector3(0.5f, -0.5f, 0.0f),
		Vector3(-0.5f, -0.5f, 0.0f)
	};

	CTransform* leftTr = leftCol->GetOwner()->GetComponent <CTransform>(eComponentType::Transform);
	CTransform* rightTr = rightCol->GetOwner()->GetComponent<CTransform>(eComponentType::Transform);

	Matrix leftMatrix = leftTr->GetWorldMatrix(); // ���� ��ȯ
	Matrix rightMatrix = rightTr->GetWorldMatrix();

	Vector3 leftScale = Vector3(leftCol->GetSize().x, leftCol->GetSize().y, 1.0f);
	Matrix  leftScaleMatrix = Matrix::CreateScale(leftScale);
	leftMatrix *= leftScaleMatrix; // ���� ��ȯ�� �浹ü�� ũ�� ����

	Vector3 rightScale = Vector3(rightCol->GetSize().x, rightCol->GetSize().y, 1.0f);
	Matrix rightScaleMatrix = Matrix::CreateScale(rightScale);
	rightMatrix *= rightScaleMatrix;

	// �и��� �迭
	Vector3 Axis[4] = {};

	// �� �浹ü�� 1���� 3�� ������ ���͸� ���� ��ȯ ����Ѵ�.
	Axis[0] = Vector3::Transform(arrLocalPos[1], leftMatrix);
	Axis[1] = Vector3::Transform(arrLocalPos[3], leftMatrix);
	Axis[2] = Vector3::Transform(arrLocalPos[1], rightMatrix);
	Axis[3] = Vector3::Transform(arrLocalPos[3], rightMatrix);
	
	// ���� ��ȯ ����� 1���� 3�� �� ���� ��ȯ ����� 0�� �����μ�
	// 0�� ���������� 1�� 3�� ������������ ���Ͱ� �ϼ��ȴ�.
	Axis[0] -= Vector3::Transform(arrLocalPos[0], leftMatrix);
	Axis[1] -= Vector3::Transform(arrLocalPos[0], leftMatrix);
	Axis[2] -= Vector3::Transform(arrLocalPos[0], rightMatrix);
	Axis[3] -= Vector3::Transform(arrLocalPos[0], rightMatrix);


	// 2���������� �浹�� ����ϱ� ���ؼ� z ���� 0.0f ���� �����Ѵ�.
	for (size_t i = 0; i < 4; i++)
	{
		Axis[i].z = 0.0f;
	}
	
	// �� �浹ü�� �߽� ������ �Ÿ�
	Vector3 vDist = leftTr->GetPosition() - rightTr->GetPosition();
	vDist.z = 0.0f;

	Vector3 vDistBetweenCols = vDist;

	for (size_t i = 0; i < 4; i++)
	{
		// ������ �Ǵ� �и����� ����ȭ
		Vector3 vAxis = XMVector3Normalize(Axis[i]);

		float projLength = 0.0f;
		for (size_t j = 0; j < 4; j++)
		{
			// ����ȭ�� �и��࿡ �� ����(0->1 �Ǵ� 3)���� ������ �翵���̸� ���ϰ� 2 �� ������.
			// ������ �翵���̵��� ��� ���Ѵ�.
			projLength += fabsf(Axis[j].Dot(vAxis) / 2.0f);
		}

		// ���� �翵���� ���ѰͰ� �� �浹ü ������ �Ÿ��� �翵���̸� ���Ѵ�.
		if (projLength < fabsf(vDistBetweenCols.Dot(vAxis)))
		{
			// �ϳ��� �и����� ���� �翵���� ���Ѱͺ��� �� �浹ü�� �Ÿ��� �翵���̰� �� ū���
			// ��, �ϳ��� �и������� �� ������ �翵���� �� �� ������ �ִ� ��� �浹���� �ʾҴ�.
			return false;
		}
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

	// �Ϲ������� 2���� ������ ����X���� �� ǥ�������� �迭�� ���� ���� ����X���η� ǥ���Ѵ�.
	mMatrix[col][row] = enable;
}

void CCollisionMgr::Clear()
{
	mMatrix->reset();
	mCollisionMap.clear();
}
