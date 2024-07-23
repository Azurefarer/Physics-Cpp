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

struct Shape {
    std::string shape_id;
    std::unique_ptr<VertexArray> va{new VertexArray()};
    std::unique_ptr<VertexBuffer> vb;
    std::unique_ptr<VertexBufferLayout> layout{new VertexBufferLayout()};
    std::unique_ptr<IndexBuffer> ib;
    unsigned int element_count;
    Shape();
    Shape(std::string name, std::vector<Vertex>* vertex_data, std::vector<unsigned int>* index_data);

};

class ShapesDict {
    public:
        ShapesDict();
        ~ShapesDict();

        void shove_vertex_index_data(std::string key, std::vector<Vertex>* data, std::vector<unsigned int>* index_data);

        void draw(std::string key);

        // FIXME: would like this to be marked as const,  but throws
        // "passing 'const std::map<const char*, Shape>' as 'this' argument discards qualifiers"
        Shape get_shape(std::string key) { return m_shapes[key]; }

        void bind_vertex_array(std::string key) { (*m_shapes[key].va).bind(); }
        void unbind_vertex_array(std::string key) { (*m_shapes[key].va).unbind(); }

    private:
        std::map<std::string, Shape> m_shapes;
    };
#endif
