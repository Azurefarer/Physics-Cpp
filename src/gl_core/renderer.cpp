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

Camera::Camera() {}
Camera::~Camera() {}

void Camera::process_keyboard(CameraMovement direction, float delta_time) {
    float velocity = m_movement_speed * delta_time;
    if (direction == FORWARD)
        m_pos += m_front * velocity;
    if (direction == BACKWARD)
        m_pos -= m_front * velocity;
    if (direction == LEFT)
        m_pos -= m_right * velocity;
    if (direction == RIGHT)
        m_pos += m_right * velocity;
}

void Camera::process_mouse_movement(double x_offset, double y_offset, GLboolean constrain_pitch) {

}

void Camera::process_mouse_scroll(double y_offset) {
    m_zoom += y_offset;
}

void Camera::update_camera_vectors() {
    glm::vec3 front;
    front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    front.y = sin(glm::radians(m_pitch));
    front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    m_front = glm::normalize(front);
    m_right = glm::normalize(glm::cross(m_front, m_world_up));
    m_up = glm::normalize(glm::cross(m_right, m_front));
}


RenderPipelineContext::RenderPipelineContext(int width, int height, std::string title) 
    : m_width(width), m_height(height) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    m_window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
	if (m_window == NULL) {
		glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
	}
    glfwMakeContextCurrent(m_window);

    RenderPipelineContext::set_callbacks();

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		throw std::runtime_error("Failed to initialize GLAD");
	}
    GL_call(glEnable(GL_DEPTH_TEST));

    glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    m_transforms["MODEL"] = m_model;
    m_transforms["VIEW"] = m_view;
    m_transforms["PROJECTION"] = m_projection;
}

RenderPipelineContext::~RenderPipelineContext() {
    glfwTerminate();
}

void RenderPipelineContext::process_input(GLFWwindow* window) {
    float delta = RenderPipelineContext::get_delta();
}

float RenderPipelineContext::get_delta() {
    float current_frame = glfwGetTime();
    m_delta = current_frame - m_last_frame;
    m_last_frame = current_frame;
    return m_delta;
}

void RenderPipelineContext::run() {
    RenderPipelineContext::process_input(m_window);
    RenderPipelineContext::set_transforms();
    GL_call(glClearColor(0.0f, RenderPipelineContext::get_cursor_pos_ratio()[0], RenderPipelineContext::get_cursor_pos_ratio()[1], 1.0f));
	GL_call(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

    // glfwSwapBuffers(m_window);
	// glfwPollEvents();
}

void RenderPipelineContext::set_transforms() {
    m_model = glm::mat4(1.0f);
    m_view = m_camera->get_view();
    m_projection = glm::mat4(1.0f);

    m_model = glm::rotate(m_model, glm::radians(m_cursor_pos_ratio[1]*360.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    m_model = glm::rotate(m_model, glm::radians(m_cursor_pos_ratio[0]*360.0f), glm::vec3(0.0f, -1.0f, 0.0f));

    m_projection = glm::perspective(glm::radians(m_camera->get_zoom()), m_aspect_ratio, 0.1f, 100.0f);

    m_transforms["MODEL"] = m_model;
    m_transforms["VIEW"] = m_view;
    m_transforms["PROJECTION"] = m_projection;
}

void RenderPipelineContext::set_callbacks() {
    glfwSetFramebufferSizeCallback(m_window, viewport_size_callback);
    
    static auto key_callback_static = [this](GLFWwindow* window, int key, int scancode, int action, int mods) {
        RenderPipelineContext::keyboard_callback(window, key, scancode, action, mods);
    };
    glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
        key_callback_static(window, key, scancode, action, mods);
        }
    );
    static auto mouse_pos_callback_static = [this](GLFWwindow* window, double xposIn, double yposIn) {
        RenderPipelineContext::mouse_callback(window, xposIn, yposIn);
    };
    glfwSetCursorPosCallback(m_window, [](GLFWwindow* window, double xposIn, double yposIn) {
        mouse_pos_callback_static(window, xposIn, yposIn);
        }
    );
    static auto scroll_callback_static = [this](GLFWwindow* window, double xoffset, double yoffset) {
        RenderPipelineContext::scroll_callback(window, xoffset, yoffset);
    };
    glfwSetScrollCallback(m_window, [](GLFWwindow* window, double xoffset, double yoffset) {
        scroll_callback_static(window, xoffset, yoffset);
        }
    );
}

void RenderPipelineContext::keyboard_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    float delta = RenderPipelineContext::get_delta();
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        m_camera->process_keyboard(RIGHT, delta);
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        m_camera->process_keyboard(LEFT, delta);
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        m_camera->process_keyboard(BACKWARD, delta);
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        m_camera->process_keyboard(FORWARD, delta);
}

void RenderPipelineContext::mouse_callback(GLFWwindow* window, double xposIn, double yposIn) {
    m_cursor_pos_x = xposIn;
    m_cursor_pos_y = yposIn;
    glfwGetWindowSize(window, &m_width, &m_height);
    m_aspect_ratio = static_cast<float>(m_width)/static_cast<float>(m_height);
    m_cursor_pos_ratio = {(float)m_cursor_pos_x/m_width, (float)m_cursor_pos_y/m_height};
    m_camera->process_mouse_movement(xposIn, yposIn);
}

void RenderPipelineContext::scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    m_camera->process_mouse_scroll(yoffset);
}
