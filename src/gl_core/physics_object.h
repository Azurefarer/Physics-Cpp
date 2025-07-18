#ifndef GL_CORE_PHYSICS_OBJECT_H_
#define GL_CORE_PHYSICS_OBJECT_H_

#include <memory>

#include "glm/glm.hpp"

struct State {
    glm::vec4 m_potential;
    glm::vec4 m_position;
};

class PhysicsObject {
    public:
        PhysicsObject() = default;
        ~PhysicsObject() = default;


    private:
        State m_state;
        State m_dstate_dt;
};

#endif
