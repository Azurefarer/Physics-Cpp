#ifndef GL_CORE_ENGINE_H_
#define GL_CORE_ENGINE_H_

#define GLM_ENABLE_EXPERIMENTAL

#include <memory>
#include <vector>

#include "gl_core/context.h"
#include "gl_core/scene.h"
#include "gl_core/services.h"
#include "gl_core/renderer.h"

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
        std::shared_ptr<Services> m_services;
        std::unique_ptr<Context> m_context;
        std::unique_ptr<Gui> m_gui;
        std::unique_ptr<Renderer> m_renderer;
        std::unique_ptr<Scene> m_scene;
};



#endif
