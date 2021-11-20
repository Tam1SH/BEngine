


cbuffer ConstantBuffer : register(b1)
{
    float4x4 World;
    float3 Color;
}

cbuffer CameraData : register(b2) {
    float4x4 Projection;
    float4x4 View;
    float3 position;

};



struct VS_INPUT
{

    float4 Pos : POSITION;

    float4 Color : COLOR;

   // float4 TexCoord : TEXCOORD;

   // float4 Normal : NORMAL;
};



struct PS_INPUT

{

    float4 Pos : SV_POSITION;

    float4 Color : COLOR;

};





//--------------------------------------------------------------------------------------

// Вершинный шейдер

//--------------------------------------------------------------------------------------

PS_INPUT VS(VS_INPUT input)

{

    PS_INPUT output = (PS_INPUT)0;


  //  output.Pos = mul(World, input.Pos);
    float4 test = (float4)input.Pos;
    float4x4 VP = mul(Projection, View);
    float4x4 MVP = mul(VP, World);
    test = mul(MVP, test);





    output.Pos = test;
    output.Color = float4(Color,1);



    return output;

}





//--------------------------------------------------------------------------------------

// Пиксельный шейдер

//--------------------------------------------------------------------------------------

float4 PS(PS_INPUT input) : SV_Target
{

    return input.Color;

}