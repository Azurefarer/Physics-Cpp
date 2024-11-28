#version 330 core
layout (triangles) in;
layout (line_strip, max_vertices = 3) out;

in vec4 frag_pos[];
out vec3 normal;

void main() {
    vec3 edge1 = frag_pos[1] - frag_pos[0];
    vec3 edge2 = frag_pos[2] - frag_pos[0];

    normal = normalize(cross(edge1, edge2));

    for (int i=0; i<3; i++) {
        gl_Position = gl_in[i].gl_Position;
        EmitVertex();
    }
    EndPrimitive();
}