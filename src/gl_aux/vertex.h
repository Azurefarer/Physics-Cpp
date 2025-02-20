#ifndef GL_AUX_VERTEX_H_
#define GL_AUX_VERTEX_H_

#include "glm/glm.hpp"

// TODO: Add a sphere

// I think these things need to be stored on the Heap.  I'm generating a boat load of 'em
// So this might become a bottleneck if I keep it like this where each vertex ius stored on the stack
// Make the position the GR space-time 4vector
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
}; // Make it so each obj in the scene only knows about a model matrix
   // the View and PRojection Matricies should be accessed from elsewhere.
   // 

#endif