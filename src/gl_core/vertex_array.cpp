#include "gl_core/renderer.h"
#include "gl_core/vertex_array.h"
#include "gl_core/vertex_buffer.h"
#include "gl_core/vertex_buffer_layout.h"

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
    const auto& elements = layout.GetElements();
    for (unsigned int i=0; i<elements.size(); i++) {
        const auto& element = elements[i];
        int offset = 0;
        glEnableVertexAttribArray(i);
        glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.get_stride(), (const void*)0);
        offset += element.count * VertexBufferElement::get_size_of_type(element.type);
    }
}

void VertexArray::bind() {
    glBindVertexArray(m_renderer_ID);
}

void VertexArray::unbind() {
    glBindVertexArray(0);
}

void add_layout(VertexBufferLayout layout) {

}