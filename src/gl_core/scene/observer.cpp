#include "scene/observer.h"

Observer::Observer() {

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
    x_offset /= m_mouse_sensitivity; // This acts as the radius of
    y_offset /= m_mouse_sensitivity; // the circle the camera looks within.
    glm::quat yaw_rotation = glm::angleAxis(glm::radians(float(x_offset)), m_world_up);  // Yaw rotation (around the world's up axis)
    glm::quat pitch_rotation = glm::angleAxis(glm::radians(float(-y_offset)), m_right);  // Pitch rotation (around the right axis)
    // Apply the rotations to the current orientation quaternion
    m_orientation = yaw_rotation * m_orientation;  // Apply yaw rotation ** Order matters
    m_orientation = pitch_rotation * m_orientation;  // Apply pitch rotation ** Order matters
    m_orientation = glm::normalize(m_orientation);

}
