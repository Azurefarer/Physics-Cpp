#include "gl_core/services.h"

Services::Services() : 
    m_shader_cache(std::make_shared<ShaderCache>()),
    m_shape_cache(std::make_shared<ShapeCache>())
    {}