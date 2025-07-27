#include "core/input.h"

void Input::set_GLFWcallbacks() {
    glfwSetFramebufferSizeCallback(m_window, viewport_size_callback);
    glfwSetKeyCallback(m_window, keyboard_callback);
    glfwSetCursorPosCallback(m_window, cursor_pos_callback);
    glfwSetCursorEnterCallback(m_window, cursor_entered_callback);
    glfwSetScrollCallback(m_window, scroll_callback);
}

void Input::viewport_size_callback(GLFWwindow* window, int width, int height) {
    if (auto* ctx = static_cast<Input*>(glfwGetWindowUserPointer(window))) {
        ctx->on_resize(width, height);
    }
}

void Input::keyboard_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (auto* ctx = static_cast<Input*>(glfwGetWindowUserPointer(window))) {
        ctx->on_key(key, scancode, action, mods);
    }
}

void Input::cursor_pos_callback(GLFWwindow* window, double xpos, double ypos) {
    if (auto* ctx = static_cast<Input*>(glfwGetWindowUserPointer(window))) {
        ctx->on_cursor_pos(xpos, ypos);
    }
}

void Input::cursor_entered_callback(GLFWwindow* window, int entered) {
    if (auto* ctx = static_cast<Input*>(glfwGetWindowUserPointer(window))) {
        ctx->on_cursor_enter(entered);
    }
}

void Input::scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    if (auto* ctx = static_cast<Input*>(glfwGetWindowUserPointer(window))) {
        ctx->on_scroll(xoffset, yoffset);
    }
}

void Input::on_resize(int width, int height) {
    glViewport(0, 0, width, height);
    m_services->set_width(width);
    m_services->set_height(height);
}

void Input::on_key(int key, int scancode, int action, int mods) {
    if ( action == GLFW_REPEAT ) {
        return;
    }
    if ( action == GLFW_PRESS ) {
        if ( key == GLFW_KEY_ESCAPE ) {
            glfwSetWindowShouldClose(m_window, true);
        }
        if ( key == GLFW_KEY_TAB ) {
            static bool gaming = true;
            if ( gaming ) {
                (m_keys).Ltab_key = key;
                glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
                gaming = true;
            } else {
                (m_keys).Ltab_key = -1;
                glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
                gaming = false;
            }
        }
        if ( key == GLFW_KEY_W ) {
            (m_keys).W_key = key;
        }
        if ( key == GLFW_KEY_A ) {
            (m_keys).A_key = key;
        }
        if ( key == GLFW_KEY_S ) {
            (m_keys).S_key = key;
        }
        if ( key == GLFW_KEY_D ) {
            (m_keys).D_key = key;
        }
    }
    if ( action == GLFW_RELEASE ) {
        if ( key == GLFW_KEY_W ) {
            (m_keys).W_key = -1;
        }
        if ( key == GLFW_KEY_A ) {
            (m_keys).A_key = -1;
        }
        if ( key == GLFW_KEY_S ) {
            (m_keys).S_key = -1;
        }
        if ( key == GLFW_KEY_D ) {
            (m_keys).D_key = -1;
        }
    }
}

void Input::on_cursor_pos(double xposIn, double yposIn) {
    m_arc_x += xposIn - m_cursor_pos_x;
    m_arc_y += m_cursor_pos_y - yposIn;
    m_cursor_pos_x = xposIn;
    m_cursor_pos_y = yposIn;
    m_cursor_pos_ratio = {m_cursor_pos_x/m_width, m_cursor_pos_y/m_height};

    set_cursor_activity(true);
}

void Input::on_cursor_enter(int entered) {
    glfwSetCursorPos(m_window, m_cursor_pos_x, m_cursor_pos_y);
}

void Input::on_scroll(double xoffset, double yoffset) {
    m_scroll_x_offset = xoffset;
    m_scroll_y_offset = yoffset;
    
    m_scroll_activity = true;
}
