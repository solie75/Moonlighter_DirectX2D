#include "Header.hlsli"

//struct VSIn
//{
//    float3 pos : POSITIONT;
//    uint Instance : SV_InstanceID;
//};

//struct VSOut
//{
//    float4 pos : SV_POSITION;
//};

struct GSOut
{
    float4 Pos : SV_Position;
    float2 UV : TEXCOORD;
};

//float4 main(VSOut In) : SV_Target
float4 main(GSOut In) : SV_TARGET
{
    float4 Out = (float4) 0.0f;
    
    Out = float4(1.0f, 0.0f, 1.0f, 1.0f);
    
    return Out;

}