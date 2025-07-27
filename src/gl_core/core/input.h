#ifndef CORE_INPUT_H_
#define CORE_INPUT_H_

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

struct keys {
    int W_key = -1;
    int A_key = -1;
    int S_key = -1;
    int D_key = -1;
    int space = -1;
    int Ltab_key = -1;
    int esc_key = -1;
};

class Input {
    public:
        Input(const std::shared_ptr<Services>& pservices);
        ~Input() = default;
        
    private:
        std::shared_ptr<Services> m_services;
        GLFWwindow* m_window;
        keys m_keys;

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

#endif // CORE_INPUT_H_
