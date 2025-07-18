#ifndef GL_AUX_VERTEX_H_
#define GL_AUX_VERTEX_H_

#include "glm/glm.hpp"

// TODO: Add a sphere


// { vec3 pos, vec4 color, vec2 uv, vec3 normal, float tex_index }
struct Vertex {
    glm::vec3 position;
    glm::vec4 color;
    glm::vec2 uv;
    glm::vec3 normal;
    float tex_index;
    Vertex(glm::vec3 position = glm::vec3(0.0),
        glm::vec4 color = glm::vec4(1.0),
        glm::vec2 uv = glm::vec2(1.0),
        glm::vec3 normal = glm::vec3(0.0),
        float tex_index = 1.0) : 
        position(position), color(color), uv(uv), normal(normal), tex_index(tex_index) {}
};

struct MVP {
    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 projection;
    MVP() : model(glm::mat4(1.0)), view(glm::mat4(1.0)), projection(glm::mat4(1.0)) {}
}; // Make it so each obj in the scene only knows about a model matrix
   // the View and PRojection Matricies should be accessed from elsewhere.
   // 

#endif