#include "gl_aux/quad.h"

Quad::Quad() {
    m_verts = {
        {-0.5, -0.5, 0.0,  0.2, 0.7, 0.5,  1.0, 1.0},
        {0.5, -0.5, 0.0,  0.4, 0.9, 0.3,  0.0, 1.0},
        {0.5, 0.5, 0.0,  0.3, 0.7, 0.1,  0.0, 0.0},
        {-0.5, 0.5, 0.0,  0.9, 0.7, 0.1,  1.0, 0.0}
    };
    m_indices = {
        0, 1, 2,
        0, 2, 3
    };
    VertexArray va;
    // m_va = &va;
}

Quad::~Quad() {
    
}

void Quad::gpu_config() {
    VertexArray va;
    VertexBuffer vb(&m_verts);
	VertexBufferLayout layout;
    layout.push_float(3);
    layout.push_float(3);
    layout.push_float(2);
   	va.add_buffer(vb, layout);
    IndexBuffer ib(&m_indices);
}
