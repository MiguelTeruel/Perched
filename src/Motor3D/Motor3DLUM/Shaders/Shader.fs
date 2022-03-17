#version 330 core

out vec4 FragColor;

in vec2 TexCoords;
in vec3 Normal;  
in vec3 FragPos;

uniform sampler2D texture_diffuse1;

uniform vec3 viewPos;
uniform vec3 lightColor;
uniform vec3 lightPos;

uniform float Ka;
uniform float Kd;

void main()
{ 
    //float Ka = 0.9;
    //float Kd = 0.7;

    //ambient
    vec3 ambientColor = lightColor;
    //difusse
    vec3 diffuseColor = lightColor;
    vec3 norm = normalize(Normal);
    
    vec3 lightDir = normalize(lightPos - FragPos);  
    float density = 100.0;
    
    vec2 screenCoord = vec2(gl_FragCoord.x/600.0, gl_FragCoord.y/600.0);
    vec2 fractional = fract(density * screenCoord);
    vec2 closestCircle = 2.0 * fractional - 1.0;
    float distFromCircle = length(closestCircle);

    float intensity = min(max(0.0, dot(norm, lightDir)), 0.9);
    float radius = 1.1 - intensity;
    vec3 color = mix(Ka*ambientColor, Kd*diffuseColor, step(radius, distFromCircle));
    

    vec4 text = texture(texture_diffuse1, TexCoords); 
    FragColor = vec4(color, 1.0)*text;

}