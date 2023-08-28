#include "Header.hlsli"

struct GSOut
{
    float4 Pos : SV_Position;
    float2 UV : TEXCOORD;
};

//float4 main(VSOut In) : SV_Target
float4 main(GSOut In) : SV_TARGET
{
    float4 Out = (float4) 0.0f;
    Out = float4(particles[0].startColor.x, particles[0].startColor.y, particles[0].startColor.z, 1.0f);
    // particles 의 각 Particle 당 다른 ps 가 적용되어야 한다. 어떻게..?
    return Out;
}