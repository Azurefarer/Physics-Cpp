#ifndef VERTEX_BUFFER_H_
#define VERTEX_BUFFER_H_

#include "gl_core/renderer.h"

class VertexBuffer {
    public:
        VertexBuffer(std::vector<Vertex>* data);
        ~VertexBuffer();

        void bind() const;
        void unbind() const;
    private:
        unsigned int m_renderer_ID = 1;
};
#endif
