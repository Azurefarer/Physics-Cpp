#version 330 core
out vec4 FragColor;
in vec2 TexCoord;
in vec3 UV;
in vec4 color;
uniform sampler2D texture01;
uniform float time;

void main() {
    vec4 tex = texture(texture01, TexCoord);
    FragColor = tex;
    FragColor *= color;
}