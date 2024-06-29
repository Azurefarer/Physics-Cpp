#include "gl_core/renderer.h"
#include "gl_core/index_buffer.h"

IndexBuffer::IndexBuffer(const void* data, unsigned int count) {
    m_count = count;
    glGenBuffers(1, &m_renderer_ID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_renderer_ID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer() {
    glDeleteBuffers(1, &m_renderer_ID);
}

void IndexBuffer::bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, m_renderer_ID);
}

void IndexBuffer::unbind() const {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}