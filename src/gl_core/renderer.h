#pragma once
#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"

// #define ASSERT(x) if (!(x)) __debugbreak();
// #define GL_call(x) std::cout << "hello preproccesor" << std::endl;\
//     GL_clear_error();\
//     x;\
//     ASSERT(GL_log_call(#x, __FILE__, __LINE__))

void GL_clear_error();
bool GL_log_call(const char* function, const char* file, int line);
void viewport_size_callback(GLFWwindow* window, int width, int height);
