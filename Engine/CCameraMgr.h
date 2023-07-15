#pragma once
#include "CSingleton.h"
#include "CCamera.h"

class CCameraMgr :
    public CSingleton<CCameraMgr>
{
private:
    vector<CCamera*> mCameras = {};

public:
    CCameraMgr();
    ~CCameraMgr();

    void Initialize();
    void Update();
    void LateUpdate();
    void Render();
    void Release();

    CCamera* AddCamera(CCamera* camera) { mCameras.push_back(camera); return camera; }
};

