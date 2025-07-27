#include "cache/shader_cache.h"

ShaderCache::ShaderCache() {
    
    struct ShaderPaths {
        std::filesystem::path vertex;
        std::filesystem::path fragment;
        std::filesystem::path geometry;
        std::filesystem::path compute;
    };

    std::unordered_map<std::string, ShaderPaths> groups;

    for (const auto& entry : std::filesystem::directory_iterator(SHADER_DIR)) { // using cmake functionality to define a macro for my glsl src code.
        if (!entry.is_regular_file()) continue;
        auto path = entry.path();
        std::string name = path.stem().string();
        auto ext = path.extension();

        ShaderPaths& p = groups[name];
        if (ext == ".vs")       p.vertex   = path;
        else if (ext == ".fs")  p.fragment = path;
        else if (ext == ".gs")  p.geometry = path;
        else if (ext == ".cs")  p.compute  = path;
    }

    for (const auto& [name, p] : groups) {
        if (!p.compute.empty()) {
            auto shader = std::make_shared<Shader>(std::filesystem::path{}, std::filesystem::path{}, std::filesystem::path{}, p.compute);
            shader->set_name(name);
            m_shader_programs.insert({name, shader});
        } else if (!p.vertex.empty() && !p.fragment.empty()) {
            auto shader = std::make_shared<Shader>(p.vertex, p.fragment, p.geometry);
            shader->set_name(name);
            m_shader_programs.insert({name, shader});
        }
    }
}

std::shared_ptr<Shader> ShaderCache::get(const std::string& name) {
    auto it = m_shader_programs.find(name);
    if (it != m_shader_programs.end()) {
        return it->second;
    } else { return nullptr; }
}
