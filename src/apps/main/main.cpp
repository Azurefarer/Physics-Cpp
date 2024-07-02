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
    Window window(900, 500, "OpenGL Application");
    // glfwSetFramebufferSizeCallback(window.get_window(), viewport_size_callback);
	// if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
	// 	std::cout << "Failed to initialize GLAD" << std::endl;
	// 	return -1;
	// }
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    // set up Shader(s)
    Shader shader(
        "./src/shader_source/vertex_shader_practice.vs",
        "./src/shader_source/fragment_shader_01_practice.fs");

    // Set up Vertex Data
    std::vector<Vertex> vertices = {
        {-0.5, -0.5, 0.0},
        {0.5, -0.5, 0.0},
        {0.5, 0.5, 0.0}
    };

    std::vector<float> positions = {
        -0.5, -0.5, 0.0,
        0.5, -0.5, 0.0,
        0.5, 0.5, 0.0
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
    IndexBuffer ib(&indices, 3);

    // Main Render Loop
    while (!glfwWindowShouldClose(window.get_window())) {
        window.process_input(window.get_window());

		glClearColor(0.0f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

        // shader.use();

        va.bind();
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
        va.unbind();
        std::cout << "while" << std::endl;
        glfwSwapBuffers(window.get_window());
		glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}
