cbuffer Timer : register(b0)
{
    float delta_time = 1.0;
};
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

VSOutput VSMain(VSInput input)
{
    VSOutput output;
    output.position = float4(input.position,1);
    output.color = input.color;
    return output;
}
float4 PSMain(VSOutput input) : SV_Target
{
    return float4(1.0,0.0,0.0,1.0);
}

float4 MovingColors(VSOutput input) : SV_Target
{
    input.color.x += delta_time;
    return input.color;

}