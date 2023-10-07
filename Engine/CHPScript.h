#pragma once
#include "CScript.h"
#include "CScene.h"

class CHPScript :
    public CScript
{
private:
	UINT mFullHP;
	UINT mCurHP;
	float mFullWidth;
	float mLeftXPos;

	Vector2 mOffset; // offset within parent object
	//CScene* mCurScene;
	CGameObject* HpObj;

public:
	CHPScript();
	~CHPScript();

	virtual void Initialize();
	virtual void Update();
	virtual void LateUpdate();
	virtual void Render();

	void SetLeftXPos(float xPos) { mLeftXPos = xPos; }
	void SetHpOffSet(Vector2 offset) { mOffset = offset; }
	//void SetScene(CScene* scene) { mCurScene = scene; }
	void AddHpObject(CScene* scene);
};

