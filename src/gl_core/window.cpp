#include "gl_core/window.h"

Window::Window(unsigned int width, unsigned int height, const char *title) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    m_window = glfwCreateWindow(width, height, title, NULL, NULL);
    glfwMakeContextCurrent(m_window);
    std::cout << "this is the current constext" << glfwGetCurrentContext() << std::endl;
}

Window::~Window() {};

void Window::process_input(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
