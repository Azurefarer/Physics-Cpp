#ifndef GL_AUX_VERTEX_H_
#define GL_AUX_VERTEX_H_

#include "glm/glm.hpp"

// TODO: Add a sphere

struct Vertex {
    glm::vec3 position;
    glm::vec4 color;
    glm::vec2 uv;
    glm::vec3 normal;
    float tex_index;
};

struct MVP {
    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 projection;
};

#endif