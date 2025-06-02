#include "gl_core/rigidbody.h"

int RigidBody::instance_count = 0;

RigidBody::RigidBody(MVP mvp) {
    m_transforms.model = mvp.model;
    m_transforms.view = mvp.view;
    m_transforms.projection = mvp.projection;
    m_shaders.push_back("default");
    m_shape = "cube";
    m_name = "cube" + std::to_string(++instance_count);
};

void RigidBody::set_shaders(const std::vector<std::string>& shaders) {
    m_shaders.clear();
    m_shaders = shaders;
}


void RigidBody::set_transforms(const std::shared_ptr<Shader>& shader) {
    shader->set_mat4("model", m_transforms.model);
    shader->set_mat4("view", m_transforms.view);
    shader->set_mat4("projection", m_transforms.projection);
    shader->set_mat3("normal_matrix", glm::inverseTranspose(glm::mat3(m_transforms.model)));
    shader->set_float("time", m_time);
}

void RigidBody::draw() {
    for (auto& shader_name : m_shaders) {
        auto shader = ShaderCache::get_instance().m_shader_programs[shader_name];
        shader->use();
        set_transforms(shader);
        std::cout << shader->get_name() << std::endl;
        ShapeCache::get_instance().draw(m_shape);
    }
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

// auto* RigidBody::get_uni_value(std::string uniform) {
//     if ()
// }


// TODO: look at Godot's implementation
