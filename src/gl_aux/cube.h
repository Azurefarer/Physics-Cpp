#pragma once

#include <vector>
#include "gl_core/renderer.h"

class Cube {
    public:
        Cube();
        ~Cube();

        std::vector<Vertex> get_verts() const { return m_verts; };
        std::vector<unsigned int> get_indices() const { return m_indices; };
    
    private:
        std::vector<Vertex> m_verts;
        std::vector<unsigned int> m_indices;
};
