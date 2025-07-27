#include "core/services.h"

Services::Services() : 
    m_material_cache(std::make_shared<MaterialCache>()),
    m_mesh_cache(std::make_shared<MeshCache>()),
    m_shader_cache(std::make_shared<ShaderCache>())
    {}