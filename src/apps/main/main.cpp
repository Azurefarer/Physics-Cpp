#include <iostream>
#include "gl_core/gl_core.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

int main() {
    // Set up Open GL Context
    Window window(1500, 975, "OpenGL Application");
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

        glm::mat4 trans = glm::mat4(1.0f);
        trans = glm::translate(trans, glm::vec3(-0.5f, -0.5f, 0.0f));
        trans = glm::rotate(trans, time, glm::vec3(0.0f, 0.0f, 1.0f));
        trans = glm::scale(trans, glm::vec3(0.5f, 0.5f, 0.5f));
        shader.use();
        shader.set_mat4("rot", trans);
        va.bind();
		GL_call(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (const void*)0));
        va.unbind();

        trans = glm::mat4(1.0f);
        trans = glm::translate(trans, glm::vec3(0.5, 0.5, 0.0));
        trans = glm::rotate(trans, time, glm::vec3(0.0, 0.0, 1.0));
        trans = glm::scale(trans, glm::vec3(0.5f, 0.5f, 0.5f));
        shader.use();
        shader.set_mat4("rot", trans);

        va.bind();
		GL_call(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (const void*)0));
        va.unbind();

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

        va.bind();
		GL_call(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (const void*)0));
        va.unbind();

        glfwSwapBuffers(window.get_window());
		glfwPollEvents();
    }
    return 0;
}
