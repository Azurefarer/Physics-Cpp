#include "servers/renderer.h"

Renderer::Renderer(const std::shared_ptr<Services>& pservices) : m_services(pservices) {}

void Renderer::run() {

}

void Renderer::render(const Scene& scene) {
    const auto& images = scene.get_images();
    const auto& mat_cache_temp = m_services->get_material_cache();
    for (const auto& [name, material] : mat_cache_temp->get_map()) {
        material->use_shader();
        material->set_float("time", m_services->get_time());
        material->set_mat4("view", m_services->get_view());
        material->set_mat4("projection", m_services->get_projection());
    }
    for (const auto& [id, image] : images) {
        image->bind();
        image->get_material()->set_mat4("model", image->get_model());
        image->get_material()->set_mat3("normal_matrix", glm::inverseTranspose(glm::mat3(image->get_model())));
        glDrawElements(GL_TRIANGLES, image->get_element_count(), GL_UNSIGNED_INT, 0);
        image->unbind();
    } 
}
