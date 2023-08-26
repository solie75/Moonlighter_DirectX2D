#include "Header.hlsli"
RWStructuredBuffer<Particle> ParticleBuffer : register(u0);

[numthreads(128, 1, 1)]
void main(uint3 DTid : SV_DispatchThreadID)
{
    if (elementCount >= DTid.x)
    {
        // elementCount >= DTid.x 는 작동됨 elementCount 에 값이 잘못 전달되고 있다는 뜻
        return;
    }

    ParticleBuffer[DTid.x].position +=
        //float4(0.1f, 0.0f, 0.0f, 1.0f);
        ParticleBuffer[DTid.x].direction * ParticleBuffer[DTid.x].speed * elapsedTime;
}