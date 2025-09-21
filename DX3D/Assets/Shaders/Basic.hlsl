struct VS_INPUT
{
    float3 position : POSITION0;
    float4 color : COLOR0;
};

struct VS_OUTPUT
{
    float4 position : SV_Position;
    float4 color : COLOR0;
};

VS_OUTPUT VSMain(VS_INPUT input)
{
    VS_OUTPUT output;
    output.position = float4(input.position, 1.0);
    output.color = input.color;
    return output;
}

float4 PSMain(VS_OUTPUT input): SV_Target
{
    return input.color;
}