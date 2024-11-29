#include "gl_core/rigidbody.h"

RigidBody::RigidBody(MVP mvp, std::shared_ptr<Shader> shader, std::string shape) {
    m_transforms.model = mvp.model;
    m_transforms.view = mvp.view;
    m_transforms.projection = mvp.projection;
    m_shader = shader;
    m_shape = shape;
};

void RigidBody::run_shader() {
    m_shader->use();
    m_shader->set_mat4("model", m_transforms.model);
    m_shader->set_mat4("view", m_transforms.view);
    m_shader->set_mat4("projection", m_transforms.projection);
    m_shader->set_mat3("normal_matrix", glm::mat3(glm::transpose(glm::inverse(m_transforms.model))));
    m_shader->set_float("time", m_time);
}

void RigidBody::set_model_matrix(glm::vec3 model_offset_from_world, glm::vec3 scale) {
    m_model = glm::translate(m_model, model_offset_from_world);
    m_model = glm::scale(m_model, scale);
    m_transforms.model = m_model;
}

void RigidBody::update_view_and_perspective(glm::mat4 view, glm::mat4 projection) {
    m_transforms.view = view;
    m_transforms.projection = projection;
}

// TODO: look at Godot's implementation
