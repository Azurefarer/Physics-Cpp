#include "core/engine.h"

Engine::Engine() {
    
    setup();
}

void Engine::run() {
    m_context->run();
    m_scene->run();
    m_renderer->render(*m_scene);
}

void Engine::setup() {
    m_context = std::make_shared<Context>(1920, 1080, std::string("OpenGL Application"));
    m_services = std::make_shared<Services>(m_context);

    m_input = std::make_unique<Input>(m_context->get_window(), m_services);
    m_renderer = std::make_unique<Renderer>(m_services);
    m_scene = std::make_unique<Scene>(m_services);

    m_services->config_cache();

    auto dmesh = m_services->get_mesh_cache()->get("default");
    auto dmaterial = m_services->get_material_cache()->get("default");
    m_scene->add_rb(dmesh, dmaterial);
}
