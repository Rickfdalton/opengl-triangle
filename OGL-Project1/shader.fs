#version 330 core
out vec4 FragColor;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
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
    FragColor = vec4 ( (ambient+diffuse) * objectColor,1.0) ;
}
