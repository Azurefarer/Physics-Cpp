#ifndef RENDERER_H_
#define RENDERER_H_

#include <iostream>
#include <vector>
#include "glad/glad.h"
#include "GLFW/glfw3.h"

#define ASSERT(x) if (!(x)) __debugbreak();
#define GL_call(x) GL_clear_error();\
    x;\
    ASSERT(GL_log_call(#x, __FILE__, __LINE__))

typedef struct {
    float x, y, z;
    float r, g, b;
    // float nx, ny, nz;
    float u, v;
} Vertex;

void GL_clear_error();
bool GL_log_call(const char* function, const char* file, int line);
void viewport_size_callback(GLFWwindow* window, int width, int height);

class Window {
    public:
        Window(unsigned int width, unsigned int height, const char* title);
        ~Window();

        void process_input(GLFWwindow* window);

        std::vector<float> get_cursor_pos_ratio() const { return m_cursor_pos_ratio; }

        GLFWwindow* get_window() const { return m_window; }

    private:
        GLFWwindow* m_window;
        double m_cursor_pos_x = 0;
        double m_cursor_pos_y = 0;
        unsigned int m_width = 0;
        unsigned int m_height = 0;
        std::vector<float> m_cursor_pos_ratio{0, 0};
};
#endif
