#include "gl_core/gpu_config.h"

GpuConfig::GpuConfig() {
    
}

GpuConfig::~GpuConfig() {

}

void GpuConfig::shove_vertex_index_data(const char* key, std::vector<Vertex>* vertex_data, std::vector<unsigned int>* index_data) {
    m_shapes[key].name = key;
    m_shapes[key].va = (new VertexArray());
    m_shapes[key].vb = (new VertexBuffer(vertex_data));
    m_shapes[key].layout = (new VertexBufferLayout());
    (*m_shapes[key].layout).push_float(3);
    (*m_shapes[key].layout).push_float(3);
    (*m_shapes[key].layout).push_float(2);
    (*m_shapes[key].va).add_buffer((*m_shapes[key].vb), (*m_shapes[key].layout));
    m_shapes[key].ib = (new IndexBuffer(index_data));
    m_shapes[key].element_count = size(*index_data);
}

void GpuConfig::draw(const char* key) {
    (*m_shapes[key].va).bind();
    GL_call(glDrawElements(GL_TRIANGLES, m_shapes[key].element_count, GL_UNSIGNED_INT, (const void*)0));
    (*m_shapes[key].va).unbind();
}
