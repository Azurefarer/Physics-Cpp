#include "gl_core/shapes.h"

IndexBuffer::IndexBuffer(std::vector<unsigned int> data) {
    m_count = data.size();
    glGenBuffers(1, &m_renderer_ID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_renderer_ID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_count * sizeof(data)[0], &(data)[0], GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer() {
    glDeleteBuffers(1, &m_renderer_ID);
}

void IndexBuffer::bind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_renderer_ID);
}

void IndexBuffer::unbind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

VertexBuffer::VertexBuffer(std::vector<Vertex> data) {
    glGenBuffers(1, &m_renderer_ID);
    glBindBuffer(GL_ARRAY_BUFFER, m_renderer_ID);
    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(Vertex), &(data)[0], GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer() {
    glDeleteBuffers(1, &m_renderer_ID);
}

void VertexBuffer::bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, m_renderer_ID);
}

void VertexBuffer::unbind() const {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

VertexBufferLayout::VertexBufferLayout() {}

VertexBufferLayout::~VertexBufferLayout() {}

VertexArray::VertexArray() {
    glGenVertexArrays(1, &m_renderer_ID);
    glBindVertexArray(m_renderer_ID);
}

VertexArray::~VertexArray() {
    glDeleteVertexArrays(1, &m_renderer_ID);
}

void VertexArray::add_buffer(const VertexBuffer& vb, const VertexBufferLayout& layout) {
    bind();
    vb.bind();
    const auto& elements = layout.get_elements();
    uintptr_t offset = 0;
    for (unsigned int i=0; i<elements.size(); i++) {
        const auto& element = elements[i];
        glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.get_stride(), (const void*)offset);
        glEnableVertexAttribArray(i);
        offset += element.count * VertexBufferElement::get_size_of_type(element.type);
    }
}

void VertexArray::bind() {
    glBindVertexArray(m_renderer_ID);
}

void VertexArray::unbind() {
    glBindVertexArray(0);
}

Shape::Shape(std::string type) {

    m_va_ptr.reset(new VertexArray());
    m_vb_ptr.reset(new VertexBuffer(vertex_data));
    m_layout_ptr.reset(new VertexBufferLayout());
    m_layout_ptr.get()->push_float(3);
    m_layout_ptr.get()->push_float(4);
    m_layout_ptr.get()->push_float(2);
    m_layout_ptr.get()->push_float(3);
    m_layout_ptr.get()->push_float(1);
    m_va_ptr.get()->add_buffer((*m_vb_ptr.get()), (*m_layout_ptr.get()));
    m_ib_ptr.reset(new IndexBuffer(index_data));
    m_element_count = std::size(index_data);
}
// Shape::Shape(std::vector<Vertex> vertex_data, std::vector<unsigned int> index_data) {
//     m_va_ptr.reset(new VertexArray());
//     m_vb_ptr.reset(new VertexBuffer(vertex_data));
//     m_layout_ptr.reset(new VertexBufferLayout());
//     m_layout_ptr.get()->push_float(3);
//     m_layout_ptr.get()->push_float(4);
//     m_layout_ptr.get()->push_float(2);
//     m_layout_ptr.get()->push_float(3);
//     m_layout_ptr.get()->push_float(1);
//     m_va_ptr.get()->add_buffer((*m_vb_ptr.get()), (*m_layout_ptr.get()));
//     m_ib_ptr.reset(new IndexBuffer(index_data));
//     m_element_count = std::size(index_data);
// }

ShapeMan::ShapeMan() {
    Quad quad;
    Cube cube;
    shove_vertex_index_data("QUAD", quad.get_verts(), quad.get_indices());
    shove_vertex_index_data("CUBE", cube.get_verts(), cube.get_indices());
}

ShapeMan::~ShapeMan() {}

void ShapeMan::shove_vertex_index_data(std::string key, std::vector<Vertex> vertex_data, std::vector<unsigned int> index_data) {
    m_shapes[key] = std::make_unique<Shape>(vertex_data, index_data);
}

void ShapeMan::draw(std::string key) {
    (*m_shapes.at(key).get()).bind();
    glDrawElements(GL_TRIANGLES, (*m_shapes.at(key).get()).get_element_count(), GL_UNSIGNED_INT, (const void*)0);
    (*m_shapes.at(key).get()).unbind();
}
