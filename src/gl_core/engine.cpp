#include "gl_core/engine.h"

Engine::Engine() 
    : m_services(std::make_shared<Services>()),
    m_context (std::make_unique<Context>(1920, 1080, std::string("OpenGL Application"), &m_services)),
    m_gui (std::make_unique<Gui>(m_context->get_window(), &m_services)),
    m_renderer (std::make_unique<Renderer>(&m_services)),
    m_scene (std::make_unique<Scene>(&m_services))
    {}

void Engine::run() {
    m_context->run();
    m_scene->run();
    m_renderer->run();
}
