#include <iostream>
#include "gl_core/renderer.h"
#include "gl_core/window.h"
#include "gl_core/shader.h"
#include "gl_core/triangle.h"
#include "gl_core/vertex_array.h"
#include "gl_core/vertex_buffer.h"
#include "gl_core/vertex_buffer_layout.h"
#include "gl_core/index_buffer.h"

int main() {
    // Set up Open GL Context
    Window window(1000, 650, "OpenGL Application");
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    // set up Shader(s)
    Shader shader(
        "../src/shader_source/vertex_shader_practice.vs",
        "../src/shader_source/fragment_shader_01_practice.fs");

    // Set up Vertex Data
    std::vector<Vertex> vertices = {
        {-0.5, -0.5, 0.0},
        {0.5, -0.5, 0.0},
        {0.5, 0.5, 0.0}
    };
    std::vector<unsigned int> indices = {
        0, 1, 2
    };
    Triangle triangle(vertices);
    std::vector<Vertex> position = triangle.get_mesh_vertex_data();

    // Configure GPU memory
    VertexArray va;
    VertexBuffer vb(&position);
	VertexBufferLayout layout;
    layout.push_float(3);
   	va.add_buffer(vb, layout);
    IndexBuffer ib(&indices);

    // Main Render Loop
    while (!glfwWindowShouldClose(window.get_window())) {
        window.process_input(window.get_window());

		glClearColor(0.0f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

        shader.use();
        float time = glfwGetTime();
		shader.setFloat("time", time);

        va.bind();
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (const void*)0);
        va.unbind();

        glfwSwapBuffers(window.get_window());
		glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}
