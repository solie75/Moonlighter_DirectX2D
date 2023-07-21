#pragma once
#include "CSingleton.h"
#include "CScene.h"

class CSceneMgr :
    public CSingleton<CSceneMgr>
{
private:
    CScene* mActiveScene;
    std::map<std::wstring, CScene*> mScenes;

public:
    CSceneMgr();
    ~CSceneMgr();

    void Initialize();
    void Update();
    void LateUpdate();
    void Render();
    void Release();

    void Destroy();

    CScene* GetActiveScene() { return mActiveScene; }
    void SetActiveScene(CScene* scene) { mActiveScene = scene; }

    template <typename T>
    static bool AddScene(std::wstring sceneName)
    {
        T* scene = new T();

        std::map<std::wstring, CScene*>::iterator iter = CSceneMgr::GetInst()->mScenes.find(sceneName);

        if (iter != CSceneMgr::GetInst()->mScenes.end())
        {
            return false;
        }

        CSceneMgr::GetInst()->mScenes.insert(std::make_pair(sceneName, scene));
        CSceneMgr::GetInst()->SetActiveScene(scene);
        scene->Initialize();

        return true;
    }
};

