#include "cache/material_cache.h"

MaterialCache::MaterialCache(const std::shared_ptr<ShaderCache>& cache) {
    const auto& shaders = cache->get_map();
    for (const auto& [name, shader] : shaders) {
        m_materials[name] = std::make_shared<Material>(shader);
    }
}

void MaterialCache::add(const std::string& name, std::shared_ptr<Material> material) {
    m_materials[name] = material;
}

void MaterialCache::add(const std::string& name, const std::shared_ptr<Shader>& shader) {
    m_materials[name] = std::make_shared<Material>(shader);
}

std::shared_ptr<Material> MaterialCache::get(const std::string& name) const {
    auto it = m_materials.find(name);
    if (it != m_materials.end()) {
        return it->second;
    } else { return nullptr; }
}
