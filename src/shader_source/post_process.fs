#version 430 core
out vec4 FragColor;
in vec2 TexCoord;
uniform sampler2D texture01;
uniform float time;

void main() {
    vec4 tex = texture(texture01, TexCoord);
    FragColor = vec4(0.0);
}