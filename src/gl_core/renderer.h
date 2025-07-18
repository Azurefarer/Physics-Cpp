#ifndef GL_CORE_RENDERER_H_
#define GL_CORE_RENDERER_H_

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
#include "gl_core/context.h"
#include "gl_core/camera.h"
#include "gl_core/gui.h"
#include "gl_core/shader.h"
#include "gl_core/services.h"
#include "gl_core/rigidbody.h"
#include "gl_core/mesh.h"
#include "gl_core/texture_man.h"

class Renderer {
    public:
        Renderer(const std::shared_ptr<Services>& pservices);
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

        // get these gui fcts out of here
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

        void rigidbody_push_back(const MVP& mvp);

        float m_delta = 0.0f;
        float m_last_frame = 0.0f;
        float m_current_frame = 0.0f;

        MVP m_transforms;
        std::shared_ptr<std::vector<std::shared_ptr<RigidBody>>> m_assets;

        std::unique_ptr<BatchRenderer> m_batch = nullptr;
        std::shared_ptr<Services> m_services = nullptr;
        std::unordered_map<std::string, std::shared_ptr<Shader>> m_shaders;
        std::unique_ptr<TextureMan> m_texture_man = nullptr;
        std::unique_ptr<Gui> m_gui = nullptr;
};

#endif
