#include "gl_core/context.h"

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
    static auto viewport_callback_static = [this](GLFWwindow* window, int width, int height) {
        Context::viewport_size_callback(window, width, height);
    };
    glfwSetFramebufferSizeCallback(m_window, [](GLFWwindow* window, int width, int height) {
        viewport_callback_static(window, width, height);
        }
    );

    static auto key_callback_static = [this](GLFWwindow* window, int key, int scancode, int action, int mods) {
        Context::keyboard_callback(window, key, scancode, action, mods);
    };
    glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
        key_callback_static(window, key, scancode, action, mods);
        }
    );

    static auto cursor_pos_callback_static = [this](GLFWwindow* window, double xposIn, double yposIn) {
        Context::cursor_pos_callback(window, xposIn, yposIn);
    };
    glfwSetCursorPosCallback(m_window, [](GLFWwindow* window, double xposIn, double yposIn) {
        cursor_pos_callback_static(window, xposIn, yposIn);
        }
    );

    static auto cursor_entered_callback_static = [this](GLFWwindow* window, int entered) {
        Context::cursor_entered_callback(window, entered);
    };
    glfwSetCursorEnterCallback(m_window, [](GLFWwindow* window, int entered) {
        cursor_entered_callback_static(window, entered);
        }
    );

    static auto scroll_callback_static = [this](GLFWwindow* window, double xoffset, double yoffset) {
        Context::scroll_callback(window, xoffset, yoffset);
    };
    glfwSetScrollCallback(m_window, [](GLFWwindow* window, double xoffset, double yoffset) {
        scroll_callback_static(window, xoffset, yoffset);
        }
    );
}

void Context::viewport_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    m_services->set_aspect_ratio(static_cast<float>(width)/static_cast<float>(height));
    m_aspect_ratio = static_cast<float>(width)/static_cast<float>(height);

    m_width = width;
    m_height = height;
}

void Context::keyboard_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if ( action == GLFW_REPEAT ) {
        return;
    }
    if ( action == GLFW_PRESS ) {
        if ( key == GLFW_KEY_ESCAPE ) {
            glfwSetWindowShouldClose(window, true);
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

void Context::cursor_pos_callback(GLFWwindow* window, double xposIn, double yposIn) {
    m_arc_x += xposIn - m_cursor_pos_x;
    m_arc_y += m_cursor_pos_y - yposIn;
    m_cursor_pos_x = xposIn;
    m_cursor_pos_y = yposIn;
    m_cursor_pos_ratio = {m_cursor_pos_x/m_width, m_cursor_pos_y/m_height};

    set_cursor_activity(true);
}

void Context::cursor_entered_callback(GLFWwindow* window, int entered) {
    glfwSetCursorPos(m_window, m_cursor_pos_x, m_cursor_pos_y);
}

void Context::scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    m_scroll_x_offset = xoffset;
    m_scroll_y_offset = yoffset;
    
    m_scroll_activity = true;
}
