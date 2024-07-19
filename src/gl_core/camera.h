#ifndef GL_CORE_CAMERA_H_
#define GL_CORE_CAMERA_H_

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Camera {
    public:
        Camera();
        ~Camera();

        void set_pos(glm::vec3 pos) { m_pos = pos; }
        void set_target(glm::vec3 target) { m_target = target; }
        void set_up(glm::vec3 up) { m_up = up; }
        glm::mat4 get_view() const { return m_view; }
    
    private:
        glm::vec3 m_pos;
        glm::vec3 m_target;
        glm::vec3 m_up;
        glm::mat4 m_view;

        void update_view() { m_view = glm::lookAt(m_pos, m_target, m_up); }
};
#endif
