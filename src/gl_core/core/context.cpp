#include "core/context.h"

Context::Context(int width, int height, std::string title, const std::shared_ptr<Services>& pservices) 
    : m_width(width),
    m_height(height),
    m_cursor_pos_x(width/2),
    m_cursor_pos_y(height/2),
    m_services(pservices)
    {
    
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
    m_window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
	if (m_window == NULL) { 
		glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
	}
    glfwMakeContextCurrent(m_window);
    glfwSetWindowPos(m_window, 0, 10); // Make this flush with OS taskbar or fullscreen it.
    glfwSetWindowUserPointer(m_window, this); // glfw expects a void *, so instead we set it to expect context *
    set_GLFWcallbacks();

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		throw std::runtime_error("Failed to initialize GLAD");
	}
    glfwSwapInterval(0);
    glEnable(GL_DEBUG_OUTPUT);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnable(GL_DEPTH_TEST);
    set_GLcallbacks();
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
    m_services->set_time(m_current_frame);
    m_services->set_delta(m_delta);
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

void Context::set_GLFWcallbacks() {
    glfwSetFramebufferSizeCallback(m_window, viewport_size_callback);
    glfwSetKeyCallback(m_window, keyboard_callback);
    glfwSetCursorPosCallback(m_window, cursor_pos_callback);
    glfwSetCursorEnterCallback(m_window, cursor_entered_callback);
    glfwSetScrollCallback(m_window, scroll_callback);
}

void Context::viewport_size_callback(GLFWwindow* window, int width, int height) {
    if (auto* ctx = static_cast<Context*>(glfwGetWindowUserPointer(window))) {
        ctx->on_resize(width, height);
    }
}

void Context::keyboard_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (auto* ctx = static_cast<Context*>(glfwGetWindowUserPointer(window))) {
        ctx->on_key(key, scancode, action, mods);
    }
}

void Context::cursor_pos_callback(GLFWwindow* window, double xpos, double ypos) {
    if (auto* ctx = static_cast<Context*>(glfwGetWindowUserPointer(window))) {
        ctx->on_cursor_pos(xpos, ypos);
    }
}

void Context::cursor_entered_callback(GLFWwindow* window, int entered) {
    if (auto* ctx = static_cast<Context*>(glfwGetWindowUserPointer(window))) {
        ctx->on_cursor_enter(entered);
    }
}

void Context::scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    if (auto* ctx = static_cast<Context*>(glfwGetWindowUserPointer(window))) {
        ctx->on_scroll(xoffset, yoffset);
    }
}

void Context::on_resize(int width, int height) {
    glViewport(0, 0, width, height);
    m_aspect_ratio = static_cast<float>(width)/static_cast<float>(height);

    m_width = width;
    m_height = height;
}

void Context::on_key(int key, int scancode, int action, int mods) {
    if ( action == GLFW_REPEAT ) {
        return;
    }
    if ( action == GLFW_PRESS ) {
        if ( key == GLFW_KEY_ESCAPE ) {
            glfwSetWindowShouldClose(m_window, true);
        }
        if ( key == GLFW_KEY_TAB ) {
            if ( m_gui_focus == false ) {
                (*m_keys).Ltab_key = key;
                glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
                set_gui_focus(true);
            } else {
                (*m_keys).Ltab_key = -1;
                glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
                set_gui_focus(false); 
            }
        }
        if ( key == GLFW_KEY_W ) {
            (*m_keys).W_key = key;
        }
        if ( key == GLFW_KEY_A ) {
            (*m_keys).A_key = key;
        }
        if ( key == GLFW_KEY_S ) {
            (*m_keys).S_key = key;
        }
        if ( key == GLFW_KEY_D ) {
            (*m_keys).D_key = key;
        }
    }
    if ( action == GLFW_RELEASE ) {
        if ( key == GLFW_KEY_W ) {
            (*m_keys).W_key = -1;
        }
        if ( key == GLFW_KEY_A ) {
            (*m_keys).A_key = -1;
        }
        if ( key == GLFW_KEY_S ) {
            (*m_keys).S_key = -1;
        }
        if ( key == GLFW_KEY_D ) {
            (*m_keys).D_key = -1;
        }
    }
}

void Context::on_cursor_pos(double xposIn, double yposIn) {
    m_arc_x += xposIn - m_cursor_pos_x;
    m_arc_y += m_cursor_pos_y - yposIn;
    m_cursor_pos_x = xposIn;
    m_cursor_pos_y = yposIn;
    m_cursor_pos_ratio = {m_cursor_pos_x/m_width, m_cursor_pos_y/m_height};

    set_cursor_activity(true);
}

void Context::on_cursor_enter(int entered) {
    glfwSetCursorPos(m_window, m_cursor_pos_x, m_cursor_pos_y);
}

void Context::on_scroll(double xoffset, double yoffset) {
    m_scroll_x_offset = xoffset;
    m_scroll_y_offset = yoffset;
    
    m_scroll_activity = true;
}
