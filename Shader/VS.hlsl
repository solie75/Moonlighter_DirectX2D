#include "Header.hlsli"

cbuffer Transform : register(b0)
{
    float4 TransPos;
}

VSOut main(VSIn In)
{
    VSOut Out = (VSOut) 0.0f;

    //Out.Pos.x += TransPos.x;
    //Out.Pos.y += TransPos.y;
    Out.Pos = float4(In.Pos, 1.0f);
    Out.Pos.x += TransPos.x;
 
    Out.Color = In.Color;
    
    return Out;
}