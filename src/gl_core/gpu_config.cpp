#include "gl_core/gpu_config.h"

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
