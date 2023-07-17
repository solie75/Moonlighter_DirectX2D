#include "Header.hlsli"

Texture2D smileTexture : register(t0);
SamplerState pointSampler : register(s0);
SamplerState anisotropicSampler : register(s1);

float4 main(VSOut In) : SV_TARGET
{
    float4 color = (float) 0.0f;
    color = smileTexture.Sample(anisotropicSampler, In.UV);
    
    return color;
}