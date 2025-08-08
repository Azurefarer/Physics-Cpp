#ifndef CORE_CONTEXT_H_
#define CORE_CONTEXT_H_

#include <iostream>
#include <memory>
#include <vector>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

class Context {
    public:
        Context(int width, int height, std::string title);
        ~Context();
        void run();

        bool is_live() const { return !glfwWindowShouldClose(m_window); }

        GLFWwindow* get_window() const { return m_window; }

        void set_width(int width) { m_width = width; }
        void set_height(int height) { m_height = height; }
        int get_width() const { return m_width; }
        int get_height() const { return m_height; }
        double get_aspect_ratio() const;
        float get_time() const { return m_current_frame; }
        float get_delta_time() { return m_delta; }

        void set_resolution(int width, int height);

        void swap_buffers();

    private:
        int m_width;
        int m_height;
        std::string m_title;

        GLFWwindow* m_window;
        float m_delta;
        float m_current_frame;
        float m_last_frame;

        void set_GLcallbacks();
        void APIENTRY message_callback(GLenum source,
                 GLenum type,
                 GLuint id,
                 GLenum severity,
                 GLsizei length,
                 const GLchar* message,
                 const void* userParam);
};

#endif // CORE_CONTEXT_H_