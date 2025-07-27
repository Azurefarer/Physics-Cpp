#ifndef ASSET_MATERIAL_H_
#define ASSET_MATERIAL_H_

#include "asset/shader.h"

// Material is kind of an extra interface layer between the actual shaderprogram and the entity that will use it.

class Material {
    public:
        Material(const std::shared_ptr<Shader> &shader) : m_shader(shader) {};

        void use_shader();

        void set_bool   (const std::string& name, bool value) const;
        void set_int    (const std::string& name, unsigned int value);
        void set_float  (const std::string& name, float value) const;
        void set_vec2   (const std::string& name, const glm::vec2 &value) const;
        void set_vec2   (const std::string& name, float x, float y) const;
        void set_vec3   (const std::string& name, const glm::vec3 &value) const;
        void set_vec3   (const std::string& name, float x, float y, float z) const;
        void set_vec4   (const std::string& name, const glm::vec4 &value) const;
        void set_vec4   (const std::string& name, float x, float y, float z, float w) const;
        void set_mat2   (const std::string& name, const glm::mat2 &mat) const;
        void set_mat3   (const std::string& name, const glm::mat3 &mat) const;
        void set_mat4   (const std::string& name, const glm::mat4 &mat) const;

    private:
        std::shared_ptr<Shader> m_shader;
        std::unordered_map<std::string, float> m_floats;
        std::unordered_map<std::string, glm::vec4> m_vec4s;
        std::unordered_map<std::string, int> m_ints;
        std::unordered_map<std::string, glm::mat4> m_mat4s;
};

#endif // ASSET_MATERIAL_H_
