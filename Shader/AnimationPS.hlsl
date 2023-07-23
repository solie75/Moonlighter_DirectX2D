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

	color = atlasTexture.Sample(anisotropicSampler, In.UV);

	if (AnimationType == 1)
	{
		float2 diff = (AtlasSize - SpriteSize) / 2.0f;
		float2 UV = (SpriteLeftTop - diff - SpriteOffset) + (AtlasSize * In.UV);
		
		/*if (UV.x < SpriteLeftTop.x || UV.x > SpriteLeftTop.x + SpriteSize.x
			|| UV.y < SpriteLeftTop.y || UV.y > SpriteLeftTop.y + SpriteSize.y)
			discard;*/

		color = atlasTexture.Sample(anisotropicSampler, UV);
	}
	return color;
}