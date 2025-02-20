/*
This document contains the 4 core components of an OpenGL 3.0 render pipeline
using GLFW, Glad, and ImGui.
The Camera, Context, Gui, and Renderer.
*/


#ifndef GL_CORE_PIPELINE_H_
#define GL_CORE_PIPELINE_H_

#define GLM_ENABLE_EXPERIMENTAL

#include <cmath>
#include <iostream>
#include <numbers>
#include <unordered_map>
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
#include "gl_core/rigidbody.h"
#include "gl_core/shader_parser.h"
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

    // Everything in this struct should be able to be categorized as a System

    // *Sys* Resolution tracking
    struct Resolution {
        int WIDTH = 2560;
        int HEIGHT = 1440;
    };
    Resolution res;

    // int counting system
    int rigidbodies = 0;

    // Shader Texture System
    bool set_null = false;
    bool set_king = false;
    bool set_face = false;
    bool set_back = false;
    bool set_sand = false;

    // Shader uniform system
    float v_amplitude_mult = 1.050;
    float v_amplitude = 2.150;
    float v_omega_mult = 0.440;
    float v_omega = 0.02;
    float v_lambda_mult = 1.500;
    float v_lambda = 326.000; // 320
    float v_peak_width = 0.430;
    float fresnel_coeff = 10.0;
    float spec_coeff = 7.0;

    bool toon = true;
    int toon_buckets = 8;

    float ambient_strength = 1.0;
    glm::vec4 light_color = glm::vec4{1.0};
    glm::vec4 light_pos = glm::vec4{0.0, 25.0, 0.0, 0.0};
};

struct batch_data {

    // Same with the Batch data, everything should be a part of a system.

    glm::vec3 pos = glm::vec3(0.0, -100.0, 0.0);
    float width = 500.0f;
    float length = 500.0f;
    float subdivide_width = 5.0f;
    float subdivide_length = 5.0f;

    int draw_count = 0;
    int quad_count = 0;
};

class Gui {
    public:
        Gui(GLFWwindow *context);
        ~Gui();

        void run();

        void set_scene_data(scene_data s) { m_sdata = s; }
        void set_batch_data(batch_data b) { m_bdata = b; }
        scene_data get_scene_data() { return m_sdata; }
        batch_data get_batch_data() { return m_bdata; }

        void set_rigidbodies(std::shared_ptr<std::unordered_map<std::string, std::shared_ptr<RigidBody>>> assets);
        void sleep();
        void wake_up();
        bool status_report() { return m_status; }
        int get_res_id() { return m_res_id; }

    private:
        bool m_status = false; // True means run() is being called by Renderer.
        scene_data m_sdata;
        batch_data m_bdata;

        GLFWwindow *m_context;

        int m_res_id = 0;
        int m_tex_id = 0;

        std::shared_ptr<std::unordered_map<std::string, std::shared_ptr<RigidBody>>> m_assets;
        bool add_button_bool();
        std::vector<bool> m_rigidbody_shader_param_references;
        std::vector<bool>::iterator m_rigidbody_shader_param_references_iterator;

        void init(GLFWwindow *context);
        void start_frame(const char* title);
        void show_diagnostics();
        void set_resolution();
        void show_asset_data();
        void set_shader_uniforms(RigidBody asset);
        void set_batch(std::string asset_name);
        void set_batch_shader();
        void reset_texture_options();
        void set_texture();
        void set_toon();
        void set_light(std::string asset_name);
        void set_light_shader();
        void end_frame();
};

class Context {
    public:
        Context(int width, int height, std::string title);
        ~Context();

        void run();

        bool is_live() { return !glfwWindowShouldClose(m_window); }
        bool get_gui_focus() { return m_gui_focus; }
        void set_gui_focus(bool focus) { m_gui_focus = focus; }

        GLFWwindow *get_window() { return m_window; }
        float get_delta_time() { return m_delta; }

        void set_MVP(glm::mat4 view, double zoom);
        MVP get_MVP() const { return m_mvp; }

        float get_aspect_ratio() { return m_aspect_ratio; }
        double get_scroll_x() { return m_scroll_x_offset; }
        double get_scroll_y() { return m_scroll_y_offset; }
        double get_arc_x() { return m_arc_x; }
        double get_arc_y() { return m_arc_y; }
        void set_arc_x(double x) { m_arc_x = x; }
        void set_arc_y(double y) { m_arc_y = y; }

        bool get_cursor_activity() { return m_cursor_activity; }
        void set_cursor_activity(bool activity) { m_cursor_activity = activity; };
        
        bool get_scroll_activity() { return m_scroll_activity; }
        void set_scroll_activity(bool activity) { m_scroll_activity = activity; };
        
        bool get_keyboard_activity() { return m_keyboard_activity; } // may remove
        void set_keyboard_activity(bool activity) { m_keyboard_activity = activity; }; // may remove

        void set_resolution(int width, int height);

        void swap_buffers();

        keys *get_keys_pressed() { return m_keys.get(); }

        std::vector<double> get_cursor_pos_ratio() const { return m_cursor_pos_ratio; }

    private:
        GLFWwindow* m_window;
        float m_delta;
        float m_current_frame;
        float m_last_frame;

        int m_width;
        int m_height;
        float m_aspect_ratio = static_cast<float>(m_width)/static_cast<float>(m_height);

        bool m_gui_focus = false;
        
        bool m_cursor_activity = false;
        bool m_scroll_activity = false;
        bool m_keyboard_activity = false; // may remove

        double m_arc_x = 0.0f;
        double m_arc_y = 0.0f;
        double m_cursor_pos_x;
        double m_cursor_pos_y;
        std::vector<double> m_cursor_pos_ratio{0.5, 0.5};
        
        double m_scroll_x_offset = 0.0f;
        double m_scroll_y_offset = 0.0f;

        std::shared_ptr<keys> m_keys = std::make_unique<keys>();

        MVP m_mvp;

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

class Camera {
    public:
        Camera(std::shared_ptr<Context> pcontext);
        void point_at(glm::vec3 front);
        void run();

        void set_control(bool activity);

        void process_keyboard(int key, float delta_time);
        void process_mouse_movement(double x_offset, double y_offset, GLboolean constrain_pitch = true);
        void process_mouse_scroll(double y_offset);

        float get_pos() const { return m_pos.x; }
        float get_zoom() const { return m_zoom; }

        glm::mat4 get_view() const { return m_view; }
    
    private:
        std::shared_ptr<Context> m_context;
        bool m_active = true;
        
        double m_yaw;
        double m_pitch; // for (m_yaw, m_pitch) = (0, 0) m_front, m_right, and m_up are the xyz basis vectors.
        double m_movement_speed = 600.0;
        double m_mouse_sensitivity = 100;
        double m_zoom = 45.0;

        glm::mat4 m_view;
        void set_view();

        glm::vec3 m_pos;
        glm::vec3 m_front;
        glm::vec3 m_up;
        glm::vec3 m_world_up;
        glm::vec3 m_right;

        void update_camera_vectors();
};

class IO {
    public:
        IO(std::shared_ptr<Context> pcontext);
        ~IO();

        void run();

    private:
        std::shared_ptr<Context> m_context;
};

class Renderer {
    public:
        Renderer(std::shared_ptr<Context> pcontext);
        ~Renderer() = default;

        void run();
    private:
        void draw();

        void set_MVP(glm::vec3 model_offset, glm::vec3 scale = glm::vec3(1.0)); // Model-View-Projection Matrix
        void draw_batch();
        void updates_for_gui();
        void process_delta();

        void gui_updates();
        void context_updates();

        void set_shader_uniform_texture(std::string tex_name, std::string uniform);
        void set_shader_uniform_float(std::string uniform, float value);
        void set_shader_uniform_int(std::string uniform, int value);
        void set_shader_uniform_vec4(std::string uniform, glm::vec4 vec4);

        void update_gui_uniforms();

        void set_batch_config_params();

        void set_batch_uniforms();
        void set_phong_uniforms();
        void set_light_uniforms();
        void set_toon_uniforms();

        void rigidbody_push_back(const MVP& mvp, std::string shaderhandle, std::string shape);

        float m_delta = 0.0f;
        float m_last_frame = 0.0f;
        float m_current_frame = 0.0f;

        scene_data m_sdata;
        batch_data m_bdata;

        MVP m_transforms;
        std::shared_ptr<std::unordered_map<std::string, std::shared_ptr<RigidBody>>> m_assets;

        std::unique_ptr<BatchRenderer> m_batch = nullptr;
        std::shared_ptr<Context> m_context = nullptr;
        std::unordered_map<std::string, std::shared_ptr<Shader>> m_shaders;
        std::unique_ptr<ShapeMan> m_shape_man = nullptr;
        std::unique_ptr<TextureMan> m_texture_man = nullptr;
        std::unique_ptr<Gui> m_gui = nullptr;
};

#endif
