#include "Header.hlsli"

struct VSIn
{
	float3 Pos : POSITION;
	float4 color : COLOR;
	float2 UV : TEXCOORD;
};

struct VSOut
{
	float4 Pos : SV_POSITION;
	float4 Color : COLOR;
	float2 UV : TEXCOORD;
};

float4 main(VSOut In) : SV_TARGET
{
	float4 color = (float4) 1.0f;

    float2 modifiendTexcoord = In.UV * SpriteSize + Offset;
    color = atlasTexture.Sample(anisotropicSampler, modifiendTexcoord);
	
    color *= lightsAttribute[0].color;
	return color;
}