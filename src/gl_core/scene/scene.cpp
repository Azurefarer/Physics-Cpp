#include "scene/scene.h"

Scene::Scene(const std::shared_ptr<Services>& pservices) :
    m_services(pservices)
{
    m_camera = std::make_shared<Camera>(pservices);
    add_rb();
}

void Scene::run() {
    // Update Loop
    for (auto& [id, rb] : m_images ) {
        /*
        PhysicsServer(rb)   -  Does some work on the rb
        GameUpdate(rb)      -  Game Logic
        */
    }
    m_observer->run();
    m_camera->run(m_observer->get_orientation());
}

int Scene::add_rb(const std::shared_ptr<Mesh>& mesh, const std::shared_ptr<Material>& material) {
    m_render_ids++;
    if (mesh && material) {
        std::cout << "hi" << std::endl;
        m_images[m_render_ids] = std::make_shared<RigidBody>(mesh, material);
    } else {
        const std::shared_ptr<Mesh>& dmesh = m_services->get_mesh_cache()->get("default");
        const std::shared_ptr<Material>& dmaterial = m_services->get_material_cache()->get("default");

        m_images[m_render_ids] = std::make_shared<RigidBody>(dmesh, dmaterial);
    }
    return m_render_ids;
}
