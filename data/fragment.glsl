#version 410 core

in vec3 normal;
in vec3 fragment;
in vec2 uv;

out vec4 fragmentColor;

void main()
{
    vec3 lightSource = vec3(1.2f, 1.0f, 2.0f);
    vec3 eye = vec3(0.0f, 0.0f, 3.0f);

    vec3 light = vec3(1.0f, 1.0f, 1.0f);
    vec3 object = vec3(0.0f, 1.0f, 0.0f);

// Phong Illumination Logic Provided By:
// learnopengl.com

    // ambient
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * light;
  	
    // diffuse 
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(lightSource - fragment);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * light;
    
    // specular
    float specularStrength = 0.5f;
    vec3 viewDir = normalize(eye - fragment);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * light;  
        
    vec3 result = (ambient + diffuse + specular) * object;
    fragmentColor = vec4(result, 1.0);
}