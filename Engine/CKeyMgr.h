#pragma once
#include "CSingleton.h"
#include "Header.h"

enum class KEY
{
	Q, W, E, R, T, Y, U, I, O, P,
	A, S, D, F, G, H, J, K, L,
	Z, X, C, V, B, N, M,

	UP, DOWN, LEFT, RIGHT, SPACE,
	LBUTTON, RBUTTON,
	END,
};

enum class KEY_STATE
{
	TAP,
	PRESSED,
	RELEASE,
	NONE,
};

struct KeyInfo
{
	KEY			key;
	KEY_STATE	state;
	bool		bPressed;
};

class CKeyMgr
	: public CSingleton<CKeyMgr>
{
private:
	vector<KeyInfo> mVecKey;
	Vector2 mMousePos;

	HWND mHwnd;

public:
	CKeyMgr();
	~CKeyMgr();

	void Init(HWND _hWnd);
	void Update();

	KEY_STATE GetKeyState(KEY _key) { return mVecKey[(UINT)_key].state; }
	Vector2 GetMousePos() { return mMousePos; }
};

