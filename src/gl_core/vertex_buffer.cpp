#include "gl_core/vertex_buffer.h"

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
