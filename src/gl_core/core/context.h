#ifndef CORE_CONTEXT_H_
#define CORE_CONTEXT_H_

#include <iostream>
#include <memory>
#include <vector>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "core/services.h"
#include "core/vertex.h"

class Context {
    public:
        Context(int width, int height, std::string title);
        ~Context();
        void run();

        bool is_live() const { return !glfwWindowShouldClose(m_window); }

        GLFWwindow* get_window() const { return m_window; }
        float get_delta_time() { return m_delta; }

        void set_resolution(int width, int height);

        void swap_buffers();
        void set_services(const std::shared_ptr<Services>& pservices) { m_services = pservices; }
    private:
        std::shared_ptr<Services> m_services;
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