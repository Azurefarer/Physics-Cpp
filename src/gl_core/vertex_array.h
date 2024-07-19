#ifndef GL_CORE_VERTEX_ARRAY_H_
#define GL_CORE_VERTEX_ARRAY_H_

#include <stdint.h>

#include "gl_core/renderer.h"
#include "gl_core/vertex_buffer.h"
#include "gl_core/vertex_buffer_layout.h"

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
#endif
