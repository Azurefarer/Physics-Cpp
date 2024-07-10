#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;
out vec3 UV;
out vec2 TexCoord;
out vec3 color;
uniform float time;

vec2 rotation(vec2 pos, float t) {
    vec2 rotated;
    mat2 rot = mat2(vec2(cos(t), sin(t)), vec2(-sin(t), cos(t)));
    rotated = rot * pos;
    return rotated;
}

void main()
{
    vec2 rotated_positions = rotation(aPos.xy, time);
    gl_Position = vec4(rotated_positions, aPos.z, 1.0);
    gl_Position = vec4(aPos, 1.0);
	UV = aPos.rgb;
    TexCoord = aTexCoord;
    color = aColor;
}