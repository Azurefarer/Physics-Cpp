#include "scene/camera.h"

Camera::Camera(const std::shared_ptr<Services>& pservices) : 
    m_services(pservices),
    m_pos(glm::vec3(0.0f, 2.0f, 15.0f)),
    m_world_up(glm::vec3(0.0f, 1.0f, 0.0f))
{
    m_yaw = 0;
    m_pitch = 0.0;
    update_camera_vectors();
    set_view_projection_transforms();
}

void Camera::run() {
    int *iter = &(m_context->get_keys_pressed()->W_key); // Memory Address Starts at the beginning of the keys struct.
    for ( int i=0; i*4<sizeof(keys); i++ ) { 
        int key = *(iter);
        process_keyboard(key, m_context->get_delta_time());
        iter++;
    }
    if ( m_context->get_cursor_activity() ) {
        process_mouse_movement(m_context->get_arc_x(), m_context->get_arc_y());
        m_context->set_cursor_activity(false);
        m_context->set_arc_x(0);
        m_context->set_arc_y(0);
    } else {}
    if ( m_context->get_scroll_activity() ) {
        process_mouse_scroll(m_context->get_scroll_y());
        m_context->set_scroll_activity(false);
    } else {}
    set_view_projection_transforms();
}

void Camera::set_view_projection_transforms() {
    glm::vec3 target = m_pos + m_front;
    m_services->set_view(glm::lookAt(m_pos, target, m_up));
    m_services->set_projection(glm::perspective(glm::radians(m_zoom), m_services->get_aspect_ratio(), 1.0, 100.0));
}

void Camera::set_control(bool activity) {
    m_active = activity;
}

void Camera::process_keyboard(int key, float delta_time) {
    if (m_active) {
        float velocity = m_movement_speed * delta_time;
        if (key == GLFW_KEY_W) 
            m_pos += m_front * velocity; 
        if (key == GLFW_KEY_A)
            m_pos -= m_right * velocity;
        if (key == GLFW_KEY_S)
            m_pos -= m_front * velocity;
        if (key == GLFW_KEY_D)
            m_pos += m_right * velocity;
    } else {};
}

void Camera::process_mouse_movement(double x_offset, double y_offset, GLboolean constrain_pitch) {
    x_offset /= m_mouse_sensitivity; // This acts as the radius of
    y_offset /= m_mouse_sensitivity; // the circle the camera looks within.
    glm::quat y_axis_rotation = glm::angleAxis(glm::radians(float(x_offset)), m_world_up);  // Yaw rotation (around the world's up axis)
    glm::quat x_axis_rotation = glm::angleAxis(glm::radians(float(-y_offset)), m_right);  // Pitch rotation (around the right axis)
    // Apply the rotations to the current orientation quaternion
    m_orientation = y_axis_rotation * m_orientation;  // Apply yaw rotation ** Order matters
    m_orientation = x_axis_rotation * m_orientation;  // Apply pitch rotation ** Order matters
    m_orientation = glm::normalize(m_orientation);

    Camera::update_camera_vectors(); 
}

void Camera::update_camera_vectors(const glm::quat& orientation) {
    m_front = orientation * m_front;
    m_right = glm::normalize(glm::cross(m_front, m_world_up));
    m_up = glm::normalize(glm::cross(m_right, m_front));
}

void Camera::process_mouse_scroll(double y_offset) {
    if (!m_active) { return; }
    else {
        m_zoom -= y_offset; // Scroll down will zoom out, that is, increase the fovy
    }
}
