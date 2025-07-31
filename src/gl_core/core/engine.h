#ifndef GL_CORE_ENGINE_H_
#define GL_CORE_ENGINE_H_

#define GLM_ENABLE_EXPERIMENTAL
#define GLFW_INCLUDE_NONE

#include <memory>
#include <vector>

#include "core/context.h"
#include "core/input.h"
#include "core/services.h"
#include "scene/scene.h"
#include "servers/renderer.h"

// The Engine is what organizes all the components in the system
// An organized system has low entropy, meaning there's a lot to get.
// A well organized Engine executes low cost commands for a high output.
class Engine {
    public:
        Engine();
        ~Engine() = default;

        void run();

        bool context_active() const { return m_context->is_live(); }

    private:
        void setup();
        std::shared_ptr<Services> m_services;
        std::unique_ptr<Context> m_context;
        std::unique_ptr<Input> m_input;
        // std::unique_ptr<Gui> m_gui; // should take out as another higher-order entity like engine.
        std::unique_ptr<Renderer> m_renderer;
        std::unique_ptr<Scene> m_scene;

};

#endif
