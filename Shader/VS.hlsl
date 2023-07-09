#include "Header.hlsli"

VSOut main(VSIn In)
{
    VSOut Out = (VSOut) 0.0f;
    Out.Pos = float4(In.Pos, 1.0f);
    Out.Color = In.Color;
    
    return Out;
}