#ifndef CORE_CONTEXT_H_
#define CORE_CONTEXT_H_

#define GLM_ENABLE_EXPERIMENTAL

#include <cmath>
#include <iostream>
#include <numbers>
#include <unordered_map>
#include <memory>
#include <vector>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "core/services.h"
#include "core/vertex.h"

class Context {
    public:
        Context(int width, int height, std::string title, const std::shared_ptr<Services>& pservices);
        ~Context();
        void run();

        bool is_live() const { return !glfwWindowShouldClose(m_window); }
        bool get_gui_focus() { return m_gui_focus; }
        void set_gui_focus(bool focus) { m_gui_focus = focus; }
        GLFWwindow* get_window() const { return m_window; }
        float get_delta_time() { return m_delta; }
        float get_aspect_ratio() { return m_aspect_ratio; }
        double get_scroll_x() { return m_scroll_x_offset; }
        double get_scroll_y() { return m_scroll_y_offset; }

        double get_arc_x() { return m_arc_x; }
        void set_arc_x(double x) { m_arc_x = x; }
        double get_arc_y() { return m_arc_y; }
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
        std::shared_ptr<Services> m_services;
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
        std::shared_ptr<keys> m_keys = std::make_shared<keys>();
        void set_GLcallbacks();
        void APIENTRY message_callback(GLenum source,
                 GLenum type,
                 GLuint id,
                 GLenum severity,
                 GLsizei length,
                 const GLchar* message,
                 const void* userParam);
        void set_GLFWcallbacks();
        // Static glfw bounce fcts
        static void viewport_size_callback(GLFWwindow* window, int width, int height);
        static void keyboard_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
        static void cursor_pos_callback(GLFWwindow* window, double xposIn, double yposIn);
        static void cursor_entered_callback(GLFWwindow* window, int entered);
        static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
        // glfw callback responses
        void on_resize(int width, int height);
        void on_key(int key, int scancode, int action, int mods);
        void on_cursor_pos(double xposIn, double yposIn);
        void on_cursor_enter(int entered);
        void on_scroll(double xoffset, double yoffset);

};

#endif // CORE_CONTEXT_H_