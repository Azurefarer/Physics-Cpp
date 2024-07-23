#include "gl_core/gpu_config.h"

Shape::Shape(std::string name, std::vector<Vertex>* vertex_data, std::vector<unsigned int>* index_data) {
    shape_id = name;
    vb.reset(new VertexBuffer(vertex_data));
    ib.reset(new IndexBuffer(index_data));
    element_count = std::size(*index_data);
}


ShapesDict::ShapesDict() {
    
}

ShapesDict::~ShapesDict() {

}

void ShapesDict::shove_vertex_index_data(std::string key, std::vector<Vertex>* vertex_data, std::vector<unsigned int>* index_data) {
    // m_shapes[key].name = key;
    // m_shapes[key].va = (new VertexArray());
    // m_shapes[key].vb = (new VertexBuffer(vertex_data));
    // m_shapes[key].layout = (new VertexBufferLayout());
    // (*m_shapes[key].layout).push_float(3);
    // (*m_shapes[key].layout).push_float(3);
    // (*m_shapes[key].layout).push_float(2);
    // (*m_shapes[key].va).add_buffer((*m_shapes[key].vb), (*m_shapes[key].layout));
    // m_shapes[key].ib = (new IndexBuffer(index_data));
    // m_shapes[key].element_count = size(*index_data);
    Shape shape(key, vertex_data, index_data);
    m_shapes[key] = shape;    

}

void ShapesDict::draw(std::string key) {
    (*m_shapes[key].va).bind();
    GL_call(glDrawElements(GL_TRIANGLES, m_shapes[key].element_count, GL_UNSIGNED_INT, (const void*)0));
    (*m_shapes[key].va).unbind();
}
