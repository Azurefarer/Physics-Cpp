#ifndef GL_CORE_GUI_H_
#define GL_CORE_GUI_H_

#define GLM_ENABLE_EXPERIMENTAL

#include <cmath>
#include <iostream>
#include <numbers>
#include <memory>
#include <vector>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/string_cast.hpp"

#include "gl_core/batch_renderer.h"
#include "gl_core/shader.h"
#include "gl_core/rigidbody.h"
#include "gl_core/shapes.h"
#include "gl_core/texture_man.h"

// Gui should talk directly to the engine for any info it wants
// Could be from any of the components of the Engine.

class Gui {
    public:
        Gui(GLFWwindow *context);
        ~Gui();

        void run();

        void set_rigidbodies(const std::shared_ptr<std::vector<std::shared_ptr<RigidBody>>>& assets);
        void sleep();
        void wake_up();
        bool status_report() { return m_status; }
        int get_res_id() { return m_res_id; }

    private:
        bool m_status = false; // True means run() is being called by Renderer.

        GLFWwindow *m_context;

        int m_res_id = 0;
        int m_tex_id = 0;

        std::shared_ptr<std::vector<std::shared_ptr<RigidBody>>> m_assets;
        bool add_button_bool();
        std::vector<bool> m_rigidbody_shader_param_references;
        std::vector<bool>::iterator m_rigidbody_shader_param_references_iterator;

        void init(GLFWwindow *context);
        void start_frame(const char* title);
        void show_diagnostics();
        void set_resolution();
        void show_asset_data();
        void set_shader_uniforms(RigidBody& asset);
        void set_batch(std::string asset_name);
        void set_batch_shader();
        void reset_texture_options();
        void set_texture();
        void set_toon();
        void set_light(std::string asset_name);
        void set_light_shader();
        void end_frame();
};

#endif
