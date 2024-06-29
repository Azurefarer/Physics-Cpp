#pragma once
#include <array>

class Triangle {
    private:
        unsigned int m_ID = 0;
        std::array<float, 9> m_position;

    public:
        Triangle(std::array<float, 9> position);
        ~Triangle();

        void generate_triangle_mesh();
        void set_mesh_vertex_data(std::array<float, 9> position);

        std::array<float, 9> get_mesh_vertex_data() { return m_position; }
};
