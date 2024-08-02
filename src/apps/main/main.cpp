#include <iostream>

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "gl_core/gl_core.h"
#include "gl_aux/gl_aux.h"

int main() {
    RenderPipelineContext context(1500, 975, "OpenGL Application");
	GL_call(glPolygonMode(GL_FRONT_AND_BACK, GL_FILL));

    Shader shader(
        "../src/shader_source/vertex_shader_practice.vs",
        "../src/shader_source/fragment_shader_01_practice.fs");

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

    while (!glfwWindowShouldClose(context.get_window())) {
        context.run();
        { // TODO:
        // Something called like render_pipeline that creates/modifies
        // appropriate model, view and projection maticies.
        }

        { // TODO:
        // This render pipeline is going to need to use the camera obj
        // and know about all objs in the scene
        }
        
        shader.use();
        shader.set_mat4("model", context.get_transform("MODEL"));
        shader.set_mat4("view", context.get_transform("VIEW"));
        shader.set_mat4("projection", context.get_transform("PROJECTION"));
        shape_man.draw("CUBE");

        glfwSwapBuffers(context.get_window());
		glfwPollEvents();
    }
    return 0;
}
