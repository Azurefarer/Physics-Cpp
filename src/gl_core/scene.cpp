#include "gl_core/scene.h"

Scene::Scene(const std::shared_ptr<Services>& pservices) :
    m_services(pservices)
{
    m_camera = std::make_unique<Camera>();
}

void Scene::get_rigidbodies() {

}

void Scene::run() {

}

void Scene::add_rigidbody() {
    m_assets.push_back(std::make_shared<RigidBody>(m_transforms));
}