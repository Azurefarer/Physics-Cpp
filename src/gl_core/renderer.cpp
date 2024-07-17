#include "gl_core/renderer.h"
#include <stdexcept>

void GL_clear_error() {
    while (glGetError() != GL_NO_ERROR);
}

bool GL_log_call(const char* function, const char* file, int line) {
    while (GLenum error = glGetError()) {
        std::cout << "[OpenGL Error] (" << error << "): " << function <<
            " " << file << ":" << line << std::endl;
        return false;
    }
    return true;
}

void viewport_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

Window::Window(unsigned int width, unsigned int height, const char *title) {
    m_width = width; m_height = height;
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
    GL_call(glEnable(GL_DEPTH_TEST));
}

Window::~Window() {
    glfwTerminate();
}

void Window::process_input(GLFWwindow* window) {
    glfwGetCursorPos(window, &m_cursor_pos_x, &m_cursor_pos_y);
    glfwGetWindowSize(window, (int*)&m_width, (int*)&m_height);
    m_cursor_pos_ratio = {(float)m_cursor_pos_x/m_width, (float)m_cursor_pos_y/m_height};

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
