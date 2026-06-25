
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

//For Mr.Sphere
struct VS_I_Sphere
{
    float3 position : POSITION0;
    float3 normals : NORMAL0;
    float2 textCoord : TEXCOORD0;
};

struct VS_O_Sphere
{
    float3 position : POSITION0;
    float3 normals : NORMAL0;
    float2 textCoord : TEXCOORD0;
};


cbuffer ConstantData : register(b0)
{
    row_major float4x4 world;
    row_major float4x4 view;
    row_major float4x4 proj;
};

VSOutput VSMain(VSInput input)
{
    VSOutput output;
    output.position = mul(float4(input.position, 1), world);
    output.position = mul(output.position, view);
    output.color = input.color;
    return output;
}

VS_O_Sphere VSMain_Sphere(VS_I_Sphere input)
{
    VS_O_Sphere output;
    output.position = mul(float4(input.position, 1), world);
    output.position = mul(output.position, view);
    output.normals = input.normals;
    output.textCoord = input.textCoord;
    return output;

}

float4 PSMain(VSOutput input) : SV_Target
{
    return input.color;
}