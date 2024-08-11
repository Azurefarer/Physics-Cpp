#version 330 core
out vec4 FragColor;
in vec4 color;
uniform sampler2D texture01;
uniform float time;

void main() {
    vec4 light_color = vec4(1.0f);
    FragColor = light_color;
}