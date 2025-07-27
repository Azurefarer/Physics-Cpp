#ifndef PHYSICS_RIGIDBODY_H_
#define PHYSICS_RIGIDBODY_H_

#define GLM_ENABLE_EXPERIMENTAL

#include <memory>

#include "glm/gtc/matrix_inverse.hpp"
#include "glm/gtx/string_cast.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "asset/shader.h"
#include "asset/material.h"
#include "asset/mesh.h"
#include "core/object.h"

class RigidBody : public Image {
    public:
        RigidBody(const std::shared_ptr<Mesh>& mesh, const std::shared_ptr<Material>& material);
        ~RigidBody() = default;

        bool gui_bool = false;

    private:
        std::shared_ptr<Material> m_material;
        std::shared_ptr<Mesh> m_mesh;
        glm::mat4 m_model = glm::mat4(1.0f);
        glm::mat3 m_normal = glm::mat3(1.0f);
};

#endif // PHYSICS_RIGIDBODY_H_
