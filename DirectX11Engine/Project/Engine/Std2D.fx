#ifndef _STD2D
#define _STD2D

#include "Common.fx"

struct VS_INPUT
{
    float3 pos : POSITION0;
    float4 color : COLOR;
    float2 uv : TEXCOORD;
};

struct VS_OUTPUT
{
    float4 pos : SV_Position;
    float4 color : COLOR;
    float2 uv : TEXCOORD;
};

VS_OUTPUT VS_Std2D(VS_INPUT _input)
{
    VS_OUTPUT output = (VS_OUTPUT) 0.f;
    
    float4 worldPos = mul(float4(_input.pos, 1), matWorld);
    float4 viewPos = mul(worldPos, matView);
    float4 projPos = mul(viewPos, matProj);
    
    output.pos = projPos;
    output.color = _input.color;
    output.uv = _input.uv;

    return output;
}

float4 PS_Std2D(VS_OUTPUT _in) : SV_Target
{
    float4 vColor = g_tex_0.Sample(g_texSampler_0, _in.uv);
    return vColor;
}


#endif