#include "gl_aux/cube.h"

Cube::Cube() {
    m_verts = {
        {glm::vec3(-0.5, -0.5, -0.5),  glm::vec4(0.0, 0.0, 1.0, 1.0),  glm::vec2(1.0, 0.0)}, //back bottom left
        {glm::vec3(-0.5, -0.5, 0.5),  glm::vec4(1.0, 1.0, 1.0, 1.0),  glm::vec2(0.0, 0.0)}, //front bottom left
        {glm::vec3(-0.5, 0.5, -0.5),  glm::vec4(0.0, 0.0, 1.0, 1.0),  glm::vec2(1.0, 1.0)}, //back top left
        {glm::vec3(-0.5, 0.5, 0.5),  glm::vec4(1.0, 1.0, 1.0, 1.0),  glm::vec2(0.0, 1.0)}, //front top left
        {glm::vec3(0.5, -0.5, -0.5),  glm::vec4(1.0, 0.0, 0.0, 1.0),  glm::vec2(0.0, 0.0)}, //back bottom right
        {glm::vec3(0.5, -0.5, 0.5),  glm::vec4(0.0, 1.0, 0.0, 1.0),  glm::vec2(1.0, 0.0)}, //front bottom right
        {glm::vec3(0.5, 0.5, -0.5),  glm::vec4(1.0, 0.0, 0.0, 1.0),  glm::vec2(0.0, 1.0)}, //back top right
        {glm::vec3(0.5, 0.5, 0.5),  glm::vec4(0.0, 1.0, 0.0, 1.0),  glm::vec2(1.0, 1.0)} //front top right
    };

    m_indices = {
        // left face
        0, 1, 2,
        1, 2, 3,
        // right face
        5, 4, 7,
        4, 7, 6,
        // front face
        1, 5, 3,
        5, 3, 7,
        // back face
        4, 0, 6,
        0, 6, 2,
        // bottom face
        4, 5, 0,
        5, 0, 1,
        // top face
        6, 7, 2,
        7, 2, 3
    };
}
