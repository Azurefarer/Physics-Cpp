#version 430 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in vec3 aNormal;
out vec2 TexCoord;
out vec4 color;
out vec3 normal;
out vec4 frag_pos;

uniform float time;
uniform mat4 rot;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat3 normal_matrix;

void main() {
    TexCoord = aTexCoord;
    color = aColor;
    normal = normal_matrix * aNormal;
    frag_pos = model * vec4(aPos, 0.0);
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}