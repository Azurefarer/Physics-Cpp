#include "cache/mesh_cache.h"

MeshCache::MeshCache() {
    m_meshes["default"] = std::make_shared<Mesh>(quad_vertices, quad_indices);
    m_meshes["quad"] = std::make_shared<Mesh>(quad_vertices, quad_indices);
    m_meshes["cube"] = std::make_shared<Mesh>(cube_vertices, cube_indices);
}

void MeshCache::add(const std::string& name, std::shared_ptr<Mesh> mesh) {
    m_meshes[name] = mesh;
}

std::shared_ptr<Mesh> MeshCache::get(const std::string& name) const {
    auto it = m_meshes.find(name);
    if (it != m_meshes.end()) {
        return it->second;
    } else { return nullptr; }
}
