#pragma once
#include <iostream>
#include "gl_core/renderer.h"

class Window {
    public:
        Window(unsigned int width, unsigned int height, const char* title);
        ~Window();

        void process_input(GLFWwindow* window);
        GLFWwindow* get_window() const { return m_window; }
        
    private:
        GLFWwindow* m_window;
};
