#include "gl_core/scene.h"

void Scene::add_rigidbody() {
    m_assets.push_back(std::make_shared<RigidBody>(m_transforms));
}