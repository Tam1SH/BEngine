#version 450
layout(std140, set = 0,  binding = 0) uniform GameObjectData {
    mat4 model;
    vec3 color;
} object;



layout(std140, set = 1, binding = 0) buffer CameraData {
    mat4 proj;
    mat4 view;
    vec3 position;
} Camera;



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
    gl_Position = Camera.proj * Camera.view * object.model * vec4(inPosition, 1.0);
    fragPosition = vec3(object.model * vec4(inPosition, 1.0));
    fNormal = mat3(transpose(inverse(object.model))) * normal;

    fragColor = Camera.position;
    fragTexCoord = inTexCoord;
    cameraPosition = Camera.position;
    objectColor = object.color;


}