#ifndef GL_CORE_RENDERER_H_
#define GL_CORE_RENDERER_H_

#include <iostream>
#include <map>
#include <memory>
#include <vector>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

#define ASSERT(x) if (!(x)) __debugbreak();
#define GL_call(x) GL_clear_error();\
    x;\
    ASSERT(GL_log_call(#x, __FILE__, __LINE__))

struct Vertex {
    float x, y, z;
    float r, g, b;
    // float nx, ny, nz;
    float u, v;
};

void GL_clear_error();
bool GL_log_call(const char* function, const char* file, int line);
void viewport_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double x_pos, double y_pos);
void scroll_callback(GLFWwindow* window, double x_offset, double y_offset);

enum CameraMovement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

class Camera {
    public:
        Camera();
        ~Camera();

        void process_keyboard(CameraMovement direction, float delta_time);
        void process_mouse_movement(double x_offset, double y_offset, GLboolean constrain_pitch = true);
        void process_mouse_scroll(double y_offset);

        float get_pos() const { return m_pos.x; }
        float get_zoom() const { return m_zoom; }

        glm::mat4 get_view() const { return glm::lookAt(m_pos, m_pos + m_front, m_up); }
    
    private:
        float m_yaw = -90.0f;
        float m_pitch = 0.0f;
        float m_movement_speed = 2.5f;
        float m_mouse_sensitivity = 0.1f;
        double m_zoom = 45.0f;

        glm::vec3 m_pos = glm::vec3(0.0f, 0.0f, 3.0f);
        glm::vec3 m_front = glm::vec3(0.0f, 0.0f, -1.0f);
        glm::vec3 m_up = glm::vec3(0.0f, 1.0f, 0.0f);
        glm::vec3 m_world_up = glm::vec3(0.0f, 1.0f, 0.0f);
        glm::vec3 m_right = glm::normalize(glm::cross(m_front, m_world_up));

        void update_camera_vectors();
};

class RenderPipelineContext {
    public:
        RenderPipelineContext(int width, int height, std::string title);
        ~RenderPipelineContext();

        void process_input(GLFWwindow* window);
        float get_delta();

        void run();

        void set_transforms();
        glm::mat4 get_transform(std::string key) const { return m_transforms.at(key); };
        glm::mat4 get_view() const { return m_camera->get_view(); }

        std::vector<float> get_cursor_pos_ratio() const { return m_cursor_pos_ratio; }

        GLFWwindow* get_window() const { return m_window; }

    private:
        GLFWwindow* m_window;
        int m_width;
        int m_height;
        float m_aspect_ratio = 0;

        float m_delta = 0.0f;
        float m_last_frame = 0.0f;

        double m_cursor_pos_x = 0;
        double m_cursor_pos_y = 0;
        std::vector<float> m_cursor_pos_ratio{0, 0};

        glm::mat4 m_model;
        glm::mat4 m_view;
        glm::mat4 m_projection;

        std::map<std::string, glm::mat4> m_transforms;

        std::unique_ptr<Camera> m_camera = std::make_unique<Camera>();

        // std::unique_ptr<Shader> m_shader;
        void set_callbacks();
        void keyboard_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
        void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);
        void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
};

#endif
