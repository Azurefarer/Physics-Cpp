#include "gl_core/shape_man.h"

Shape::Shape(std::vector<Vertex>* vertex_data, std::vector<unsigned int>* index_data) {
    m_va_ptr.reset(new VertexArray());
    m_vb_ptr.reset(new VertexBuffer(vertex_data));
    m_layout_ptr.reset(new VertexBufferLayout());
    (*m_layout_ptr.get()).push_float(3);
    (*m_layout_ptr.get()).push_float(3);
    (*m_layout_ptr.get()).push_float(2);
    (*m_va_ptr.get()).add_buffer((*m_vb_ptr.get()), (*m_layout_ptr.get()));
    m_ib_ptr.reset(new IndexBuffer(index_data));
    m_element_count = std::size(*index_data);
}

Shape::~Shape() {}

ShapeMan::ShapeMan() {}

ShapeMan::~ShapeMan() {}

void ShapeMan::shove_vertex_index_data(std::string key, std::vector<Vertex>* vertex_data, std::vector<unsigned int>* index_data) {
    m_shapes[key] = std::make_unique<Shape>(vertex_data, index_data);
}

void ShapeMan::draw(std::string key) {
    (*m_shapes.at(key).get()).bind();
    GL_call(glDrawElements(GL_TRIANGLES, (*m_shapes.at(key).get()).get_element_count(), GL_UNSIGNED_INT, (const void*)0));
    (*m_shapes.at(key).get()).unbind();
}
