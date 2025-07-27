#ifndef GL_CORE_RENDERER_H_
#define GL_CORE_RENDERER_H_

#include <cmath>
#include <iostream>
#include <numbers>
#include <unordered_map>
#include <memory>
#include <vector>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/string_cast.hpp"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "asset/mesh.h"
#include "asset/shader.h"
#include "core/services.h"
#include "scene/scene.h"
// #include "gl_core/texture_man.h"

class Renderer {
    public:
        Renderer(const std::shared_ptr<Services>& pservices);
        ~Renderer() = default;

        void run();
        void render(const Scene& scene);
    private:

        float m_delta = 0.0f;
        float m_last_frame = 0.0f;
        float m_current_frame = 0.0f;

        std::shared_ptr<Services> m_services = nullptr;
};

#endif
