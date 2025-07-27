#include "core/object.h"

Image::Image(const std::shared_ptr<Mesh>& mesh, const std::shared_ptr<Material>& material) 
    : m_mesh(mesh),
    m_material(material),
    m_element_count(mesh->get_element_count())
{};

void Image::bind() {
    m_material->use_shader();
    m_mesh->bind();
};
void Image::unbind() {
    m_mesh->unbind();
};

void Image::set_model_position(const glm::vec3& model_offset_from_world) {
    m_model = glm::mat4(1.0f);
    m_model = glm::translate(m_model, model_offset_from_world);
}
