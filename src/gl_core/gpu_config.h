#ifndef GL_CORE_GPU_CONFIG_H_
#define GL_CORE_GPU_CONFIG_H_

#include <map>
#include <memory>
#include <string>

#include "gl_core/renderer.h"
#include "gl_core/vertex_array.h"
#include "gl_core/vertex_buffer.h"
#include "gl_core/vertex_buffer_layout.h"
#include "gl_core/index_buffer.h"

class Shape {
    public:
        Shape(std::vector<Vertex>* vertex_data, std::vector<unsigned int>* index_data);
        ~Shape();

    private:
        std::unique_ptr<VertexArray> m_va_ptr;
        std::unique_ptr<VertexBuffer> m_vb_ptr;
        std::unique_ptr<VertexBufferLayout> m_layout_ptr;
        unsigned int element_count;    
};

// struct Shape {
//     VertexArray va;
//     VertexBuffer vb;
//     VertexBufferLayout layout;
//     unsigned int element_count;
//     Shape(std::vector<Vertex>* vertex_data, std::vector<unsigned int>* index_data);
// };

class ShapesDict {
    public:
        ShapesDict();
        ~ShapesDict();

        void shove_vertex_index_data(std::string key, std::vector<Vertex>* data, std::vector<unsigned int>* index_data);

        void draw(std::string key);

        // FIXME: would like this to be marked as const,  but throws
        // "passing 'const std::map<const char*, Shape>' as 'this' argument discards qualifiers"
        struct Shape get_shape(std::string key) { return m_shapes.at(key); }

    private:
        std::map<std::string, Shape> m_shapes;
    };
#endif
