#ifndef GL_CORE_RIGIDBODY_H_
#define GL_CORE_RIGIDBODY_H_

#include <memory>

#include "glm/gtc/matrix_transform.hpp"

#include "gl_aux/vertex.h"
#include "gl_core/shader.h"

class RigidBody {
    public:
        RigidBody(MVP mvp, std::shared_ptr<Shader> shader, std::string shape);
        ~RigidBody() { --instance_count; };

        void run_shader();

        void set_model_matrix(glm::vec3 model_offset_from_world, glm::vec3 scale = glm::vec3(1.0f));
        void set_shape(std::string shape) { m_shape = shape; } //

        void update_view_and_perspective(glm::mat4 view, glm::mat4 projection);

        void set_time(float time) { m_time = time; }
        int get_instance_count() const { return instance_count; }

        std::string get_name() { return m_name; }
        std::string get_shape() { return m_shape; }

        bool gui_bool = false;

    private:
        static int instance_count;
        
        std::string m_name;
        MVP m_transforms;
        std::shared_ptr<Shader> m_shader = nullptr;

        glm::mat4 m_model = glm::mat4(1.0f);
        glm::mat3 m_normal = glm::mat3(1.0f);
        float m_time;

        std::string m_shape = "QUAD";

};

#endif
