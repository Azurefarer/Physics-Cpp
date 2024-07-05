#include "gl_core/renderer.h"
#include "gl_core/index_buffer.h"

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