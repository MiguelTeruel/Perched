#version 430 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;
 
out vec2 TexCoords;
out vec3 FragPos;  
out vec3 Normal;
out float gl_ClipDistance[6];

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 projViewModel;
uniform float scale;

uniform vec4 clipPlaneTop;
uniform vec4 clipPlaneBot;
uniform vec4 clipPlaneRht;
uniform vec4 clipPlaneLft;
uniform vec4 clipPlaneNer;
uniform vec4 clipPlaneFar;

void main()
{
    TexCoords = aTexCoords; 
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    gl_ClipDistance[0] = dot(model * vec4(aPos,1.0), clipPlaneTop);
    gl_ClipDistance[1] = dot(model * vec4(aPos,1.0), clipPlaneBot);
    gl_ClipDistance[2] = dot(model * vec4(aPos,1.0), clipPlaneRht);
    gl_ClipDistance[3] = dot(model * vec4(aPos,1.0), clipPlaneLft);
    gl_ClipDistance[4] = dot(model * vec4(aPos,1.0), clipPlaneNer);
    gl_ClipDistance[5] = dot(model * vec4(aPos,1.0), clipPlaneFar);
    FragPos = vec3(model * vec4(aPos, 1.0));
    Normal = aNormal;
}