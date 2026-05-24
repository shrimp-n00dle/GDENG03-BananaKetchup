float4 VSMain(float3 pos : POSITION) : SV_Position
{
    return float4(pos.xyz, 1.0);
}
float4 PSMain() : SV_Target
{
    return float4(1.0, 1.0, 1.0, 1.0);
}