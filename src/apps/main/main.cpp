#include <iostream>
#include <array>
#include "gl_core/renderer.h"
#include "gl_core/window.h"
#include "gl_core/shader.h"
#include "gl_core/triangle.h"
#include "gl_core/vertex_array.h"
#include "gl_core/vertex_buffer.h"
#include "gl_core/vertex_buffer_layout.h"
#include "gl_core/index_buffer.h"

int main() {
    Window window(900, 500, "OpenGL Application");
    glfwSetFramebufferSizeCallback(window.get_window(), viewport_size_callback);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    Shader shader(
        "./src/shader_source/vertex_shader_practice.vs",
        "./src/shader_source/fragment_shader_01_practice.fs");
    std::array<float, 9> positions = {
        -0.5, -0.5, 0.0,
        0.5, -0.5, 0.0,
        0.5, 0.5, 0.0
    };
    std::array<unsigned int, 3> indices = {
        0, 1, 2
    };
    Triangle triangle(positions);

    std::array<float, 9> position = triangle.get_mesh_vertex_data();

    VertexArray va;
    VertexBuffer vb(&position, sizeof(&position));
	VertexBufferLayout layout;
    layout.push_float(3);
   	va.add_buffer(vb, layout);

    IndexBuffer ib(&indices, 3);

    while (!glfwWindowShouldClose(window.get_window())) {
        window.process_input(window.get_window());

		glClearColor(0.0f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

        shader.use();

        va.bind();
		GL_call(glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0));
        // va.unbind();

        glfwSwapBuffers(window.get_window());
        // std::cout << "in while loop : " << std::endl;
		glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}
