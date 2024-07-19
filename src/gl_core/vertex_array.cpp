#include "gl_core/vertex_array.h"

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
