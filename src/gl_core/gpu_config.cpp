#include "gl_core/gpu_config.h"

GpuConfig::GpuConfig() {
    
}

GpuConfig::~GpuConfig() {

}

void GpuConfig::shove_vertex_data(std::vector<Vertex>* data) {
    VertexArray temp_va;
    m_va.push_back(temp_va);
    VertexBuffer temp_vb(data);
    VertexBufferLayout temp_layout;
    temp_layout.push_float(3);
    temp_layout.push_float(3);
    temp_layout.push_float(2);
    m_va[0].add_buffer(temp_vb, temp_layout);
}

void GpuConfig::shove_index_data(std::vector<unsigned int>* data) {
    IndexBuffer temp_ib(data);
}
