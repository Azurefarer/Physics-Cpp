#include "gl_core/rigidbody.h"

int RigidBody::instance_count = 0;

RigidBody::RigidBody(MVP mvp, std::shared_ptr<Shader> shader, std::string shape) {
    m_transforms.model = mvp.model;
    m_transforms.view = mvp.view;
    m_transforms.projection = mvp.projection;
    m_shader = shader;
    m_shaders.push_back(shader);
    m_shape = shape;
    m_name = shape + std::to_string(++instance_count);
};

void RigidBody::run_shader() {
    m_shader->use();
    m_shader->set_mat4("model", m_transforms.model);
    m_shader->set_mat4("view", m_transforms.view);
    m_shader->set_mat4("projection", m_transforms.projection);
    m_shader->set_mat3("normal_matrix", glm::inverseTranspose(glm::mat3(m_transforms.model)));
    m_shader->set_float("time", m_time);
}

void RigidBody::set_model_matrix(glm::vec3 model_offset_from_world, glm::vec3 scale) {
    m_model = glm::mat4(1.0f);
    m_model = glm::translate(m_model, model_offset_from_world);
    m_model = glm::scale(m_model, scale);
    m_transforms.model = m_model;
}

void RigidBody::update_view_and_perspective(glm::mat4 view, glm::mat4 projection) {
    m_transforms.view = view;
    m_transforms.projection = projection;
}

// TODO: look at Godot's implementation
