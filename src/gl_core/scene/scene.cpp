#include "scene/scene.h"

Scene::Scene(const std::shared_ptr<Services>& pservices) :
    m_services(pservices)
{
    m_camera = std::make_unique<Camera>();
    add_rb();
}

void Scene::run() {
    m_camera->run();
    // Update Loop
    for (auto& [id, rb] : m_images ) {
        /*
            PhysicsServer(rb)   -  Does some work on the rb
            GameUpdate(rb)      -  Game Logic
        */
    }
}

int Scene::add_rb(const std::shared_ptr<Mesh>& mesh, const std::shared_ptr<Material>& material) {
    m_render_ids++;
    if (mesh && material) {
        m_images[m_render_ids] = std::make_shared<RigidBody>(mesh, material);
    } else {
        const std::shared_ptr<Mesh>& dmesh = m_services->get_mesh_cache()->get("default");
        const std::shared_ptr<Material>& dmaterial = m_services->get_material_cache()->get("default");

        m_images[m_render_ids] = std::make_shared<RigidBody>(dmesh, dmaterial);
    }
    return m_render_ids;
}
