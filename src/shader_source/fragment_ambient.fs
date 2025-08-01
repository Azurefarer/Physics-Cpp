#version 410 core
out vec4 FragColor;
in vec2 TexCoord;
in vec3 UV;
in vec4 color;
uniform sampler2D texture01;
uniform float time;

void main() {
    float ambient_strength = 0.1;
    vec3 light_color = vec3(0.1, 0.1, 0.1);
    vec3 ambient = ambient_strength * light_color;

    vec3 result = ambient * color.rgb;
    FragColor = vec4(result, 1.0);
}