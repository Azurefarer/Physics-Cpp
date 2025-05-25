#ifndef GL_CORE_SHAPE_MAN_H_
#define GL_CORE_SHAPE_MAN_H_

#include <map>
#include <memory>
#include <stdint.h>
#include <string>
#include <vector>

#include "glad/glad.h"

#include "gl_aux/cube.h"
#include "gl_aux/quad.h"
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

template <typename T>
class Shape {
    public:
        Shape(const T& type) {
            m_va_ptr.reset(new VertexArray());
            m_vb_ptr.reset(new VertexBuffer(type.get_verts()));
            m_layout_ptr.reset(new VertexBufferLayout());
            m_layout_ptr.get()->push_float(3);
            m_layout_ptr.get()->push_float(4);
            m_layout_ptr.get()->push_float(2);
            m_layout_ptr.get()->push_float(3);
            m_layout_ptr.get()->push_float(1);
            m_va_ptr.get()->add_buffer((*m_vb_ptr.get()), (*m_layout_ptr.get()));
            m_ib_ptr.reset(new IndexBuffer(type.get_indices()));
            m_element_count = std::size(type.get_indices());
        }
        // Shape(std::vector<Vertex> vertex_data, std::vector<unsigned int> index_data);
        ~Shape();

        void bind() const { (*m_va_ptr.get()).bind(); }
        void unbind() const { (*m_va_ptr.get()).unbind(); }

        unsigned int get_element_count() const { return m_element_count; }

    private:
        std::unique_ptr<VertexArray> m_va_ptr;
        std::unique_ptr<VertexBuffer> m_vb_ptr;
        std::unique_ptr<VertexBufferLayout> m_layout_ptr;
        std::unique_ptr<IndexBuffer> m_ib_ptr;
        unsigned int m_element_count;
};

class ShapeMan {
    public:
        ShapeMan();
        ~ShapeMan();

        void shove_vertex_index_data(std::string key, std::vector<Vertex> vertex_data, std::vector<unsigned int> index_data);

        void draw(std::string key);

    private:
        std::map<std::string, std::unique_ptr<Shape>> m_shapes;
    };

#endif
