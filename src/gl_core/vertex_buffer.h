#pragma once
#include "gl_core/renderer.h"

class VertexBuffer {
    private:
        unsigned int m_renderer_ID = 1;
    public:
        VertexBuffer(std::vector<Vertex>* data);
        ~VertexBuffer();

        void bind() const;
        void unbind() const;
};
