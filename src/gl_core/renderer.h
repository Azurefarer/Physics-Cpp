#pragma once
#include <iostream>
#include <vector>
#include "glad/glad.h"
#include "GLFW/glfw3.h"

#define ASSERT(x) if (!(x)) __debugbreak();
#define GL_call(x) GL_clear_error();\
    x;\
    ASSERT(GL_log_call(#x, __FILE__, __LINE__))

typedef struct {
    float x, y, z;
    float r, g, b;
    // float nx, ny, nz;
    float u, v;
} Vertex;

void GL_clear_error();
bool GL_log_call(const char* function, const char* file, int line);
void viewport_size_callback(GLFWwindow* window, int width, int height);
