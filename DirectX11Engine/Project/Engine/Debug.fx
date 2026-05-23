#ifndef _DEBUG_SHAPE
#define _DEBUG_SHAPE

#include "Common.fx"

struct VS_INPUT
{
    float3 position : POSITION;
    float2 uv : TEXCOORD;
};

struct VS_OUPUT
{
    float4 position : SV_Position;
    float2 uv : TEXCOORD;
};

VS_OUPUT VS_DebugShape(VS_INPUT _in)
{
    VS_OUPUT output;
    
    float4 worldPos = mul(float4(_in.position, 1.f), matWorld);
    float4 viewPos = mul(worldPos, matView);
    float4 projPos = mul(viewPos, matProj);
    
    output.position = projPos;
    output.uv = _in.uv;

    return output;
}

float4 PS_DebugShape(VS_OUPUT _in) : SV_Target
{
    //if (_in.uv.x > 0.05f && _in.uv.x < 0.95f &&
    //    _in.uv.y > 0.05f && _in.uv.y < 0.95f)
    //{
    //    discard;
    //}
    
    return vec4Value_0;
}

#endif