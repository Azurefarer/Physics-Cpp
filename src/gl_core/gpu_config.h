#ifndef GL_CORE_GPU_CONFIG_H_
#define GL_CORE_GPU_CONFIG_H_

#include <map>

#include "gl_core/vertex_array.h"
#include "gl_core/vertex_buffer.h"
#include "gl_core/vertex_buffer_layout.h"
#include "gl_core/index_buffer.h"

typedef struct {
    const char* name;
    VertexArray va;
    unsigned int element_count;
} Shape;

class GpuConfig {
    public:
        GpuConfig();
        ~GpuConfig();

        void shove_vertex_data(const char* key, std::vector<Vertex>* data);
        void shove_index_data(const char* key, std::vector<unsigned int>* data);

        void draw(const char* key);

        void bind_vertex_array(const char* key) { m_shapes[key].va.bind(); }
        void unbind_vertex_array(const char* key) { m_shapes[key].va.unbind(); }

    private:
        std::map<const char*, Shape> m_shapes;
        unsigned int m_va_count = 0;
        VertexBuffer* m_vb;
        VertexBufferLayout* m_layout;
        IndexBuffer* m_ib;
        std::map<const char*, int> m_element_count;
};
#endif
