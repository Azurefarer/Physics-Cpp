#ifndef GL_AUX_CUBE_H_
#define GL_AUX_CUBE_H_

#include <vector>
#include "gl_aux/vertex.h"

class Cube {
    public:
        Cube();

        std::vector<Vertex> get_verts() const { return m_verts; };
        std::vector<unsigned int> get_indices() const { return m_indices; };
    
    private:
        std::vector<Vertex> m_verts;
        std::vector<unsigned int> m_indices;
};
#endif
