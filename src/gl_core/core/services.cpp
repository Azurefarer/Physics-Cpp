#include "core/services.h"

Services::Services() : 
    m_mesh_cache(std::make_shared<MeshCache>()),
    m_shader_cache(std::make_shared<ShaderCache>())
{
    m_material_cache = std::make_shared<MaterialCache>(m_shader_cache);
}