#ifndef GL_AUX_QUAD_H_
#define GL_AUX_QUAD_H_

#include <vector>
#include "gl_core/renderer.h"

class Quad {
    public:
        Quad();
        ~Quad();

        std::vector<Vertex> get_verts() const { return m_verts; };
        std::vector<unsigned int> get_indices() const { return m_indices; };
    
    private:
        std::vector<Vertex> m_verts;
        std::vector<unsigned int> m_indices;
};
#endif
