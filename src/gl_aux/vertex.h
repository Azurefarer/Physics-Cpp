#ifndef GL_AUX_VERTEX_H_
#define GL_AUX_VERTEX_H_

#include "glm/glm.hpp"

struct Vertex {
    glm::vec3 position;
    glm::vec4 color;
    glm::vec2 uv;
    float tex_index;
};

#endif