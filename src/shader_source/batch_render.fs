#version 430 core
out vec4 FragColor;

in vec2 TexCoord;
in vec3 normal;
in vec4 frag_pos;

uniform vec3 view;
uniform sampler2D texture01;
uniform float time;
uniform vec4 light_color;
uniform vec4 light_pos;
uniform float ambient_strength;

// Coefficients

uniform float fresnel_coeff = 10.0;
uniform float spec_coeff = 7.014;

void fragment() {
	float alpha = 1.0 - pow(abs(dot(normalize(normal), -view)), fresnel_coeff);
	FragColor = vec4(0.1, 0.3, 0.8, alpha);
}

void light() {
	#ifdef LIGHTING
		vec3 light = normalize((invViewMat * vec4(LIGHT, 0.0)).xyz);
		vec3 v = normalize((invViewMat * vec4(VIEW, 0.0)).xyz);
		vec3 norm = normalize(NORMAL);
		#ifdef DIFFUSE
			DIFFUSE_LIGHT += ALBEDO * clamp(dot(norm, -light), 0.0, 1.0);
		#endif
		#ifdef SPECULAR
			vec3 reflight = normalize(reflect(-LIGHT, NORMAL));
			vec3 h = normalize(VIEW + LIGHT);
			float spec = pow(clamp(dot(reflight, VIEW), 0.0, 1.0), spec_coeff);
			SPECULAR_LIGHT += spec;
		#endif
	#endif
}

vec4 ambient() {
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
    vec4 norm = normalize(vec4( normalize(normal), 0.0));
    FragColor = vec4(normal.x, -normal.y, normal.z,0.0);
    // FragColor = texture_color() * ambient() * diffuse(norm);
}
