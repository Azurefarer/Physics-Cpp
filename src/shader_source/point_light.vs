#version 430 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in vec3 aNormal;
layout (location = 4) in float atex_index;

out vec3 UV;
out vec2 TexCoord;
out vec4 color;
out vec3 normal;

uniform float time;
uniform mat4 rot;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform vec4 light_pos;

void main()
{
    UV = aPos.rgb;
    TexCoord = aTexCoord;
    color = aColor;
    normal = aNormal;
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}