#include "gl_aux/cube.h"

Cube::Cube() {
    m_verts = {
        {glm::vec3(-0.5, -0.5, -0.5),  glm::vec4(0.0, 0.0, 1.0, 1.0),  glm::vec2(1.0, 0.0),  glm::vec3(-1.0, 0.0, 0.0)}, //back bottom left
        {glm::vec3(-0.5, -0.5, -0.5),  glm::vec4(0.0, 0.0, 1.0, 1.0),  glm::vec2(1.0, 0.0),  glm::vec3(0.0, -1.0, 0.0)}, //back bottom left
        {glm::vec3(-0.5, -0.5, -0.5),  glm::vec4(0.0, 0.0, 1.0, 1.0),  glm::vec2(1.0, 0.0),  glm::vec3(0.0, 0.0, -1.0)},
         //back bottom left
        {glm::vec3(-0.5, -0.5, 0.5),  glm::vec4(1.0, 1.0, 1.0, 1.0),  glm::vec2(0.0, 0.0),  glm::vec3(-1.0, 0.0, 0.0)}, //front bottom left
        {glm::vec3(-0.5, -0.5, 0.5),  glm::vec4(1.0, 1.0, 1.0, 1.0),  glm::vec2(0.0, 0.0),  glm::vec3(0.0, -1.0, 0.0)}, //front bottom left
        {glm::vec3(-0.5, -0.5, 0.5),  glm::vec4(1.0, 1.0, 1.0, 1.0),  glm::vec2(0.0, 0.0),  glm::vec3(0.0, 0.0, 1.0)},
        //front bottom left
        {glm::vec3(-0.5, 0.5, -0.5),  glm::vec4(0.0, 0.0, 1.0, 1.0),  glm::vec2(1.0, 1.0),  glm::vec3(-1.0, 0.0, 0.0)}, //back top left
        {glm::vec3(-0.5, 0.5, -0.5),  glm::vec4(0.0, 0.0, 1.0, 1.0),  glm::vec2(1.0, 1.0),  glm::vec3(0.0, 1.0, 0.0)}, //back top left
        {glm::vec3(-0.5, 0.5, -0.5),  glm::vec4(0.0, 0.0, 1.0, 1.0),  glm::vec2(1.0, 1.0),  glm::vec3(0.0, 0.0, -1.0)},
        //back top left
        {glm::vec3(-0.5, 0.5, 0.5),  glm::vec4(1.0, 1.0, 1.0, 1.0),  glm::vec2(0.0, 1.0),  glm::vec3(-1.0, 0.0, 0.0)}, //front top left
        {glm::vec3(-0.5, 0.5, 0.5),  glm::vec4(1.0, 1.0, 1.0, 1.0),  glm::vec2(0.0, 1.0),  glm::vec3(0.0, 1.0, 0.0)}, //front top left
        {glm::vec3(-0.5, 0.5, 0.5),  glm::vec4(1.0, 1.0, 1.0, 1.0),  glm::vec2(0.0, 1.0),  glm::vec3(0.0, 0.0, 1.0)},
        //front top left
        {glm::vec3(0.5, -0.5, -0.5),  glm::vec4(1.0, 0.0, 0.0, 1.0),  glm::vec2(0.0, 0.0),  glm::vec3(1.0, 0.0, 0.0)}, //back bottom right
        {glm::vec3(0.5, -0.5, -0.5),  glm::vec4(1.0, 0.0, 0.0, 1.0),  glm::vec2(0.0, 0.0),  glm::vec3(0.0, -1.0, 0.0)}, //back bottom right
        {glm::vec3(0.5, -0.5, -0.5),  glm::vec4(1.0, 0.0, 0.0, 1.0),  glm::vec2(0.0, 0.0),  glm::vec3(0.0, 0.0, -1.0)},
        //back bottom right
        {glm::vec3(0.5, -0.5, 0.5),  glm::vec4(0.0, 1.0, 0.0, 1.0),  glm::vec2(1.0, 0.0),  glm::vec3(1.0, 0.0, 0.0)}, //front bottom right
        {glm::vec3(0.5, -0.5, 0.5),  glm::vec4(0.0, 1.0, 0.0, 1.0),  glm::vec2(1.0, 0.0),  glm::vec3(0.0, -1.0, 0.0)}, //front bottom right
        {glm::vec3(0.5, -0.5, 0.5),  glm::vec4(0.0, 1.0, 0.0, 1.0),  glm::vec2(1.0, 0.0),  glm::vec3(0.0, 0.0, 1.0)},
        //front bottom right
        {glm::vec3(0.5, 0.5, -0.5),  glm::vec4(1.0, 0.0, 0.0, 1.0),  glm::vec2(0.0, 1.0),  glm::vec3(1.0, 0.0, 0.0)}, //back top right
        {glm::vec3(0.5, 0.5, -0.5),  glm::vec4(1.0, 0.0, 0.0, 1.0),  glm::vec2(0.0, 1.0),  glm::vec3(0.0, 1.0, 0.0)}, //back top right
        {glm::vec3(0.5, 0.5, -0.5),  glm::vec4(1.0, 0.0, 0.0, 1.0),  glm::vec2(0.0, 1.0),  glm::vec3(0.0, 0.0, -1.0)},
        //back top right
        {glm::vec3(0.5, 0.5, 0.5),  glm::vec4(0.0, 1.0, 0.0, 1.0),  glm::vec2(1.0, 1.0),  glm::vec3(1.0, 0.0, 0.0)}, //front top right
        {glm::vec3(0.5, 0.5, 0.5),  glm::vec4(0.0, 1.0, 0.0, 1.0),  glm::vec2(1.0, 1.0),  glm::vec3(0.0, 1.0, 0.0)}, //front top right
        {glm::vec3(0.5, 0.5, 0.5),  glm::vec4(0.0, 1.0, 0.0, 1.0),  glm::vec2(1.0, 1.0),  glm::vec3(0.0, 0.0, 1.0)}
        //front top right
    };

    m_indices = {
        // left face
        0, 3, 6,
        3, 6, 12,
        // right face
        15, 12, 21,
        12, 21, 18,
        // front face
        5, 17, 11,
        17, 11, 23,
        // back face
        14, 2, 20,
        2, 20, 8,
        // bottom face
        13, 16, 1,
        16, 1, 4,
        // top face
        19, 22, 7,
        22, 7, 10
    };
}
