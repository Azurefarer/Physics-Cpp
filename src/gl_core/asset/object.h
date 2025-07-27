#ifndef ASSET_OBJECT_H_
#define ASSET_OBJECT_H_

#define GLM_ENABLE_EXPERIMENTAL

#include <memory>

#include "glm/gtc/matrix_inverse.hpp"
#include "glm/gtx/string_cast.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "asset/shader.h"
#include "asset/material.h"
#include "asset/mesh.h"

/*
    An Image is something that may or may not show up on your screen.
    Images can get culled if their mesh is not within view of the camera or is to close or too far from it.
    There are other culling algs like with the Z-buffer or smthing
*/
class Image {
    public:
        Image(const std::shared_ptr<Mesh>& mesh, const std::shared_ptr<Material>& material);

        const std::shared_ptr<Material>& get_material() const { return m_material; }
        void set_material(const std::shared_ptr<Material>& material) { m_material = material; }

        const std::shared_ptr<Mesh>& get_mesh() const { return m_mesh; }
        void set_mesh(const std::shared_ptr<Mesh>& mesh) { m_mesh = mesh; }

        const glm::mat4& get_model() const { return m_model; }
        void set_model_position(const glm::vec3& model_offset_from_world);

        const unsigned int& get_element_count() const { return m_element_count; }
        void bind();
        void unbind();
        
    protected:
        std::shared_ptr<Material> m_material;
        std::shared_ptr<Mesh> m_mesh;
        glm::mat4 m_model = glm::mat4(1.0f);
        unsigned int m_element_count;
};

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

class Object {
    public:
        Object();
        ~Object();

    private:
        int m_id;
};

#endif // ASSET_OBJECT_H_