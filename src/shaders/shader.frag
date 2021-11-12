#version 450
#extension GL_ARB_separate_shader_objects : enable

/*
layout(std140, set = 2, binding = 0) uniform PointLightData {

    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
	
    float constant;
    float linear;
    float quadratic;

} PointLight;
*/
layout(std140, set = 3, binding = 0) readonly buffer DirLightData {

    vec3 direction;
	
    vec3 Dir_ambient;
    vec3 Dir_diffuse;
    vec3 Dir_specular;

} DirLight;

/*
layout(std140, set = 4, binding = 0) uniform SpotLightData {

    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;
  
    float constant;
    float linear;
    float quadratic;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;       
} SpotLight;
*/



layout(binding = 1) uniform sampler2D texSampler;


layout(location = 0) in vec3 fragColor;
layout(location = 1) in vec2 fragTexCoord;
layout(location = 2) in vec3 fNormal;
layout(location = 3) in vec3 fragPosition;
layout(location = 4) in vec3 cameraPosition;
layout(location = 5) in vec3 objectColor;

layout(location = 0) out vec4 outColor;


//vec3 CalcSpotLight(vec3 normal, vec3 viewDir);



struct _PointLight {

    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
	
    float constant;
    float linear;
    float quadratic;

};

layout( push_constant ) uniform constants {
    int count_lights;
};

layout(std140, set = 2, binding = 0) readonly buffer lightsBuffer {

	_PointLight lights[];
} lights;


vec3 CalcDirLight(vec3 normal, vec3 viewDir);
vec3 CalcPointLight(_PointLight pLight, vec3 normal, vec3 viewDir);

void main() {


    // Свойства
    vec3 norm = normalize(fNormal);
    vec3 viewDir = normalize(cameraPosition - fragPosition);
    
    // =====================================================
    // Наше освещение настраивается в 3 этапа: направленное освещение, точечный свет  и, опционально, фонарик.
    // Для каждого этапа определяется функция расчета, которая вычисляет соответствующий цвет от каждого источника света.
    // В функции main() мы берем все вычисленные цвета и складываем их вместе для определения окончательного цвета заданного фрагмента
    // =====================================================
	
    // Этап №1: Направленное освещение
    vec3 result = vec3(0);
    result = CalcDirLight(norm, viewDir);
    // Этап №2: Точечные источники света
    for(int i = 0; i < count_lights; i++) {
        result += CalcPointLight(lights.lights[i], norm, viewDir);  
    }

		
    // Этап №3: Прожектор
    //result += CalcSpotLight(norm, viewDir);    
    
    vec4 FragColor = vec4(result * objectColor,1.0f);

   // outColor = texture(texSampler, fragTexCoord) * FragColor; 
    outColor = FragColor; 
}

// Вычисляем цвет при использовании точечного источника света
vec3 CalcPointLight(_PointLight pLight, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(pLight.position - fragPosition);

    float diff = max(dot(normal, lightDir), 0.0);

    float ambientStrength = 0.01;
    vec3 ambient = pLight.ambient * ambientStrength;

    vec3 diffuse = diff * pLight.diffuse;
    float specularStrength = 0.5f;
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * pLight.specular; 
    
    float distance = length(pLight.position - fragPosition);
    float attenuation = 1.0 / (pLight.constant + pLight.linear * distance + pLight.quadratic * (distance * distance));    

    ambient *= attenuation;  
    diffuse *= attenuation;
    specular *= attenuation;   
    return (ambient + diffuse + specular);
}

vec3 CalcDirLight(vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-DirLight.direction);
	
    // Диффузное затенение
    float diff = max(dot(normal, lightDir), 0.0);
	
    // Отраженное затенение
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	
    // Совмещаем результаты
    vec3 ambient = DirLight.Dir_ambient;
    vec3 diffuse = DirLight.Dir_diffuse * diff;
    vec3 specular = DirLight.Dir_specular * spec;
    return (ambient + diffuse + specular);
}

/*
// Вычисляем цвет при использовании прожектора
vec3 CalcSpotLight(vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(SpotLight.position - fragPosition);
	
    // Диффузное затенение
    float diff = max(dot(normal, lightDir), 0.0);
	
    // Отраженное затенение
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	
    // Затухание
    float distance = length(SpotLight.position - fragPosition);
    float attenuation = 1.0 / (SpotLight.constant + SpotLight.linear * distance + SpotLight.quadratic * (distance * distance)); 
	
    // Интенсивность прожектора
    float theta = dot(lightDir, normalize(-SpotLight.direction)); 
    float epsilon = SpotLight.cutOff - SpotLight.outerCutOff;
    float intensity = clamp((theta - SpotLight.outerCutOff) / epsilon, 0.0, 1.0);
	
    // Совмещаем результаты
    vec3 ambient = SpotLight.ambient;
    vec3 diffuse = SpotLight.diffuse * diff;
    vec3 specular = SpotLight.specular * spec;
    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;
    return (ambient + diffuse + specular);
}
*/
