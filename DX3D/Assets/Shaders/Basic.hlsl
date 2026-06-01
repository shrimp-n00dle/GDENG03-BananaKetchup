struct VSInput
{
    float3 position : POSITION0;
    float4 color : COLOR0;
};

struct VSOutput
{
    float4 position : SV_Position;
    float4 color : COLOR0;
};

cbuffer constant : register(b0)
{
    unsigned int m_time;
};

VSOutput VSMain(VSInput input)
{
    VSOutput output;
    output.position = float4(input.position,1);
    output.color = input.color;
    return output;
}
float4 PSMain(VSOutput input) : SV_Target
{
    return input.color;
}