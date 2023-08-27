#include "Header.hlsli"

// RWStructuredBuffer �� �б� �� ���Ⱑ ������ ����ȭ�� ��ó�� ��Ÿ����.
RWStructuredBuffer<Particle> ParticleBuffer : register(u0);

[numthreads(128, 1, 1)] // �� computeShader �� ������ ������ �׷��� ũ�⸦ �����Ѵ�. (�� ������ �׷��� 128���� ������� �̷�����ִٴ� �ǹ�)
void main(uint3 DTid : SV_DispatchThreadID)
{
    if (elementCount <= DTid.x)
        return;
    
    // particleBuffer ���� ���� �������� ID('DTid.x') �� �ش��ϴ� ��ƼŬ�� �����ϰ�,
    // ��ƼŬ�� ��ġ, ����, �ӵ�, ����ð� �� �̿��Ͽ� ��ƼŬ�� ���ο� ��ġ�� ����ϰ� ������Ʈ�Ѵ�.
    ParticleBuffer[DTid.x].position +=
    ParticleBuffer[DTid.x].direction * ParticleBuffer[DTid.x].speed * elapsedTime;
}

// ���� �ڵ�� ��ƼŬ �ý����� ������Ʈ�ϰ� �� ����� ParticleBuffer �� �����Ѵ�.