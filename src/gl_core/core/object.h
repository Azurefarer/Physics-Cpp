#ifndef CORE_OBJECT_H_
#define CORE_OBJECT_H_

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

class Object {
    public:
        Object();
        ~Object();

    private:
        int m_id;
};

#endif // CORE_OBJECT_H_