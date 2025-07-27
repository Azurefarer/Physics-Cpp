#include "scene/observer.h"

Observer::Observer(const std::shared_ptr<Services>& pservices) : m_services(pservices) {

}

void Observer::run() {
    const int *iter = &(m_services->get_keys().W_key); // Memory Address Starts at the beginning of the keys struct.
    for ( int i=0; i*4<sizeof(keys); i++ ) { 
        int key = *(iter);
        process_keyboard(key, m_services->get_delta());
        iter++;
    }
    if ( m_services->get_free_cursor() ) {
        process_mouse_movement(m_services->get_cursor_diff_x(), m_services->get_cursor_diff_y());
        m_services->set_cursor_diff_x(0);
        m_services->set_cursor_diff_y(0);
    } else {}
    update_orientation(m_orientation);
}

void Observer::process_keyboard(int key, float delta_t) {
        float velocity = m_movement_speed * delta_t;
        switch (key) {
            case GLFW_KEY_W:
                m_pos += m_front * velocity;
                break;
            case GLFW_KEY_A:
                m_pos -= m_right * velocity;
                break;
            case GLFW_KEY_S:
                m_pos -= m_front * velocity;
                break;
            case GLFW_KEY_D:
                m_pos += m_right * velocity;
                break;
            default:
                // Handle cases for other keys if needed
                break;
            }
}

void Observer::process_mouse_movement(double x_offset, double y_offset, GLboolean constrain_pitch) {
    x_offset /= m_services->get_mouse_sensitivity(); // This acts as the radius of
    y_offset /= m_services->get_mouse_sensitivity(); // the circle the camera looks within.
    glm::quat yaw_rotation = glm::angleAxis(glm::radians(float(x_offset)), m_world_up);  // Yaw rotation (around the world's up axis)
    glm::quat pitch_rotation = glm::angleAxis(glm::radians(float(-y_offset)), m_right);  // Pitch rotation (around the right axis)

    m_orientation = yaw_rotation * m_orientation;  // Apply yaw rotation ** Order matters
    m_orientation = pitch_rotation * m_orientation;  // Apply pitch rotation ** Order matters
    m_orientation = glm::normalize(m_orientation);
}

void Observer::update_orientation(const glm::quat& orientation) {
    m_front = orientation * m_front;
    m_right = glm::normalize(glm::cross(m_front, m_world_up));
    m_up = glm::normalize(glm::cross(m_right, m_front));
}
