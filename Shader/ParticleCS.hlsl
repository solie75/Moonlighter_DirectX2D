#include "Header.hlsli"

// RWStructuredBuffer �� �б� �� ���Ⱑ ������ ����ȭ�� ��ó�� ��Ÿ����.
RWStructuredBuffer<Particle> ParticleBuffer : register(u0);

float GenerateRandom(float2 uv)
{
    float value = sin(uv.x * 12.9898 + uv.y * 78.233) * 43758.5453;
    
    return frac(value);
}

[numthreads(128, 1, 1)] // �� computeShader �� ������ ������ �׷��� ũ�⸦ �����Ѵ�. (�� ������ �׷��� 128���� ������� �̷�����ִٴ� �ǹ�)
void main(uint3 DTid : SV_DispatchThreadID)
{
    if (elementCount <= DTid.x)
        return;
 
    ParticleBuffer[DTid.x].position +=
    ParticleBuffer[DTid.x].direction * ParticleBuffer[DTid.x].speed;
    
    // particleBuffer ���� ���� �������� ID('DTid.x') �� �ش��ϴ� ��ƼŬ�� �����ϰ�,
    // ��ƼŬ�� ��ġ, ����, �ӵ�, ����ð� �� �̿��Ͽ� ��ƼŬ�� ���ο� ��ġ�� ����ϰ� ������Ʈ�Ѵ�.
    
    ParticleBuffer[DTid.x].curTime += elapsedTime;
    
    if (ParticleBuffer[DTid.x].curTime > ParticleBuffer[DTid.x].endTime)
    {
        ParticleBuffer[DTid.x].state = 2;
    }
    
    if (ParticleBuffer[DTid.x].state == 2) // 2 : Dead ����
    {
        // ��ġ ����, ����� �ӵ��� �״��..
        float ranfomValueX = GenerateRandom(ParticleBuffer[DTid.x].position.xy);
        float ranfomValueY = GenerateRandom(ParticleBuffer[DTid.x].position.xy);
        
        ParticleBuffer[DTid.x].position.x = ranfomValueX * 10.0f - 3;
        ParticleBuffer[DTid.x].position.y = ranfomValueY * 6.0f - 2;
        ParticleBuffer[DTid.x].curTime = 0;
        ParticleBuffer[DTid.x].state = 1;
    }
}



// ���� �ڵ�� ��ƼŬ �ý����� ������Ʈ�ϰ� �� ����� ParticleBuffer �� �����Ѵ�.