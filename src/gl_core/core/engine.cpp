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
    m_services = std::make_shared<Services>();
    m_context = std::make_unique<Context>(1920, 1080, std::string("OpenGL Application"), m_services);
    m_input = std::make_unique<Input>(m_context->get_window(), m_services);
    m_renderer = std::make_unique<Renderer>(m_services);
    m_scene = std::make_unique<Scene>(m_services);
    m_context->set_services(m_services);
    m_services->config_cache();
}
