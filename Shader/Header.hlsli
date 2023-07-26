
cbuffer Transform : register(b0)
{
    row_major matrix WorldMatrix;
    row_major matrix ViewMatrix;
    row_major matrix ProjectionMatrix;
}

cbuffer Grid : register(b2)
{
    float4 CameraPosition;
    float2 CameraScale;
    float2 Resolution;
}

cbuffer Animator : register(b3)
{
    float2 SpriteSize;
    float2 Offset;
    uint AnimationType;
}

struct LightAttribute
{
    float4 color;
    float4 position;
    float4 direction;
    
    uint type;
    float radius;
    float angle;
    int pad;
};


//Texture2D smileTexture : register(t0);
Texture2D albedoTexture : register(t0);
Texture2D atlasTexture : register(t12);
StructuredBuffer<LightAttribute> lightsAttribute : register(t13);

SamplerState pointSampler : register(s0);
SamplerState anisotropicSampler : register(s1);