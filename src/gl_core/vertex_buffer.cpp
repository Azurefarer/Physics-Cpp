#include "gl_core/vertex_buffer.h"

VertexBuffer::VertexBuffer(std::vector<Vertex>* data) {
    glGenBuffers(1, &m_renderer_ID);
    glBindBuffer(GL_ARRAY_BUFFER, m_renderer_ID);
    glBufferData(GL_ARRAY_BUFFER, (*data).size() * sizeof(Vertex), &data[0], GL_STATIC_DRAW);
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