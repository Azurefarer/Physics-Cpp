/*
This document contains the 4 core components of an OpenGL 3.0 render pipeline
using GLFW, Glad, and ImGui.
The Camera, Context, Gui, and Renderer.
*/


#ifndef GL_CORE_PIPELINE_H_
#define GL_CORE_PIPELINE_H_

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

#include "gl_core/batch_renderer.h"
#include "gl_core/shader.h"
#include "gl_core/shape_man.h"
#include "gl_core/texture_man.h"

double radian(double degrees);

enum CameraMovement {
    FORWARD = GLFW_KEY_W,
    LEFT = GLFW_KEY_A,
    BACKWARD = GLFW_KEY_S,
    RIGHT = GLFW_KEY_D
};

struct keys {
    int W_key = -1;
    int A_key = -1;
    int S_key = -1;
    int D_key = -1;
    int Ltab_key = -1;
    int esc_key = -1;
};

struct scene_data {
    bool set_null = false;
    bool set_king = false;
    bool set_face = false;
};

struct batch_data {
    float y_pos = 0.0f;
    float width = 10.0f;
    float length = 10.0f;
    float subdivide_width = 0.1f;
    float subdivide_length = 0.1f;

    int draw_count = 0;
    int quad_count = 0;
};

class Camera {
    public:
        Camera();

        void set_control(bool activity);

        void process_keyboard(int key, float delta_time);
        void process_mouse_movement(double x_offset, double y_offset, GLboolean constrain_pitch = true);
        void process_mouse_scroll(double y_offset);

        float get_pos() const { return m_pos.x; }
        float get_zoom() const { return m_zoom; }

        glm::mat4 get_view() const { return glm::lookAt(m_pos, m_pos + m_front, m_up); }
    
    private:
        bool m_active = true;
        
        double m_yaw = -(std::numbers::pi / 2);
        double m_pitch = 0.0;
        double m_movement_speed = 60.0;
        double m_mouse_sensitivity = 100;
        double m_zoom = 45.0;

        glm::vec3 m_pos;
        glm::vec3 m_front;
        glm::vec3 m_up;
        glm::vec3 m_world_up;
        glm::vec3 m_right;

        void update_camera_vectors();
};

class Gui {
    public:
        Gui(GLFWwindow *context);
        ~Gui();

        void run();
        void update_frame();

        void set_scene_data(scene_data s) { m_sdata = s; }
        void set_batch_data(batch_data b) { m_bdata = b; }
        scene_data get_scene_data() { return m_sdata; }
        batch_data get_batch_data() { return m_bdata; }

    private:
        scene_data m_sdata;
        batch_data m_bdata;
};

class Context {
    public:
        Context(int width, int height, std::string title);
        ~Context();

        bool is_live() { return !glfwWindowShouldClose(m_window); }
        bool mouse_control() { return m_mouse_control; }

        GLFWwindow *get_window() { return m_window; }
        float get_aspect_ratio() { return m_aspect_ratio; }
        double get_scroll_x() { return m_scroll_x_offset; }
        double get_scroll_y() { return m_scroll_y_offset; }
        double get_arc_x() { return m_arc_x; }
        double get_arc_y() { return m_arc_y; }

        bool get_cursor_activity() { return m_cursor_activity; }
        void set_cursor_activity(bool active);

        void swap_buffers();

        keys *get_keys_pressed() { return m_keys.get(); }

        std::vector<double> get_cursor_pos_ratio() const { return m_cursor_pos_ratio; }

    private:
        GLFWwindow* m_window;
        int m_width;
        int m_height;
        float m_aspect_ratio = static_cast<float>(m_width)/static_cast<float>(m_height);

        // bool live = glfwWindowShouldClose(m_window);
        bool m_mouse_control = true;
        double m_scroll_x_offset = 0.0f;
        double m_scroll_y_offset = 0.0f;

        double m_arc_x = 0.0f;
        double m_arc_y = 0.0f;
        bool m_cursor_activity = false;
        double m_cursor_pos_x;
        double m_cursor_pos_y;
        std::vector<double> m_cursor_pos_ratio{0.5, 0.5};

        std::shared_ptr<keys> m_keys = std::make_unique<keys>();

        void set_GLcallbacks();
        void APIENTRY message_callback(GLenum source,
                 GLenum type,
                 GLuint id,
                 GLenum severity,
                 GLsizei length,
                 const GLchar* message,
                 const void* userParam);
        void set_GLFWcallbacks();
        void viewport_size_callback(GLFWwindow* window, int width, int height);
        void keyboard_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
        void cursor_pos_callback(GLFWwindow* window, double xposIn, double yposIn);
        void cursor_entered_callback(GLFWwindow* window, int entered);
        void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
};

class Renderer {
    public:
        Renderer(std::unique_ptr<Context> pcontext);
        ~Renderer() = default;

        void run();
        void set_transforms(glm::vec3 model_offset);
        void set_shader_uniforms();
        void set_shader2_uniforms();
        void set_shader_texture(std::string tex_name, std::string uniform);
        void update_for_gui();
        void update_from_gui();
        float get_delta();

        glm::mat4 get_transform(std::string key) const { return m_transforms.at(key); };
        glm::mat4 get_view() const { return m_camera->get_view(); }

        void context_updates();

    private:
        float m_delta = 0.0f;
        float m_last_frame = 0.0f;

        scene_data m_sdata;
        batch_data m_bdata;

        std::map<std::string, glm::mat4> m_transforms;

        std::unique_ptr<BatchRenderer> m_batch = nullptr;
        std::unique_ptr<Camera> m_camera = std::make_unique<Camera>();
        std::unique_ptr<Context> m_context =  nullptr;
        std::unique_ptr<Shader> m_shader =  nullptr;
        std::unique_ptr<Shader> m_shader2 =  nullptr;
        std::unique_ptr<ShapeMan> m_shape_man = nullptr;
        std::unique_ptr<TextureMan> m_texture_man = nullptr;
        std::unique_ptr<Gui> m_gui = nullptr;
};

#endif
