#ifndef GUI_GUI_H_
#define GUI_GUI_H_

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

class Gui {
    public:
        Gui();
        ~Gui();

    private:
        bool m_set_null = false;
        bool m_set_king = false;
        bool m_set_face = false;
        float m_imgui_y = 0;
        float m_imgui_width = 10.0;
        float m_imgui_length = 10.0;
        float m_imgui_sub_width = 0.1;
        float m_imgui_sub_length = 0.1;
};

#endif
