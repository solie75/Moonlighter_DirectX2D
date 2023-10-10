#pragma once
#include "CScript.h"

class CNaviScript :
    public CScript
{
public:
    struct sNode
    {
        UINT total;
        UINT heuristicValue;
        UINT curSideValue;
        Vector2 nodePos;
        sNode* ParentNode;
    };

private:
    Vector2 mNodeSize;
public:
    CNaviScript();
    ~CNaviScript();

    virtual void Initialize();
    virtual void Update();
    virtual void LateUpdate();
};

