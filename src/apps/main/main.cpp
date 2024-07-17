#include <iostream>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "gl_core/gl_core.h"
#include "gl_aux/gl_aux.h"

int main() {
    // Set up Open GL Context
    Window window(1500, 975, "OpenGL Application");
	GL_call(glPolygonMode(GL_FRONT_AND_BACK, GL_FILL));

    // set up Shader(s)
    Shader shader(
        "../src/shader_source/vertex_shader_practice.vs",
        "../src/shader_source/fragment_shader_01_practice.fs");

    // Set up Vertex Data
    Quad quad;
    std::vector<Vertex> quad_verts = quad.get_verts();
    std::vector<unsigned int> quad_indices = quad.get_indices();

    Cube cube;
    std::vector<Vertex> cube_verts = cube.get_verts();
    std::vector<unsigned int> cube_indices = cube.get_indices();

    GpuConfig gpu_config;
    gpu_config.shove_vertex_data(&quad_verts);
    gpu_config.shove_index_data(&quad_indices);
    gpu_config.shove_vertex_data(&cube_verts);
    gpu_config.shove_index_data(&cube_indices);

    TextureBuffer tb;
    tb.add_texture("../src/king_canute.png");
    tb.add_texture("../src/awesomeface.png");

    shader.use();
    auto tex_int_01 = tb.get_texture(0);
    auto tex_int_02 = tb.get_texture(1);
    if (!tex_int_01.has_value() || !tex_int_02.has_value()) {
        throw std::runtime_error("invalid tex");
    }
    shader.set_int("texture01", tex_int_01.value());
    shader.set_int("texture02", tex_int_02.value());

    // Camera obj
    Camera cam;

    // Main Render Loop
    while (!glfwWindowShouldClose(window.get_window())) {
        window.process_input(window.get_window());

        // I'm going to want an abstract draw(Shader &shader) function
        // gpu_config.draw(1); the draw fct is in GpuConfig right now.
        // this is not very separation of concerns.
        
        // Something called like render_pipeline that creates/modifies
        // appropriate model, view and projection maticies.

        // This render pipeline is going to need to use the camera obj
        // and know about all objs in the scene

        float g = window.get_cursor_pos_ratio()[0];
        float b = window.get_cursor_pos_ratio()[1];

		GL_call(glClearColor(0.0f, g, b, 1.0f));
		GL_call(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
        
        glm::mat4 model(1.0f);
        glm::mat4 view(1.0f);
        glm::mat4 projection(1.0f);
        model = glm::rotate(model, glm::radians(b*360.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::rotate(model, glm::radians(g*360.0f), glm::vec3(0.0f, -1.0f, 0.0f));
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -5.0f));
        projection = glm::perspective(glm::radians(45.0f), 1500.0f/975.0f, 0.1f, 100.0f);
        shader.use();
        shader.set_mat4("model", model);
        shader.set_mat4("view", cam.get_view());
        shader.set_mat4("projection", projection);
        gpu_config.draw(1);

        glfwSwapBuffers(window.get_window());
		glfwPollEvents();
    }
    return 0;
}
