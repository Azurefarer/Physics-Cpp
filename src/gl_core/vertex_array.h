#pragma once
#include <stdint.h>
#include "gl_core/vertex_buffer.h"
#include "gl_core/vertex_buffer_layout.h"

class VertexArray {
    public:
        VertexArray();
        ~VertexArray();

        void add_buffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
        void bind();
        void unbind();
        void add_layout();

    private:
        unsigned int m_renderer_ID = 1;
};
