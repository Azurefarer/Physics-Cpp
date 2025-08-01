#include "core/services.h"

Services::Services(std::shared_ptr<Context> context) :
m_context(context) {
}

void Services::config_cache() {
    m_mesh_cache = std::make_shared<MeshCache>();
    m_shader_cache = std::make_shared<ShaderCache>();
    m_material_cache = std::make_shared<MaterialCache>(m_shader_cache);
}