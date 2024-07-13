#pragma once

#include "gl_core/vertex_array.h"
#include "gl_core/vertex_buffer.h"
#include "gl_core/vertex_buffer_layout.h"
#include "gl_core/index_buffer.h"

class GpuConfig {
    public:
        GpuConfig();
        ~GpuConfig();

        void shove_vertex_data(std::vector<Vertex>* data);
        void shove_index_data(std::vector<unsigned int>* data);

        void bind_vertex_array(int index) { m_va[index].bind(); }
        void unbind_vertex_array(int index) { m_va[index].unbind(); }

    private:
        std::vector<VertexArray> m_va;
};
