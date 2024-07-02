#include "gl_core/triangle.h"

// I'm going to use this triangle as the base for all shapes.
// Using the idea of covariant and contravariant tensors
// The mesh is the invariant object and it's position is variant
// So far the mesh has only one invariant property,
// but I am still making a distinction for modularity in the future
// Here's the mesh:

Triangle::Triangle(std::vector<Vertex> vertex) {
	Triangle::generate_triangle_mesh();
	Triangle::set_mesh_vertex_data(vertex);
}

Triangle::~Triangle() {};

void Triangle::generate_triangle_mesh() {
	m_ID = 1;
}

void Triangle::set_mesh_vertex_data(std::vector<Vertex> vertex) {
	m_vertices = vertex;
}
