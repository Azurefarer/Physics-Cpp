#include "scene/camera.h"

Camera::Camera(const std::shared_ptr<Services>& pservices) : 
    m_services(pservices),
    m_pos(glm::vec3(0.0f, 2.0f, 15.0f)),
    m_world_up(glm::vec3(0.0f, 1.0f, 0.0f))
{
    
    update_orientation(glm::quat(0.0, 0.0, 0.0, 0.0));
    set_view_projection_transforms();
}

void Camera::run(const glm::quat& orientation) {
    process_mouse_scroll(m_services->get_scroll_offset_y());
    update_orientation(orientation);
    set_view_projection_transforms();
}

void Camera::set_view_projection_transforms() {
    glm::vec3 target = m_pos + m_front;
    m_services->set_view(glm::lookAt(m_pos, target, m_up));
    m_services->set_projection(glm::perspective(glm::radians(m_zoom), m_services->get_aspect_ratio(), 1.0, 100.0));
}

void Camera::update_orientation(const glm::quat& orientation) {
    m_front = orientation * m_front;
    m_right = glm::normalize(glm::cross(m_front, m_world_up));
    m_up = glm::normalize(glm::cross(m_right, m_front));
}

void Camera::process_mouse_scroll(double y_offset) {
    m_zoom -= y_offset;
}

// void Camera::set_control(bool activity) {
//     m_active = activity;
// }
