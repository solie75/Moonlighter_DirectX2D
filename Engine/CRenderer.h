#pragma once
#include "CSingleton.h"
#include "Graphic.h"

class CRenderer
	: public CSingleton<CRenderer>
{
public:
	CRenderer();
	~CRenderer();

	void Init();
	void Update();
	void Release();
};

