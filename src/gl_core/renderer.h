#ifndef GL_CORE_RENDERER_H_
#define GL_CORE_RENDERER_H_

#define GLM_ENABLE_EXPERIMENTAL

#include <iostream>
#include <numbers>
#include <map>
#include <memory>
#include <vector>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/string_cast.hpp"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "gl_aux/cube.h"
#include "gl_aux/quad.h"
#include "gl_core/shader.h"
#include "gl_core/shape_man.h"
#include "gl_core/texture_man.h"

double radian(double degrees);
void GL_clear_error();
bool GL_log_call(const char* function, const char* file, int line);

enum CameraMovement {
    FORWARD = GLFW_KEY_W,
    BACKWARD = GLFW_KEY_S,
    LEFT = GLFW_KEY_A,
    RIGHT = GLFW_KEY_D
};

class Camera {
    public:
        Camera();

        void process_keyboard(int key, float delta_time);
        void process_mouse_movement(double x_offset, double y_offset, GLboolean constrain_pitch = true);
        void process_mouse_scroll(double y_offset);

        float get_pos() const { return m_pos.x; }
        float get_zoom() const { return m_zoom; }

        glm::mat4 get_view() const { return glm::lookAt(m_pos, m_pos + m_front, m_up); }
    
    private:
        double m_yaw = -(std::numbers::pi / 2);
        double m_pitch = 0.0;
        double m_movement_speed = 2.5;
        double m_mouse_sensitivity = 0.001;
        double m_zoom = 45.0;

        glm::vec3 m_pos;
        glm::vec3 m_front;
        glm::vec3 m_up;
        glm::vec3 m_world_up;
        glm::vec3 m_right;

        void update_camera_vectors();
};

class RenderPipelineContext {
    public:
        RenderPipelineContext(int width, int height, std::string title);
        ~RenderPipelineContext();

        void init_imgui();
        void run_imgui();
        void process_input(GLFWwindow* window);
        float get_delta();

        void set_texture(std::string tex_name);
        void set_transforms();
        void run();

        glm::mat4 get_transform(std::string key) const { return m_transforms.at(key); };
        glm::mat4 get_view() const { return m_camera->get_view(); }

        std::vector<double> get_cursor_pos_ratio() const { return m_cursor_pos_ratio; }

    private:
        GLFWwindow* m_window;
        int m_width;
        int m_height;
        float m_aspect_ratio = static_cast<float>(m_width)/static_cast<float>(m_height);

        float m_delta = 0.0f;
        float m_last_frame = 0.0f;

        double m_cursor_pos_x;
        double m_cursor_pos_y;
        std::vector<double> m_cursor_pos_ratio{0.5, 0.5};

        std::map<std::string, glm::mat4> m_transforms;

        std::unique_ptr<Camera> m_camera = std::make_unique<Camera>();
        std::unique_ptr<Shader> m_shader = nullptr;
        std::unique_ptr<ShapeMan> m_shape_man = nullptr;
        std::unique_ptr<TextureMan> m_texture_man = nullptr;

        void set_callbacks();
        void viewport_size_callback(GLFWwindow* window, int width, int height);
        void keyboard_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
        void cursor_pos_callback(GLFWwindow* window, double xposIn, double yposIn);
        void cursor_entered_callback(GLFWwindow* window, int entered);
        void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
};

#endif
