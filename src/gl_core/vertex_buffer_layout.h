#pragma once
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
    private:
        std::vector<VertexBufferElement> m_elements;
        unsigned int m_stride;
    public:
        VertexBufferLayout();
        ~VertexBufferLayout();

        void push_float(unsigned int count) {
            m_elements.push_back({GL_FLOAT, count, GL_FALSE});
            m_stride += VertexBufferElement::get_size_of_type(GL_FLOAT);
        }

        void push_unsigned_int(unsigned int count) {
            m_elements.push_back({GL_UNSIGNED_INT, count, GL_FALSE});
            m_stride += VertexBufferElement::get_size_of_type(GL_UNSIGNED_INT);
        }

        void push_unsigned_char(unsigned int count) {
            m_elements.push_back({GL_UNSIGNED_BYTE, count, GL_TRUE});
            m_stride += VertexBufferElement::get_size_of_type(GL_UNSIGNED_BYTE);
        }

        inline const std::vector<VertexBufferElement> GetElements() const { return m_elements; }
        inline unsigned int get_stride() const { return m_stride; }
};
