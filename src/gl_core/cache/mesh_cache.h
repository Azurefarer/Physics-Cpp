#ifndef ASSET_CACHE_MESH_CACHE_H_
#define ASSET_CACHE_MESH_CACHE_H_

#include <unordered_map>
#include <string>
#include <memory>
#include "asset/mesh.h"

class MeshCache {
public:
    MeshCache();
    ~MeshCache() = default;
    void add(const std::string& name, std::shared_ptr<Mesh> mesh);
    std::shared_ptr<Mesh> get(const std::string& name) const;

private:
    std::unordered_map<std::string, std::shared_ptr<Mesh>> m_meshes;
};

#endif // ASSET_CACHE_MESH_CACHE_H_
