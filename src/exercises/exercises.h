#pragma once
#include <array>
#include "glad/glad.h"
#include "GLFW/glfw3.h"

int exercises();

void gen_gl_objs(unsigned int *VAO, unsigned int *VBO);

// How would I write this differently?
template <std::size_t N>
void bind_gl_objs(unsigned int *VAO, unsigned int *VBO, std::array<float, N> vertices) {
	glBindVertexArray(VAO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);
}

void vert_attrib_pointer_config(bool color, bool UV);

template <std::size_t N>
void write_to_element_buffer(unsigned int *EBO, std::array<unsigned int, N> indices) {
	glGenBuffers(1, EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[0]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices, GL_STATIC_DRAW);
}

void set_texture_params();

float* sphere(float radius);
