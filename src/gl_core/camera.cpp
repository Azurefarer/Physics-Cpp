#include "gl_core/camera.h"

Camera::Camera() {
    m_pos = glm::vec3(0.0f, 0.0f, 3.0f);
    m_target = glm::vec3(0.0f, 0.0f, 0.0f);
    m_up = glm::vec3(0.0f, 1.0f, 0.0f);
    m_view = glm::lookAt(m_pos, m_target, m_up);
}

Camera::~Camera() {
    
}
