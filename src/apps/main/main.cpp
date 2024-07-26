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

    ShapeMan shape_man;
    shape_man.shove_vertex_index_data("QUAD", &quad_verts, &quad_indices);
    shape_man.shove_vertex_index_data("CUBE", &cube_verts, &cube_indices);

    TextureMan texture_man;
    texture_man.add_texture("king_canute", "../src/king_canute.png");
    texture_man.add_texture("awesome_face", "../src/awesomeface.png");

    shader.use();
    auto tex_int_01 = texture_man.get_texture("king_canute");
    auto tex_int_02 = texture_man.get_texture("awesome_face");
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

        { // Completed:
        // I'm going to want an abstract draw(Shader &shader) function
        // The draw fct is in GpuConfig right now. gpu_config.draw("Shape");
        // this is not very separation of concerns.

        // Put this in a ShapeDict class that knows about all the Shapes it can draw    
        }
        
        { // TODO:
        // Something called like render_pipeline that creates/modifies
        // appropriate model, view and projection maticies.
        }

        { // TODO:
        // This render pipeline is going to need to use the camera obj
        // and know about all objs in the scene
        }

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
        shape_man.draw("CUBE");

        glfwSwapBuffers(window.get_window());
		glfwPollEvents();
    }
    return 0;
}
