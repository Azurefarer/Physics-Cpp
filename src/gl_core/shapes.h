#ifndef GL_CORE_SHAPE_MAN_H_
#define GL_CORE_SHAPE_MAN_H_

#include <map>
#include <memory>
#include <stdint.h>
#include <string>
#include <vector>

#include "glad/glad.h"

#include "gl_core/vertex.h"

extern const std::vector<Vertex> cube_vertices;
extern const std::vector<unsigned int> cube_indices;
extern const std::vector<Vertex> quad_vertices;
extern const std::vector<unsigned int> quad_indices;

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
        IndexBuffer(const std::vector<unsigned int>& data);
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
        VertexBuffer(const std::vector<Vertex>& data);
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

class Shape {
    public:
        Shape(int shape) {
            m_va_ptr.reset(new VertexArray());
            m_vb_ptr.reset(new VertexBuffer(cube_vertices));
            m_layout_ptr.reset(new VertexBufferLayout());
            m_layout_ptr.get()->push_float(13); // 13 floats per vertex
            m_va_ptr.get()->add_buffer((*m_vb_ptr.get()), (*m_layout_ptr.get()));
            m_ib_ptr.reset(new IndexBuffer(cube_indices));
            m_element_count = std::size(cube_indices);
        }
        void bind() const { (*m_va_ptr.get()).bind(); }
        void unbind() const { (*m_va_ptr.get()).unbind(); }
        void draw() {
            bind();
            glDrawElements(GL_TRIANGLES, m_element_count, GL_UNSIGNED_INT, (const void*)0);
            unbind();
        }
        unsigned int get_element_count() const { return m_element_count; }

    private:
        std::unique_ptr<VertexArray> m_va_ptr;
        std::unique_ptr<VertexBuffer> m_vb_ptr;
        std::unique_ptr<VertexBufferLayout> m_layout_ptr;
        std::unique_ptr<IndexBuffer> m_ib_ptr;
        unsigned int m_element_count;
};

#endif
