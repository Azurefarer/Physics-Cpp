#ifndef CACHE_MATERIAL_CACHE_H_
#define CACHE_MATERIAL_CACHE_H_

#include <unordered_map>
#include <string>
#include <memory>
#include "asset/material.h"
#include "cache/shader_cache.h"

class MaterialCache {
public:
    MaterialCache(const std::shared_ptr<ShaderCache>& shaders);
    ~MaterialCache() = default;
    void add(const std::string& name, std::shared_ptr<Material> material);
    void add(const std::string& name, const std::shared_ptr<Shader>& shader);
    std::shared_ptr<Material> get(const std::string& name) const;
    const std::unordered_map<std::string, std::shared_ptr<Material>>& get_map() { return m_materials; }

private:
    std::unordered_map<std::string, std::shared_ptr<Material>> m_materials;
};

#endif // CACHE_MATERIAL_CACHE_H_
