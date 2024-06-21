#pragma once
#include <iostream>
#include <array>

enum Triangle {
    Equilateral,
    Isoceles_Right,
    Isoceles_Obtuse,
    Isoceles_Acute,
    Scalene_Right,
    Scalene_Obtuse,
    Scalene_Acute
};
// class Triangle {
//     public:
//     Triangle();
//     enum Type {
//         Equilateral,
//         Isoceles_Right,
//         Isoceles_Obtuse,
//         Isoceles_Acute,
//         Scalene_Right,
//         Scalene_Obtuse,
//         Scalene_Acute
//     };
// };

std::array<float, 9> create_triangle_mesh(Triangle type);

std::array<float, 9> create_mesh_vertices(Triangle type);

std::array<float, 9> equilateral();

std::array<float, 9> isoceles_right();

std::array<float, 9> isoceles_obtuse();

std::array<float, 9> isoceles_acute();

std::array<float, 9> scalene_right();

std::array<float, 9> scalene_obtuse();

std::array<float, 9> scalene_acute();
