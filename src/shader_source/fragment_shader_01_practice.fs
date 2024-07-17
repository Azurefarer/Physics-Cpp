#version 330 core
out vec4 FragColor;
in vec2 TexCoord;
in vec3 UV;
in vec3 color;
uniform sampler2D texture01;
uniform sampler2D texture02;
uniform float time;

void main() {
    vec4 king_tex = texture(texture01, TexCoord);
    vec4 awesome_tex = texture(texture02, TexCoord);
    vec4 mix_tex = mix(king_tex, awesome_tex, 0.5);
    FragColor = mix_tex;
    FragColor *= vec4(color, 1.0);
}