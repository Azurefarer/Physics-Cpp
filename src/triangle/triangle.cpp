#include <math.h>
#include <iostream>
#include <array>
#include "triangle/triangle.h"

// enum Triangle {
//     Equilateral,
//     Isoceles_Right,
//     Isoceles_Obtuse,
//     Isoceles_Acute,
//     Scalene_Right,
//     Scalene_Obtuse,
//     Scalene_Acute
// };

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

// I'm going to use this triangle as the base for all shapes.
// Using the idea of covariant and contravariant tensors
// The mesh is the invariant object and it's vertices are variant
// So far the mesh has only one invariant property,
// but I am still making a distinction for modularity in the future
// Here's the mesh:
std::array<float, 9> create_triangle_mesh(Triangle type) {
	std::array<float, 9> vertices;
	vertices = create_mesh_vertices(type);
	return vertices;
}

// based on input this fct will decide where to put a certain mesh
std::array<float, 9> create_mesh_vertices(Triangle type) {
	std::array<float, 9> vertices;
	switch (type) {
		case Triangle::Equilateral:
			vertices = equilateral();
			std::cout << "Equilateral";
			break;
		case Triangle::Isoceles_Right:
			vertices = isoceles_right();
			std::cout << "Isoceles_Right";
			break;
		case Triangle::Isoceles_Obtuse:
			vertices = isoceles_obtuse();
			std::cout << "Isoceles_Obtuse";
			break;
		case Triangle::Isoceles_Acute:
			vertices = isoceles_acute();
			std::cout << "Isoceles_Acute";
			break;
		case Triangle::Scalene_Right:
			vertices = scalene_right();
			std::cout << "Scalene_Right";
			break;
		case Triangle::Scalene_Obtuse:
			vertices = scalene_obtuse();
			std::cout << "Scalene_Obtuse";
			break;
		case Triangle::Scalene_Acute:
			vertices = scalene_acute();
			std::cout << "Scalene_Acute";
			break;
	}
	return vertices;
}

std::array<float, 9> equilateral() {
	std::array<float, 9> vertices;
	vertices[0] = 0.0, 0.0, 0.0;
	vertices[1] = 1.0, 0.0, 0.0;
	vertices[2] = 0.866, 1.0, 0.0;
	return vertices;
}

std::array<float, 9> isoceles_right() {
	std::array<float, 9> vertices;
	return vertices;
}

std::array<float, 9> isoceles_obtuse() {
	std::array<float, 9> vertices;
	return vertices;
}

std::array<float, 9> isoceles_acute() {
	std::array<float, 9> vertices;
	return vertices;
}

std::array<float, 9> scalene_right() {
	std::array<float, 9> vertices;
	return vertices;
}

std::array<float, 9> scalene_obtuse() {
	std::array<float, 9> vertices;
	return vertices;
}

std::array<float, 9> scalene_acute() {
	std::array<float, 9> vertices;
	return vertices;
}
