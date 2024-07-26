#ifndef GL_CORE_SHAPE_DICT_H_
#define GL_CORE_SHAPE_DICT_H_

#include <map>
#include <memory>
#include <string>

#include "gl_core/renderer.h"
#include "gl_core/gpu_config.h"

class Shape {
    public:
        Shape(std::vector<Vertex>* vertex_data, std::vector<unsigned int>* index_data);
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

class ShapeDict {
    public:
        ShapeDict();
        ~ShapeDict();

        void shove_vertex_index_data(std::string key, std::vector<Vertex>* vertex_data, std::vector<unsigned int>* index_data);

        void draw(std::string key);

    private:
        std::map<std::string, std::unique_ptr<Shape>> m_shapes;
    };
#endif
