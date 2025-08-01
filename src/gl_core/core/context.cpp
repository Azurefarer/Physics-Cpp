#include "core/context.h"

Context::Context(int width, int height, std::string title) :
m_width(width),
m_height(height),
m_title(title) {
    glfwInit();
    // glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);  // 4 fails with macos
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
    m_window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
	if (m_window == NULL) {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
	}
    glfwMakeContextCurrent(m_window);
    glfwSetWindowPos(m_window, 10, 10); // Make this flush with OS taskbar or fullscreen it.
    
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        throw std::runtime_error("Failed to initialize GLAD");
	}
    glfwSwapInterval(0);
    glEnable(GL_DEBUG_OUTPUT);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnable(GL_DEPTH_TEST);
//    set_GLcallbacks();
    glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

Context::~Context() {
    glfwTerminate();
}

void Context::run() {
    glfwPollEvents();

    m_current_frame = glfwGetTime();
    m_delta = m_current_frame - m_last_frame;
    m_last_frame = m_current_frame;
}

double Context::get_aspect_ratio() const {
    if ((m_width <= 0) || (m_height <= 0)) {
        // TODO: need a runtime error strategy - return std::optional, std::expected, throw, other?
        throw std::runtime_error(m_title + ": error - bad window size");
    }
    return static_cast<double>(m_width)/static_cast<double>(m_height);
}

void Context::set_resolution(int width, int height) {
    glfwSetWindowSize(m_window, width, height);
}

void Context::swap_buffers() {
    glfwSwapBuffers(m_window);
}

void Context::set_GLcallbacks() {
    static auto message_callback_static = [this](GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
        Context::message_callback(source, type, id, severity, length, message, userParam);
    };
    glDebugMessageCallback(
        [](GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
            message_callback_static(source, type, id, severity, length, message, userParam);},
        0
    );
}

void Context::message_callback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) { 
    if (type == GL_DEBUG_TYPE_OTHER) {
            return;
    }
    fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
        ( type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "" ), type, severity, message
    );
};
