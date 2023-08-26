#include "Header.hlsli"

struct VSIn
{
    float3 Localpos : POSITION;
    uint Instance : SV_InstanceID;
};

struct VSOut
{
    float4 Localpos : SV_Position;
    uint Instance : SV_InstanceID;
};

VSOut main(VSIn In)
{
    VSOut Out = (VSOut) 0.0f;
    
    Out.Localpos = float4(In.Localpos, 1.0f);
    Out.Instance = In.Instance;
    
    //float4 worldPos = mul(float4(In.pos, 1.0f), WorldMatrix);
    //worldPos.xyz += particles[In.Instance].position.xyz; // 월드 공간 좌표에 paricles 에 저장된 위치를 더한다.
    
    //float4 viewPos = mul(worldPos, ViewMatrix);
    //Out.pos = mul(viewPos, ProjectionMatrix);

    return Out;
}
