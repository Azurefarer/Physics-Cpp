#include "gl_core/renderer.h"

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
