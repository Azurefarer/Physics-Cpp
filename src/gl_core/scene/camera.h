#ifndef SCENE_CAMERA_H_
#define SCENE_CAMERA_H_

#define GLM_ENABLE_EXPERIMENTAL

#include <iostream>
#include <memory>

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/string_cast.hpp"

#include "core/services.h"

enum CameraMovement {
    FORWARD = GLFW_KEY_W,
    LEFT = GLFW_KEY_A,
    BACKWARD = GLFW_KEY_S,
    RIGHT = GLFW_KEY_D
};

class Camera {
    public:
        Camera(const std::shared_ptr<Services>& pservices);
        void run(const glm::quat& orientation);

        void update_orientation(const glm::quat& orientation);
        
        float get_pos() const { return m_pos.x; }
        float get_zoom() const { return m_zoom; }
        
        glm::mat4 get_view() const { return m_view; }
        glm::mat4 get_projection() const { return m_projection; }
        
    private:
        std::shared_ptr<Services> m_services;
        double m_zoom = 45.0;
        glm::mat4 m_view;
        glm::mat4 m_projection;
        glm::vec3 m_pos;
        glm::vec3 m_front;
        glm::vec3 m_up;
        glm::vec3 m_world_up;
        glm::vec3 m_right;
        
        void process_mouse_scroll(double y_offset);
        void set_view_projection_transforms();
};

#endif