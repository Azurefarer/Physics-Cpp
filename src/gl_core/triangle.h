#pragma once
#include "gl_core/renderer.h"

class Triangle {
    public:
        Triangle(std::vector<Vertex> vertex);
        ~Triangle();

        void generate_triangle_mesh();
        void set_mesh_vertex_data(std::vector<Vertex> vertex);

        std::vector<Vertex> get_mesh_vertex_data() { return m_vertices; }
    
    private:
        unsigned int m_ID = 0;
        std::vector<Vertex> m_vertices;
};
