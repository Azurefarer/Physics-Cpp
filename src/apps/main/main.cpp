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
    std::cout << "inside main fct" << std::endl;
    VertexBuffer vb(&position, sizeof(&position));
	VertexBufferLayout layout;
    layout.push_float(3);
   	va.add_buffer(vb, layout);

    IndexBuffer ib(&indices, 3);

    while (!glfwWindowShouldClose(window.get_window())) {
        window.process_input(window.get_window());

		(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

        std::cout << "in while loop" << std::endl;
        shader.use();

        va.bind();
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
        va.unbind();

        glfwSwapBuffers(window.get_window());
		glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}
