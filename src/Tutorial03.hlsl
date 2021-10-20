


cbuffer ConstantBuffer : register(b1)
{
    float4x4 World;
}

cbuffer CameraData : register(b2) {
    float4x4 Projection;
    float4x4 View;

};



struct VS_INPUT

{

    float4 Pos : POSITION;

    float4 Color : COLOR;

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

    float4 test = mul(World, input.Pos);
    float4x4 PV = mul(Projection, View);
    test = mul(PV, test);


    output.Pos = test;
    output.Color = test;



    return output;

}





//--------------------------------------------------------------------------------------

// Пиксельный шейдер

//--------------------------------------------------------------------------------------

float4 PS(PS_INPUT input) : SV_Target

{

    return input.Color;

}