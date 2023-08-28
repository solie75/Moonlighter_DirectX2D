#include "Header.hlsli"

// RWStructuredBuffer 는 읽기 및 쓰기가 가능한 구조화된 버처를 나타낸다.
RWStructuredBuffer<Particle> ParticleBuffer : register(u0);

float GenerateRandom(float2 uv)
{
    float value = sin(uv.x * 12.9898 + uv.y * 78.233) * 43758.5453;
    
    return frac(value);
}

[numthreads(128, 1, 1)] // 이 computeShader 가 수생될 스레드 그룹의 크기를 정의한다. (각 쓰레드 그룹이 128개의 스레드로 이루어져있다는 의미)
void main(uint3 DTid : SV_DispatchThreadID)
{
    if (elementCount <= DTid.x)
        return;
 
    ParticleBuffer[DTid.x].position +=
    ParticleBuffer[DTid.x].direction * ParticleBuffer[DTid.x].speed * 0.1f;
    
    // particleBuffer 에서 현재 쓰레드의 ID('DTid.x') 에 해당하는 파티클을 선택하고,
    // 파티클의 위치, 방향, 속도, 경과시간 를 이용하여 파티클의 새로운 위치를 계산하고 업데이트한다.
    
    ParticleBuffer[DTid.x].curTime += elapsedTime;
    
    if (ParticleBuffer[DTid.x].curTime > ParticleBuffer[DTid.x].endTime)
    {
        ParticleBuffer[DTid.x].state = 2;
    }
    
    if (ParticleBuffer[DTid.x].state == 2) // 2 : Dead 상태
    {
        // 위치 램덤, 방향과 속도는 그대로..
        float ranfomValueX = GenerateRandom(ParticleBuffer[DTid.x].position.xy);
        float ranfomValueY = GenerateRandom(ParticleBuffer[DTid.x].position.xy);
        
        ParticleBuffer[DTid.x].position.x = ranfomValueX * 8.0f - 3;
        ParticleBuffer[DTid.x].position.y = ranfomValueY * 4.0f - 2;
        ParticleBuffer[DTid.x].curTime = 0;
        ParticleBuffer[DTid.x].state = 1;
    }
}



// 위의 코드는 파티클 시스템을 업데이트하고 그 결과를 ParticleBuffer 에 저장한다.