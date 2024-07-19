#ifndef GL_CORE_VERTEX_BUFFER_LAYOUT_H_
#define GL_CORE_VERTEX_BUFFER_LAYOUT_H_

#include <vector>
#include "gl_core/renderer.h"

struct VertexBufferElement {
    unsigned int type;
    unsigned int count;
    unsigned char normalized;

    static unsigned int get_size_of_type(unsigned int type) {
        switch (type) {
            case GL_FLOAT: return 4;
            case GL_UNSIGNED_INT: return 4;
            case GL_UNSIGNED_BYTE: return 1;
        }
        return 0;
    }
};

class VertexBufferLayout {
    public:
        VertexBufferLayout();
        ~VertexBufferLayout();

        void push_float(unsigned int count) {
            m_elements.push_back({GL_FLOAT, count, GL_FALSE});
            m_stride += count * VertexBufferElement::get_size_of_type(GL_FLOAT);
        }

        void push_unsigned_int(unsigned int count) {
            m_elements.push_back({GL_UNSIGNED_INT, count, GL_FALSE});
            m_stride += count * VertexBufferElement::get_size_of_type(GL_UNSIGNED_INT);
        }

        void push_unsigned_char(unsigned int count) {
            m_elements.push_back({GL_UNSIGNED_BYTE, count, GL_TRUE});
            m_stride += count * VertexBufferElement::get_size_of_type(GL_UNSIGNED_BYTE);
        }

        const std::vector<VertexBufferElement> get_elements() const { return m_elements; }
        unsigned int get_stride() const { return m_stride; }

    private:
        std::vector<VertexBufferElement> m_elements;
        unsigned int m_stride = 0;
};
#endif
