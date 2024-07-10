#include <iostream>
#include "gl_core/renderer.h"
#include "gl_core/window.h"
#include "gl_core/shader.h"
#include "gl_core/triangle.h"
#include "gl_core/vertex_array.h"
#include "gl_core/vertex_buffer.h"
#include "gl_core/vertex_buffer_layout.h"
#include "gl_core/index_buffer.h"
#include "gl_core/texture_buffer.h"

int main() {
    // Set up Open GL Context
    Window window(1000, 650, "OpenGL Application");
	GL_call(glPolygonMode(GL_FRONT_AND_BACK, GL_FILL));

    // set up Shader(s)
    Shader shader(
        "../src/shader_source/vertex_shader_practice.vs",
        "../src/shader_source/fragment_shader_01_practice.fs");

    // Set up Vertex Data
    std::vector<Vertex> vertices = {
        {-0.5, -0.5, 0.0,  0.2, 0.7, 0.5,  1.0, 1.0},
        {0.5, -0.5, 0.0,  0.4, 0.9, 0.3,  0.0, 1.0},
        {0.5, 0.5, 0.0,  0.3, 0.7, 0.1,  0.0, 0.0},
        {-0.5, 0.5, 0.0,  0.9, 0.7, 0.1,  1.0, 0.0}
    };
    std::vector<unsigned int> indices = {
        0, 1, 2,
        0, 2, 3
    };
    Triangle triangle(vertices);
    std::vector<Vertex> position = triangle.get_mesh_vertex_data();

    // Configure GPU memory
    VertexArray va;
    VertexBuffer vb(&position);
	VertexBufferLayout layout;
    layout.push_float(3);
    layout.push_float(3);
    layout.push_float(2);
   	va.add_buffer(vb, layout);
    IndexBuffer ib(&indices);

    TextureBuffer tb;
    tb.add_texture("../src/king_canute.png");
    tb.add_texture("../src/awesomeface.png");
    // tb.add_texture("../src/awesomeface.png");

    shader.use();
    shader.setInt("texture01", (int)tb.get_texture(0));
    shader.setInt("texture02", (int)tb.get_texture(1));

    // Main Render Loop
    while (!glfwWindowShouldClose(window.get_window())) {
        window.process_input(window.get_window());

		GL_call(glClearColor(0.0f, 0.2f, 0.2f, 1.0f));
		GL_call(glClear(GL_COLOR_BUFFER_BIT));

        shader.use();
        float time = glfwGetTime();
		shader.setFloat("time", time);

        va.bind();
		GL_call(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (const void*)0));
        va.unbind();

        glfwSwapBuffers(window.get_window());
		glfwPollEvents();
    }
    return 0;
}
