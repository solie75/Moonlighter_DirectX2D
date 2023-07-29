#pragma once
#include "CDebugObject.h"
#include "CSingleton.h"

class CEditor
	: public CSingleton<CEditor>
{
private:
	static std::vector<CDebugObject*> mDebugObjects;

public:
	CEditor();
	~CEditor();

	static void Initialize();
	static void Run();
	static void Update();
	static void LateUpdate();
	static void Render();
	static void Release();

	static void DebugRender(const DebugMesh& mesh);
};
