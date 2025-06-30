#ifndef GL_CORE_CAMERA_H_
#define GL_CORE_CAMERA_H_

#define GLM_ENABLE_EXPERIMENTAL

#include <iostream>
#include <memory>

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/string_cast.hpp"

#include "gl_core/context.h"

class Camera {
    public:
        Camera(const std::shared_ptr<Context>& pcontext);
        void point_at(glm::vec3 front);
        void run();

        void set_control(bool activity);

        void process_keyboard(int key, float delta_time);
        void process_mouse_movement(double x_offset, double y_offset, GLboolean constrain_pitch = true);
        void process_mouse_scroll(double y_offset);

        float get_pos() const { return m_pos.x; }
        float get_zoom() const { return m_zoom; }

        glm::mat4 get_view() const { return m_view; }
    
    private:
        std::shared_ptr<Context> m_context;
        bool m_active = true;
        
        double m_yaw;
        double m_pitch; // for (m_yaw, m_pitch) = (0, 0) m_front, m_right, and m_up are the xyz basis vectors.
        double m_movement_speed = 10.0;
        double m_mouse_sensitivity = 100;
        double m_zoom = 45.0;

        glm::mat4 m_view;
        void set_view();

        glm::vec3 m_pos;
        glm::vec3 m_front;
        glm::vec3 m_up;
        glm::vec3 m_world_up;
        glm::vec3 m_right;

        void update_camera_vectors();
};

#endif