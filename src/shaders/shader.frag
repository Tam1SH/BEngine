#version 450
//#extension GL_ARB_separate_shader_objects : enable
layout(std140, set = 2, binding = 0) uniform LightData {
    vec3 position;
    vec3 color;
} Light;

layout(binding = 1) uniform sampler2D texSampler;


layout(location = 0) in vec3 fragColor;
layout(location = 1) in vec2 fragTexCoord;
layout(location = 2) in vec3 fNormal;
layout(location = 3) in vec3 fragPosition;
layout(location = 4) in vec3 cameraPosition;
layout(location = 5) in vec3 objectColor;

layout(location = 0) out vec4 outColor;
void main() {
    float ambientStrength = 0.01;
    vec3 ambient = ambientStrength * Light.color;
  	
    vec3 norm = normalize(fNormal);
    vec3 lightDir = normalize(Light.position - fragPosition);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * Light.color;
    
    float specularStrength = 0.5f;
    vec3 viewDir = normalize(cameraPosition - fragPosition);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * Light.color;  
        
    vec3 result = (ambient + diffuse + specular)  * objectColor;
    vec4 FragColor = vec4(result, 1.0);

    outColor = texture(texSampler, fragTexCoord) * FragColor; 
}