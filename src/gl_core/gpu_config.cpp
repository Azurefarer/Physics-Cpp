#include "gl_core/gpu_config.h"

IndexBuffer::IndexBuffer(std::vector<unsigned int>* data) {
    m_count = (*data).size();
    GL_call(glGenBuffers(1, &m_renderer_ID));
    GL_call(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_renderer_ID));
    GL_call(glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_count * sizeof(*data)[0], &(*data)[0], GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer() {
    GL_call(glDeleteBuffers(1, &m_renderer_ID));
}

void IndexBuffer::bind() const {
    GL_call(glBindBuffer(GL_ARRAY_BUFFER, m_renderer_ID));
}

void IndexBuffer::unbind() const {
    GL_call(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

VertexArray::VertexArray() {
    GL_call(glGenVertexArrays(1, &m_renderer_ID));
    GL_call(glBindVertexArray(m_renderer_ID));
}
VertexArray::~VertexArray() {
    GL_call(glDeleteVertexArrays(1, &m_renderer_ID));
}

void VertexArray::add_buffer(const VertexBuffer& vb, const VertexBufferLayout& layout) {
    bind();
    vb.bind();
    const auto& elements = layout.get_elements();
    uintptr_t offset = 0;
    for (unsigned int i=0; i<elements.size(); i++) {
        const auto& element = elements[i];
        GL_call(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.get_stride(), (const void*)offset));
        GL_call(glEnableVertexAttribArray(i));
        offset += element.count * VertexBufferElement::get_size_of_type(element.type);
    }
}

void VertexArray::bind() {
    GL_call(glBindVertexArray(m_renderer_ID));
}

void VertexArray::unbind() {
    GL_call(glBindVertexArray(0));
}

VertexBuffer::VertexBuffer(std::vector<Vertex>* data) {
    GL_call(glGenBuffers(1, &m_renderer_ID));
    GL_call(glBindBuffer(GL_ARRAY_BUFFER, m_renderer_ID));
    GL_call(glBufferData(GL_ARRAY_BUFFER, (*data).size() * sizeof(Vertex), &(*data)[0], GL_STATIC_DRAW));
}

VertexBuffer::~VertexBuffer() {
    GL_call(glDeleteBuffers(1, &m_renderer_ID));
}

void VertexBuffer::bind() const {
    GL_call(glBindBuffer(GL_ARRAY_BUFFER, m_renderer_ID));
}

void VertexBuffer::unbind() const {
    GL_call(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

VertexBufferLayout::VertexBufferLayout() {}

VertexBufferLayout::~VertexBufferLayout() {}

