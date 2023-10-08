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
    float3 WorldPos : POSITION;
	float4 Color : COLOR;
	float2 UV : TEXCOORD;
};

float4 main(VSOut In) : SV_TARGET
{
	float4 color = (float4) 1.0f;
    float2 modifiendTexcoord = In.UV * SpriteSize + Offset;
    if (AnimationType == 0) // 0 : Basic
    {
       
        color = atlasTexture.Sample(anisotropicSampler, modifiendTexcoord);
    }
    else if (AnimationType == 1) // 1 : HitRed
    {
        color = atlasTexture.Sample(anisotropicSampler, modifiendTexcoord);
        color *= float4(10.0f, 0.0f, 0.0f, 1.0f);
        //color = atlasTexture.Sample(float4(1.0f, 0.0f, 0.0f, 1.0f), modifiendTexcoord);
    }
    else if (AnimationType == 2) // 2 : HitWhite
    {
        color = atlasTexture.Sample(anisotropicSampler, modifiendTexcoord);
        color *= float4(10.0f, 10.0f, 10.0f, 1.0f);
        //color = atlasTexture.Sample(float4(1.0f, 1.0f, 1.0f, 1.0f), modifiendTexcoord);
        
    }
    
    // color *= lightsAttribute[0].color;
    float4 lightColor = float4(0.2f, 0.2f, 0.2f, 1.0f);
    //float4 lightColor = float4(1.0f, 0.f, 0.f, 0.0f);
	
    for (int i = 0; i < 2; i++)
    {
        CalculateLight2D(lightColor, In.WorldPos, i);
    }
    
    color *= lightColor;
    
    return color;
}