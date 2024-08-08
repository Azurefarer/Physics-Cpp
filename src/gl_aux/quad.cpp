#include "gl_aux/quad.h"

Quad::Quad() {
    m_verts = {
        {glm::vec3(-0.5, -0.5, 0.0),  glm::vec4(0.2, 0.7, 0.5, 1.0),  glm::vec2(0.0, 0.0)},
        {glm::vec3(0.5, -0.5, 0.0),  glm::vec4(0.4, 0.9, 0.3, 1.0),  glm::vec2(1.0, 0.0)},
        {glm::vec3(-0.5, 0.5, 0.0),  glm::vec4(0.9, 0.7, 0.1, 1.0),  glm::vec2(0.0, 1.0)},
        {glm::vec3(0.5, 0.5, 0.0),  glm::vec4(0.3, 0.7, 0.1, 1.0),  glm::vec2(1.0, 1.0)}
    };
    m_indices = {
        0, 1, 2,
        1, 2, 3
    };
}
