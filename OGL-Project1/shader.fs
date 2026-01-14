#version 330 core
out vec4 FragColor;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;
in vec3 Normal;
in vec3 FragPos;


void main()
{
    float ambient_strength = 0.1;
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir),0.0);

    vec3 ambient = ambient_strength * lightColor;
    vec3 diffuse = diff * lightColor;

    float specular_strength = 0.8;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir,norm); 
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 64);
    vec3 specular = specular_strength * spec * lightColor;  

    FragColor = vec4 ( (ambient+diffuse+specular) * objectColor,1.0) ;
}
