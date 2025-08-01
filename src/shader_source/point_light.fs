#version 410 core
out vec4 FragColor;
in vec4 frag_pos;
in vec4 color;
in vec3 normal;
in vec2 TexCoord;
uniform sampler2D texture01;
uniform float time;

uniform vec4 h;
uniform vec4 light_color;
uniform vec4 light_pos;

vec4 ambient() {
    vec4 result;
    float ambient_strength = 0.25;
    result = color * ambient_strength;
    return result;
}

float diffuse(vec4 n) {    
    vec4 light_dir = normalize(light_pos-frag_pos);
    float diffuse = max(dot(n, light_dir), 0.0);
    return diffuse;
}

void main() {
    FragColor = ambient() * diffuse(vec4(normal, 0.0f)) + ambient();
}