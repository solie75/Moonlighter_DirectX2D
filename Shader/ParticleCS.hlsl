#include "Header.hlsli"

// RWStructuredBuffer 는 읽기 및 쓰기가 가능한 구조화된 버처를 나타낸다.
RWStructuredBuffer<Particle> ParticleBuffer : register(u0);

[numthreads(128, 1, 1)] // 이 computeShader 가 수생될 스레드 그룹의 크기를 정의한다. (각 쓰레드 그룹이 128개의 스레드로 이루어져있다는 의미)
void main(uint3 DTid : SV_DispatchThreadID)
{
    if (elementCount <= DTid.x)
        return;
    
    // particleBuffer 에서 현재 쓰레드의 ID('DTid.x') 에 해당하는 파티클을 선택하고,
    // 파티클의 위치, 방향, 속도, 경과시간 를 이용하여 파티클의 새로운 위치를 계산하고 업데이트한다.
    ParticleBuffer[DTid.x].position +=
    ParticleBuffer[DTid.x].direction * ParticleBuffer[DTid.x].speed * elapsedTime;
}

// 위의 코드는 파티클 시스템을 업데이트하고 그 결과를 ParticleBuffer 에 저장한다.