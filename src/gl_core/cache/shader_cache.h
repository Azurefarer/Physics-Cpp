#ifndef ASSET_CACHE_SHADER_CACHE_H_
#define ASSET_CACHE_SHADER_CACHE_H_

#include <memory>
#include <unordered_map>
#include <string>
#include <filesystem>
#include "asset/shader.h"

class ShaderCache {
public:
    ShaderCache();
    ~ShaderCache() = default;
    std::shared_ptr<Shader> get(const std::string& name);
    const std::unordered_map<std::string, std::shared_ptr<Shader>>& get_map() { return m_shader_programs; }

private:
    std::unordered_map<std::string, std::shared_ptr<Shader>> m_shader_programs;
};

#endif // ASSET_CACHE_SHADER_CACHE_H_
