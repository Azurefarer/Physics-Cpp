#include "gl_core/camera.h"

Camera::Camera(const std::shared_ptr<Context>& pcontext) : 
    m_context(pcontext),
    m_pos(glm::vec3(0.0f, 2.0f, 15.0f)),
    m_world_up(glm::vec3(0.0f, 1.0f, 0.0f))
{
    m_yaw = 0;
    m_pitch = 0.0;
    update_camera_vectors();
    set_view();
    m_context->set_MVP(m_view, m_zoom);
}

void Camera::run() {
    set_control(!m_context->get_gui_focus());
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
    set_view();
    m_context->set_MVP(m_view, m_zoom);
}

void Camera::set_view() {
    glm::vec3 target = m_pos + m_front;
    m_view = glm::lookAt(m_pos, target, m_up); 
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
    } else { return; }
}

void Camera::process_mouse_movement(double x_offset, double y_offset, GLboolean constrain_pitch) {
    if (m_active) { 
        x_offset /= m_mouse_sensitivity; // This acts as the radius of
        y_offset /= m_mouse_sensitivity; // the circle the camera looks within.
        m_yaw += x_offset; // negative because z-axis is flipped
        m_pitch += y_offset;
        if (m_pitch >= std::numbers::pi / 2)
            m_pitch = std::numbers::pi / 2;
        if (m_pitch <= -std::numbers::pi / 2)
            m_pitch = -std::numbers::pi / 2;
        Camera::update_camera_vectors(); 
    } else { 
        return; 
    }
}

void Camera::update_camera_vectors() {
    m_front.x = sin(m_yaw) *    cos(m_pitch);
    m_front.y =                 sin(m_pitch);
    m_front.z = -cos(m_yaw) *   cos(m_pitch);
    m_right =   glm::normalize(glm::cross(m_front, m_world_up)); // Have to normalize otherwise looking down restricts left and right movement
    m_up =      glm::cross(m_right, m_front);
}

void Camera::process_mouse_scroll(double y_offset) {
    if (!m_active) { return; }
    else {
        m_zoom -= y_offset; // Scroll down will zoom out, that is, increase the fovy
    }
}
