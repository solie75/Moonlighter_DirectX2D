#include "Header.hlsli"

//cbuffer Transform : register(b0)
//{
//    float4 TransPos;
//}

cbuffer Transform : register(b0)
{
    row_major matrix mWorld;
    row_major matrix mView;
    row_major matrix mProjection;
}

VSOut main(VSIn In)
{
    VSOut Out = (VSOut) 0.0f;
    
    float4 world = mul(float4(In.Pos, 1.0f), mWorld);
    float4 view = mul(world, mView);
    float4 proj = mul(view, mProjection);
    
    Out.Pos = proj;
    Out.Color = In.Color;
    Out.UV = In.UV;
    
    return Out;
}