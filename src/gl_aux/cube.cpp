#include "gl_aux/cube.h"

Cube::Cube() {
    m_verts = {
        {-0.5, -0.5, -0.5,  0.0, 0.0, 0.0,  0.0, 0.0}, //back bottom left
        {-0.5, -0.5, 0.5,  0.0, 0.0, 0.0,  0.0, 0.0}, //front bottom left
        {-0.5, 0.5, -0.5,  0.0, 0.0, 0.0,  0.0, 0.0}, //back top left
        {-0.5, 0.5, 0.5,  0.0, 0.0, 0.0,  0.0, 0.0}, //front top left
        {0.5, -0.5, -0.5,  0.0, 0.0, 0.0,  0.0, 0.0}, //back bottom right
        {0.5, -0.5, 0.5,  0.0, 0.0, 0.0,  0.0, 0.0}, //front bottom right
        {0.5, 0.5, -0.5,  0.0, 0.0, 0.0,  0.0, 0.0}, //back top right
        {0.5, 0.5, 0.5,  0.0, 0.0, 0.0,  0.0, 0.0} //front top right
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
        5, 0, 6,
        0, 6, 2,
        // bottom face
        5, 6, 0,
        6, 0, 1,
        // top face
        7, 6, 3,
        6, 3, 2
    };
}

Cube::~Cube() {
    
}
