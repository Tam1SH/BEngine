#version 450
layout(binding = 0) uniform UniformBufferObject {
    mat4 model;
} ubo;



layout(std140, set = 1, binding = 0) buffer CameraData {
    mat4 proj;
    mat4 view;

} Camera;


layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inColor;
layout(location = 2) in vec2 inTexCoord;
layout(location = 3) in vec3 normal;
layout(location = 4) in vec3 Tangent;
layout(location = 5) in vec3 BiTangent;

layout(location = 0) out vec4 fragColor;
layout(location = 1) out vec2 fragTexCoord;


vec2 positions[3] = vec2[](
    vec2(0.0, -0.5),
    vec2(0.5, 0.5),
    vec2(-0.5, 0.5)
);

void main() {
    gl_Position = Camera.proj * Camera.view * ubo.model * vec4(inPosition, 1.0);
    fragTexCoord = inTexCoord;
    fragColor =  Camera.proj * Camera.view * ubo.model * vec4(inPosition, 1.0);
        //gl_Position = vec4(positions[gl_VertexIndex], 0.0, 1.0);
    //fragTexCoord = inTexCoord;
   // fragColor = Camera.proj[3];
   // fragColor = Camera.proj[0] + Camera.proj[1] +  Camera.proj[2] +Camera.proj[3];
}