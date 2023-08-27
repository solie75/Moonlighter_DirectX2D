
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

cbuffer DebugColor : register(b4)
{
    float4 DebugColor;
}

cbuffer ParticleSystem : register(b5)
{
    uint elementCount;
    float elapsedTime;
    int padd;
    int padd2;
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

struct Particle
{
    float4 position;
    float4 direction;
    float4 startSize;
    float4 endSize;
    float4 startColor;
    float4 endColor;
    
    float endTime;
    float curTime;
    float speed;
    uint state;
};


//Texture2D smileTexture : register(t0);
Texture2D albedoTexture : register(t0);
Texture2D atlasTexture : register(t12);
StructuredBuffer<LightAttribute> lightsAttribute : register(t13);
StructuredBuffer<Particle> particles : register(t14);

SamplerState pointSampler : register(s0);
SamplerState anisotropicSampler : register(s1);

void CalculateLight2D(in out float4 lightColor, float3 position, int idx)
{
    if (0 == lightsAttribute[idx].type)
    {
        lightColor += lightsAttribute[idx].color;
    }
    else if (1 == lightsAttribute[idx].type)
    {
        float length = distance(position.xy, lightsAttribute[idx].position.xy);

        if (length < lightsAttribute[idx].radius)
        {
            float ratio = 1.0f - (length / lightsAttribute[idx].radius);
            lightColor += lightsAttribute[idx].color * ratio;
        }
    }
    else
    {

    }
}