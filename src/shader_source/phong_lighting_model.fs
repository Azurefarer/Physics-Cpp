#version 410 core

out vec4 FragColor;
in vec2 TexCoord;
in vec4 color;
in vec3 normal;
in vec4 frag_pos;

uniform sampler2D texture01;
uniform float time;
uniform vec4 light_color;
uniform vec4 light_pos;
uniform float ambient_strength;

vec4 phong() {
    vec4 ambient = ambient_strength * light_color;
    return ambient;
}

float diffuse(vec4 n) {    
    vec4 light_dir = normalize(light_pos-frag_pos);
    float diffuse = max(dot(n, light_dir), 0.0);
    return diffuse;
}

vec4 texture_color() {
    vec4 tex = texture(texture01, TexCoord);
    return tex;
}

void main() {
    vec4 norm = vec4( normalize(normal), 0.0);
    FragColor = color * texture_color() * phong() * diffuse(norm);
}
