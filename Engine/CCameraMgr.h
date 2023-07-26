#pragma once
#include "CSingleton.h"
#include "CCamera.h"

class CCameraMgr :
    public CSingleton<CCameraMgr>
{
private:
    std::map<CCamera*, eCameraType> mCameras = {};

public:
    CCameraMgr();
    ~CCameraMgr();

    void Initialize();
    void Update();
    void LateUpdate();
    void Render();
    void Release();

    CCamera* AddCamera(CCamera* camera, eCameraType type, const std::wstring& name) {
        mCameras.insert(std::make_pair(camera, type));
        camera->SetName(name);
        return camera; 
    }

    void ClearCamera()
    {
        mCameras.clear();
    }
};

