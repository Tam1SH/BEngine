#version 450
#extension GL_ARB_shader_draw_parameters : enable

layout(std140, set = 1, binding = 0) buffer CameraData {
    mat4 proj;
    mat4 view;
    vec3 position;
} Camera;

struct gameObject {
    mat4 model;
    vec3 color;
};

layout(std140, set = 0, binding = 0) readonly buffer objectBuffer {
	gameObject objects[];
} objects;


layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inColor;
layout(location = 2) in vec2 inTexCoord;
layout(location = 3) in vec3 normal;

layout(location = 0) out vec3 fragColor;
layout(location = 1) out vec2 fragTexCoord;
layout(location = 2) out vec3 fNormal;
layout(location = 3) out vec3 fragPosition;
layout(location = 4) out vec3 cameraPosition;
layout(location = 5) out vec3 objectColor;

void main() {
    gl_Position = Camera.proj * Camera.view * objects.objects[gl_BaseInstanceARB].model * vec4(inPosition, 1.0);
    fragPosition = vec3(objects.objects[gl_BaseInstanceARB].model * vec4(inPosition, 1.0));
    fNormal = mat3(transpose(inverse(objects.objects[gl_BaseInstanceARB].model))) * normal;

    fragColor = Camera.position;
    fragTexCoord = inTexCoord;
    cameraPosition = Camera.position;
    objectColor = objects.objects[gl_BaseInstanceARB].color;


}