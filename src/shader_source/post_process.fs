#version 430 core
out vec4 FragColor;
in vec4 frag_pos;
in vec3 normal;
in vec2 TexCoord;
in vec4 color;

uniform sampler2D texture01;
uniform vec4 light_color;
uniform vec4 light_pos;
uniform float time;

vec4 toon(vec4 n) {
    vec4 toon;

    vec4 light_dir = normalize(light_pos-frag_pos);
    float toon_coeff = max(dot(n, light_dir), 0.0);
    toon_coeff = smoothstep(0.0, 1.0, toon_coeff);
    toon = color * toon_coeff;

    return toon;
}

void main() {
    vec4 tex = texture(texture01, TexCoord);
    vec4 norm = vec4(normalize(normal), 0.0);
    FragColor = toon(norm);
}