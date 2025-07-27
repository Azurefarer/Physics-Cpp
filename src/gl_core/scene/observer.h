#ifndef SCENE_OBSERVER_H_
#define SCENE_OBSERVER_H_

#define GLM_ENABLE_EXPERIMENTAL

#include <iostream>
#include <memory>

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/string_cast.hpp"

#include "core/input.h"

class Observer {
    public:
        Observer(const std::shared_ptr<Services>& pservices);

        void run();
        void update_orientation(const glm::quat& orientation);

        void process_keyboard(int key, float delta_t);
        void process_mouse_movement(double x_offset, double y_offset, GLboolean constrain_pitch = true);
        void process_mouse_scroll(double y_offset);

        const glm::quat& get_orientation() const { return m_orientation; }
        void set_orientation(const glm::quat& orientation) { m_orientation = orientation; }
        const glm::vec3& get_pos() const { return m_pos; }
        void set_pos(const glm::vec3& pos) { m_pos = pos; }

    private:
        std::shared_ptr<Services> m_services;
        glm::quat m_orientation;  // Quaternion to represent rotation
        glm::vec3 m_pos;
        glm::vec3 m_front;
        glm::vec3 m_up;
        glm::vec3 m_world_up;
        glm::vec3 m_right;
        float m_movement_speed = 10.0;

};

#endif // SCENE_OBSERVER_H_