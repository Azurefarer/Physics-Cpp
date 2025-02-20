#version 430 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in vec3 aNormal;
out vec4 frag_pos;
out vec4 color;
out vec3 normal;
out vec2 tex_coord;

const float PI = 3.1415;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat3 normal_matrix;

float amp = 300;
float user_radius = 200;

vec3 surface(vec3 pos) {
    vec3 surface;
    surface.x = pos.x;
    surface.z = pos.z;
    float r = sqrt(pow(surface.x, 2) + pow(surface.z, 2));
    surface.y = amp * cos(PI/2 * r/user_radius);
    return surface;
}
vec3 gradient(vec3 surface) {
    vec3 gradient;
    float r = sqrt(pow(surface.x, 2) + pow(surface.z, 2));
    float consts = -amp*PI/2/user_radius;
    float dsdx = consts * sin(PI/2 * r/user_radius) * surface.x/r;
    float dsdz = consts * sin(PI/2 * r/user_radius) * surface.z/r;
    gradient = vec3(dsdx, 1.0, dsdz); 
    return normalize(gradient);
    // dsdx is positive as we go from -x to +x on the left side of the curve.  This generates colors that contradict
    // world coords.  From the camera's perspective, the right is the +x direction so normals pointing in that
    // direction should be red (1.0, 0, 0).  however, the normals calculated by (dsdx, 1.0, dsdz) are positive
    // on the left side of the surface (i.e. normals pointing to the left are red) because dsdx is computed as x goes
    // from - to +.  So from the left to right on screen we ascend up the surface resulting in a + values for dsdx.
}

void main() {
    vec3 surface = surface(aPos);
    vec3 gradient = gradient(surface);
    normal = normal_matrix * gradient;
    gl_Position = projection * view * model * vec4(surface, 1.0);

    frag_pos = vec4(aPos, 0.0);
    // frag_pos = model * vec4(surface, 1.0);
    // frag_pos = view * model * vec4(pos, 1.0);
    // frag_pos = projection * view * model * vec4(pos, 1.0);

    color = aColor;
    tex_coord = aTexCoord;
}