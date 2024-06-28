#pragma once
#include "gl_core/vertex_buffer.h"
#include "gl_core/vertex_buffer_layout.h"

class VertexArray {
    private:
    public:
        unsigned int m_renderer_ID;
        VertexArray();
        ~VertexArray();

        void add_buffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
        void bind();
        void unbind();
        void add_layout();
};
