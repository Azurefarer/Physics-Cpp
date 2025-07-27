#ifndef SCENE_OBSERVER_H_
#define SCENE_OBSERVER_H_

#include <iostream>
#include <memory>

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/string_cast.hpp"

#include "core/input.h"

class Observer {
    public:
        Observer();

        const glm::vec3& get_pos() const { return m_pos; }
        void set_pos(const glm::vec3& pos) { m_pos = pos; }

        void process_keyboard(int key, float delta_t);

    private:
        glm::vec3 m_pos;
        glm::quat m_orientation;  // Quaternion to represent rotation
};

#endif // SCENE_OBSERVER_H_