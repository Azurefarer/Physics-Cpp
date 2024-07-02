#include "gl_core/window.h"
#include <stdexcept>

Window::Window(unsigned int width, unsigned int height, const char *title) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    m_window = glfwCreateWindow(width, height, title, NULL, NULL);
	if (m_window == NULL) {
		glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
	}
    glfwMakeContextCurrent(m_window);
    glfwSetFramebufferSizeCallback(m_window, viewport_size_callback);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		throw std::runtime_error("Failed to initialize GLAD");
	}
}

Window::~Window() {};

void Window::process_input(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
