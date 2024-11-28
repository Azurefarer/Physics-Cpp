#include "gl_core/rigidbody.h"

RigidBody::RigidBody(MVP mvp) {
    m_transforms.model = mvp.model;
    m_transforms.view = mvp.view;
    m_transforms.projection = mvp.projection;

    m_shader = std::make_shared<Shader>(
        "../src/shader_source/phong_lighting_model.vs",
        "../src/shader_source/phong_lighting_model.fs");

};

void RigidBody::run_shader() {
    m_shader->use();
    m_shader->set_mat4("model", m_transforms.model);
    m_shader->set_mat4("view", m_transforms.view);
    m_shader->set_mat4("projection", m_transforms.projection);
    m_shader->set_mat3("normal_matrix", glm::mat3(glm::transpose(glm::inverse(m_transforms.model))));
}

// TODO: look at Godot's implementation
