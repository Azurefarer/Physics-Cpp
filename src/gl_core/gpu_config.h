#ifndef GL_CORE_GPU_CONFIG_H_
#define GL_CORE_GPU_CONFIG_H_

#include <map>
#include <memory>

#include "gl_core/renderer.h"
#include "gl_core/vertex_array.h"
#include "gl_core/vertex_buffer.h"
#include "gl_core/vertex_buffer_layout.h"
#include "gl_core/index_buffer.h"

struct Shape {
    const char* name;
    VertexArray* va;
    VertexBuffer* vb;
    VertexBufferLayout* layout;
    IndexBuffer* ib;
    unsigned int element_count;
};

class GpuConfig {
    public:
        GpuConfig();
        ~GpuConfig();

        void shove_vertex_index_data(const char* key, std::vector<Vertex>* data, std::vector<unsigned int>* index_data);

        void draw(const char* key);

        // FIXME: would like this to be marked as const,  but throws
        // "passing 'const std::map<const char*, Shape>' as 'this' argument discards qualifiers"
        Shape get_shape(const char* key) { return m_shapes[key]; }

        void bind_vertex_array(const char* key) { (*m_shapes[key].va).bind(); }
        void unbind_vertex_array(const char* key) { (*m_shapes[key].va).unbind(); }

    private:
        std::map<const char*, Shape> m_shapes;
    };
#endif
