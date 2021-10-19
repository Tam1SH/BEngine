


cbuffer ConstantBuffer : register(b1)
{

    matrix model;              
    matrix View;               
    matrix Projection;
}

cbuffer CameraData : register(b2) {
    float4x4 view;
    float4x4 proj;
};


struct VS_OUTPUT
{
    float4 Pos : SV_POSITION;
};

VS_OUTPUT VS( float4 Pos : POSITION )
{
    VS_OUTPUT output = (VS_OUTPUT)0;
    
  //  output.Pos = CameraData.proj * CameraData.view * UniformBufferObject.model * float4(Pos, 1.0);
    output.Pos = Pos;
    return output;
}



float4 PS(VS_OUTPUT input) : SV_Target
{
    return input.Pos;
}