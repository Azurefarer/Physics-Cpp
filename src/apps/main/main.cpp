#include <iostream>
#include "gl_core/gl_core.h"
#include "gl_aux/quad.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

int main() {
    // Set up Open GL Context
    Window window(500, 97, "OpenGL Application");
	GL_call(glPolygonMode(GL_FRONT_AND_BACK, GL_FILL));

    // set up Shader(s)
    Shader shader(
        "../src/shader_source/vertex_shader_practice.vs",
        "../src/shader_source/fragment_shader_01_practice.fs");

    // Set up Vertex Data
    Quad quad;
    
    std::vector<Vertex> quad_verts = quad.get_verts();
    std::vector<unsigned int> quad_indices = quad.get_indices();

    GpuConfig gpu_config;
    gpu_config.shove_vertex_data(&quad_verts);
    gpu_config.shove_index_data(&quad_indices);
    // quad.gpu_config();
    // Configure GPU memory
    // VertexArray va;
    // VertexBuffer vb(&quad_verts);
	// VertexBufferLayout layout;
    // layout.push_float(3);
    // layout.push_float(3);
    // layout.push_float(2);
   	// va.add_buffer(vb, layout);
    // IndexBuffer ib(&quad_indices);
 gpu_config.bind_vertex_array(0);
               std::cout << "hi" << std::endl;

    TextureBuffer tb;
    tb.add_texture("../src/king_canute.png");
    tb.add_texture("../src/awesomeface.png");

    shader.use();
    shader.set_int("texture01", (int)tb.get_texture(0));
    shader.set_int("texture02", (int)tb.get_texture(1));

    // Main Render Loop
    while (!glfwWindowShouldClose(window.get_window())) {
        window.process_input(window.get_window());

        float g = window.get_cursor_pos_ratio()[0];
        float b = window.get_cursor_pos_ratio()[1];

		GL_call(glClearColor(0.0f, g, b, 1.0f));
		GL_call(glClear(GL_COLOR_BUFFER_BIT));

        shader.use();
        float time = glfwGetTime();
		shader.set_float("time", time);

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));

        glm::mat4 view = glm::mat4(1.0f);
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(45.0f), 1500.0f/975.0f, 0.1f, 100.0f);
        
        shader.use();
        shader.set_mat4("model", model);
        shader.set_mat4("view", view);
        shader.set_mat4("projection", projection);
        gpu_config.bind_vertex_array(0);
		GL_call(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (const void*)0));
        gpu_config.unbind_vertex_array(0);

        glfwSwapBuffers(window.get_window());
		glfwPollEvents();
    }
    return 0;
}
