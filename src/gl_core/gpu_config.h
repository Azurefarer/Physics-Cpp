#ifndef GL_CORE_GPU_CONFIG_H_
#define GL_CORE_GPU_CONFIG_H_

#include <stdint.h>
#include <vector>

#include "glad/glad.h"

#include "gl_aux/vertex.h"

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

class IndexBuffer {
    public:
        IndexBuffer(std::vector<unsigned int> data);
        ~IndexBuffer();

        void bind() const;
        void unbind() const;

        unsigned int get_count() const { return m_count; }
    private:
        unsigned int m_renderer_ID = 1;
        unsigned int m_count = 0;
};

class VertexBuffer {
    public:
        VertexBuffer(std::vector<Vertex> data);
        ~VertexBuffer();

        void bind() const;
        void unbind() const;
    private:
        unsigned int m_renderer_ID = 1;
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

class VertexArray {
    public:
        VertexArray();
        ~VertexArray();

        void add_buffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
        void bind();
        void unbind();

    private:
        unsigned int m_renderer_ID = 1;
};

#endif
