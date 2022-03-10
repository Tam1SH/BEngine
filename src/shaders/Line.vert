
#version 450
#extension GL_KHR_vulkan_glsl : enable
#extension GL_ARB_shader_draw_parameters : enable

layout(std140, set = 1, binding = 0) buffer CameraData {
    mat4 proj;
    mat4 view;
    vec3 position;
} Camera;

struct Line { 
    vec3 from;
    vec3 to;
    vec3 color;
};

layout(std140, set = 5, binding = 0) readonly buffer Lines { 
    Line[] lines;
};


layout(location = 0) out vec3 fragColor;

void main()
{
    vec3 points_[2] = vec3[](lines[gl_InstanceIndex].from , lines[gl_InstanceIndex].to );

    gl_Position = Camera.proj * Camera.view * vec4(points_[gl_VertexIndex], 1.0f);

    fragColor = lines[gl_InstanceIndex].color;
}
