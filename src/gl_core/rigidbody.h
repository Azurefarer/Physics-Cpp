#ifndef GL_CORE_RIGIDBODY_H_
#define GL_CORE_RIGIDBODY_H_

#include <memory>

#include "gl_aux/vertex.h"
#include "gl_core/shader.h"

class RigidBody {
    public:
        RigidBody(MVP mvp);
        ~RigidBody() = default;

        void run_shader();
        std::string get_shape() { return m_shape; }

    private:
        MVP m_transforms;
        std::shared_ptr<Shader> m_shader = nullptr;

        float m_time;

        std::string m_shape = "QUAD";

};

#endif
