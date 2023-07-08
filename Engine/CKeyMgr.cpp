#include "CKeyMgr.h"

CKeyMgr::CKeyMgr()
	: mHwnd(nullptr)
{
}

CKeyMgr::~CKeyMgr()
{
}

int arrVK[(UINT)KEY::END] =
{
	'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P',
		'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L',
		'Z', 'X', 'C', 'V', 'B', 'N', 'M',

		VK_UP, VK_DOWN, VK_LEFT ,VK_RIGHT, VK_SPACE,
		VK_LBUTTON, VK_RBUTTON,
};

void CKeyMgr::Init(HWND _hWnd)
{
	for (int i = 0; i < (int)KEY::END; i++)
	{
		mVecKey.push_back(KeyInfo{ (KEY)i, KEY_STATE::NONE });
	}

	mHwnd = _hWnd;
}

void CKeyMgr::Update()
{
	if (GetFocus()) // �ش� �����찡 ��Ŀ�� ������ ���
	{
		for (size_t i = 0; i < mVecKey.size(); i++)
		{
			if (GetAsyncKeyState(arrVK[(UINT)mVecKey[i].key]) & 0x8000)
			{
				if (mVecKey[i].bPressed)
				{
					mVecKey[i].state = KEY_STATE::PRESSED;
				}
				else
				{
					mVecKey[i].state = KEY_STATE::TAP;
					mVecKey[i].bPressed = true;
				}
			}
			else
			{
				if (mVecKey[i].bPressed)
				{
					mVecKey[i].state = KEY_STATE::RELEASE;
					mVecKey[i].bPressed = false;
				}
				else
				{
					mVecKey[i].state = KEY_STATE::NONE;
				}
			}
		}

		// Mouse ��ġ ����
		POINT ptMousePos = {};
		GetCursorPos(&ptMousePos);
		ScreenToClient(mHwnd, &ptMousePos);
		mMousePos = Vector2((float)ptMousePos.x, (float)ptMousePos.y);
	}
	else // �ش� �����찡 ��Ŀ�� ���°� �ƴ� ���
	{
		for (size_t i = 0; i < mVecKey.size(); ++i)
		{
			if ((mVecKey[i].state == KEY_STATE::TAP) || (mVecKey[i].state == KEY_STATE::PRESSED))
			{
				mVecKey[i].state = KEY_STATE::RELEASE;
			}
			else if (mVecKey[i].state == KEY_STATE::RELEASE)
			{
				mVecKey[i].state = KEY_STATE::NONE;
			}
		}
	}
}
