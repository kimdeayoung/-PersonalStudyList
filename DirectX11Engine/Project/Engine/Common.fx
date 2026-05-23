#ifndef _VALUE
#define _VALUE

cbuffer TRANSFORM : register(b0)
{
    row_major matrix matWorld;
    row_major matrix matView;
    row_major matrix matProj;
}

cbuffer MATERIAL_CONST : register(b1)
{
    int intValue_0;
    int intValue_1;
    int intValue_2;
    int intValue_3;
    
    float floatValue_0;
    float floatValue_1;
    float floatValue_2;
    float floatValue_3;
    
    float2 vec2Value_0;
    float2 vec2Value_1;
    float2 vec2Value_2;
    float2 vec2Value_3;
    
    float4 vec4Value_0;
    float4 vec4Value_1;
    float4 vec4Value_2;
    float4 vec4Value_3;
    
    row_major Matrix matrixValue_0;
    row_major Matrix matrixValue_1;
    row_major Matrix matrixValue_2;
    row_major Matrix matrixValue_3;
}

Texture2D g_tex_0 : register(t0);
Texture2D g_tex_1 : register(t1);
Texture2D g_tex_2 : register(t2);
Texture2D g_tex_3 : register(t3);
Texture2D g_tex_4 : register(t4);
Texture2D g_tex_5 : register(t5);

TextureCube g_texCube_0 : register(t6);
TextureCube g_texCube_1 : register(t7);
TextureCube g_texCube_2 : register(t8);
TextureCube g_texCube_3 : register(t9);

Texture2DArray g_texArray_0 : register(t10);
Texture2DArray g_texArray_1 : register(t11);
Texture2DArray g_texArray_2 : register(t12);
Texture2DArray g_texArray_3 : register(t13);

SamplerState g_texSampler_0 : register(s0);
SamplerState g_texSampler_1 : register(s1);

#endif