#version 430 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in vec3 aNormal;

out vec3 normal;
out vec4 frag_pos;
out vec2 TexCoord;

uniform float time;
uniform mat4 rot;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat3 normal_matrix;

const int num_sines = 8;
const float PI = 3.1415;

uniform float v_amplitude_mult; // credit to acerola
uniform float v_amplitude; // credit to acerola
uniform float v_omega_mult; // credit to acerola
uniform float v_omega; // credit to acerola
uniform float v_lambda_mult; // credit to acerola
uniform float v_lambda; // credit to acerola
uniform float v_peak_width;

struct Wave {
	vec2[num_sines] v; // velocity
	vec2 pos; // position
	vec2[num_sines] w; // angular frequency
	vec2[num_sines] k; // wave number
	vec2[num_sines] p; // phase
	vec2[num_sines] a; // amplitude
};

Wave wave_gen() {
    // y(x, z)  The wave lives in the x, z plane with displacement on the y-axis
    Wave w;
	float a = v_amplitude;
	float f = v_omega;
	float wav = v_lambda;
	for (int i = 0; i <= (num_sines-1); i++) {
		w.a[i] = vec2(a); 
		w.w[i] = vec2(2.0 * PI * f); // angular frequency
		w.k[i] = vec2(2.0 * PI / wav); // Wave number
		w.v[i] = vec2(w.w[i] / w.k[i]);
		w.p[i] = vec2(w.v[i] * (2.0 * PI / w.k[i]));
		a *= v_amplitude_mult;
		f *= v_omega_mult;
		wav *= v_lambda_mult;
	}
	return w;
}

vec3 sum_of_sines_gauss_adjacent(float time, Wave w) {
    vec3 wave_data = vec3(0.0);
	float height = 0.0;
	float dwdx = 0.0;
	float dwdz = 0.0;
	vec2 dwdxz = vec2(0.0);
	for (int i = 0; i < (num_sines); i++) {
		float j = float(i) * 45.0 * PI / 180.0;
		float amp = w.a[i].x * w.a[i].y;
		// Gaussian deviation
        mat2 rot = mat2(vec2(cos(j), -sin(j)), vec2(sin(j), cos(j)));
        vec2 RotPos = rot * w.pos;
        float x = RotPos.x * w.k[i].x - time * w.w[i].x;
        float z = RotPos.y * w.k[i].y - time * w.w[i].y;
        float s = v_peak_width;
        float b = pow(sin(x)*cos(z)/s, 2.0);
        // height += amp * exp(1.0-b);
        height += exp(1.0-b);
        
        // Normals rotate opposite to the geometry so we need to negate the rotation here
        float _dxdx = w.k[i].x*cos(-j);
        float _dzdx = w.k[i].y*sin(-j);
        float _dxdz = -w.k[i].x*sin(-j);
        float _dzdz = w.k[i].y*cos(-j);
        mat2 _Differentials = mat2(vec2(_dxdx, _dxdz), vec2(_dzdx, _dzdz));

        float _Constants = 2.0 * amp / pow(s, 2.0);
        vec2 _TrigFcts = vec2(sin(x) * cos(x) * pow(cos(z), 2.0), -sin(z) * cos(z) * pow(sin(x), 2.0));
        
        dwdxz += -_Constants * (_Differentials * _TrigFcts) * exp(1.0 - b);
        wave_data = vec3(height, dwdxz);
    }
  	return wave_data;
}

vec3 sum_of_sines_gauss_simple(float time, Wave w) {
    vec3 wave_data = vec3(0.0);
	float height = 0.0;
	float dwdx = 0.0;
	float dwdz = 0.0;
	vec2 dwdxz = vec2(0.0);
	for (int i = 0; i < (num_sines); i++) {
		float j = float(i) * 45.0 * PI / 180.0;
		float amp = w.a[i].x * w.a[i].y;
        // Simplified Guassian
        mat2 rot = mat2(vec2(cos(j), -sin(j)), vec2(sin(j), cos(j)));
        vec2 RotPos = rot * w.pos;
        float x = RotPos.x * w.k[i].x - time * w.w[i].x;
        float z = RotPos.y * w.k[i].y - time * w.w[i].y;
        float a = x + z;
        float s = v_peak_width;
        float b = pow(sin(a)/s, 2.0);
        height += amp * exp(1.0-b);
        
        float _dxdx = w.k[i].x*cos(j);
        float _dzdx = w.k[i].y*sin(j);
        float _dxdz = -w.k[i].x*sin(j);
        float _dzdz = w.k[i].y*cos(j);				
        mat2 _Differentials = mat2(vec2(_dxdx, _dxdz), vec2(_dzdx, _dzdz));

        float _Constants = 2.0 * amp / pow(s, 2.0);
        float _TrigFctsx = sin(a) * cos(a) * (_dxdx + _dzdx);
        float _TrigFctsz = sin(a) * cos(a) * (_dzdx + _dzdz);
        
//			RotPos = normalize(RotPos);
        dwdx += RotPos.x * _Constants * _TrigFctsx * exp(1.0 - b);
        dwdx += RotPos.y * _Constants * _TrigFctsz * exp(1.0 - b);
        wave_data = vec3(height, dwdx, dwdz);
    }
	return wave_data;
}

void vertex() {
	Wave water_wave = wave_gen();
    water_wave.pos = vec2(aPos.x, aPos.z);

	vec3 wave_data = sum_of_sines_gauss_adjacent(time, water_wave);
	float wave_height = wave_data.x;

    vec4 wave_vertex = vec4(aPos, 1.0);
	wave_vertex.y = wave_height;

	vec3 tangent = normalize(vec3(1.0, wave_data.y, 0.0));
	vec3 binormal = normalize(vec3(0.0, wave_data.z, 1.0));
	normal = cross(tangent, binormal);
	gl_Position = projection * view * model * vec4(aPos.x, wave_height, aPos.z, 1.0);
	normal = normal_matrix * normal;	
//	NORMAL = MODEL_NORMAL_MATRIX * NORMAL;
}

void main() {
    TexCoord = aTexCoord;
    frag_pos = model * vec4(aPos, 0.0);
    vertex();
}
