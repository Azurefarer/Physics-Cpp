#include "gl_core/gpu_config.h"

GpuConfig::GpuConfig() {
    
}

GpuConfig::~GpuConfig() {

}

void GpuConfig::shove_vertex_data(const char* key, std::vector<Vertex>* data) {
    VertexArray temp_va;
    m_shapes[key].name = key;
    m_shapes[key].va = temp_va;
    m_vb = new VertexBuffer(data);
    m_layout = new VertexBufferLayout();
    (*m_layout).push_float(3);
    (*m_layout).push_float(3);
    (*m_layout).push_float(2);
    m_shapes[key].va.add_buffer((*m_vb), (*m_layout));
}

void GpuConfig::shove_index_data(const char* key, std::vector<unsigned int>* data) {
    m_ib = new IndexBuffer(data);
    m_shapes[key].element_count = size(*data);
}

void GpuConfig::draw(const char* key) {
    m_shapes[key].va.bind();
    GL_call(glDrawElements(GL_TRIANGLES, m_element_count[key], GL_UNSIGNED_INT, (const void*)0));
    m_shapes[key].va.unbind();
}
