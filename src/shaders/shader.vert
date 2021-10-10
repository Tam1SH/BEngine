#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(binding = 0) uniform UniformBufferObject {
    mat4 model;
} ubo;



layout(std140, set = 1, binding = 0) buffer CameraData {
    mat4 view;
    mat4 proj;
} Camera;


layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inColor;
layout(location = 2) in vec2 inTexCoord;
layout(location = 3) in vec3 normal;
layout(location = 4) in vec3 Tangent;
layout(location = 5) in vec3 BiTangent;

layout(location = 0) out vec4 fragColor;
layout(location = 1) out vec2 fragTexCoord;



void main() {
    gl_Position = Camera.proj * Camera.view * ubo.model * vec4(inPosition, 1.0);
    fragTexCoord = inTexCoord;
    fragColor = Camera.view[0];
}