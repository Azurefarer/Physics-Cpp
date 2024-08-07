#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;
out vec3 UV;
out vec2 TexCoord;
out vec3 color;
uniform float time;
uniform mat4 rot;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
	UV = aPos.rgb;
    TexCoord = aTexCoord;
    color = aColor;
}